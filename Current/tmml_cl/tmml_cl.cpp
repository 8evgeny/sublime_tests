#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace cl;

tmml_cl::tmml_cl(bool& ok, float& min_max_Val0)
{
    cout <<"START Construktor tmml_cl\n";
    initDevice(ok);
    if(!ok){cout<< "error initDevice!!!\n"; return;}
    loadAndBuildProgram(ok, string(KERNEL_FILE));
    if(!ok){cout<< "error loadAndBuildProgram!!!\n"; return;}
    imageData_ptr = make_unique<cl_uchar[]>(WORK_AREA);
    templateData_ptr = make_unique<cl_uchar[]>(TEMPLATE_AREA);
    mData_ptr = make_unique<cl_float[]>(RESULT_AREA);
    img_work_buff = Buffer(context, CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * WORK_AREA);
    img_temp_buff = Buffer(context, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * TEMPLATE_AREA);
    img_result_buff = Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_float) * RESULT_AREA);
    // Kernels
    int clError = 0;
    tmml_cl_kernel = Kernel(program, KERNEL_NAME, &clError );
    if(clError != 0 )
    {
        cout << "clError!!!" << endl;
        ok = false;
        return;
    }// END if (clError != 0 )
    queue.enqueueWriteBuffer(img_result_buff, CL_TRUE, 0,  sizeof(cl_float) * RESULT_AREA, &mData_ptr[0]);

    // Init Kernel arguments
    tmml_cl_kernel.setArg(0, img_work_buff);
    tmml_cl_kernel.setArg(1, img_temp_buff);
    tmml_cl_kernel.setArg(2, img_result_buff);
    ok = true;
    cout <<"Constructor tmml_cl ok=" << ok << endl;
}// END tmml_cl::tmml_cl

tmml_cl::~tmml_cl()
{
    cout <<"Destructor tmml_cl\n";
}// END tmml_cl::~tmml_cl

void tmml_cl::work_tmml(const Mat& img_work, const Mat& img_temp, Pix& max_pix )
{
    loadDataMatToUchar(imageData_ptr.get(), img_work);
    loadDataMatToUchar(templateData_ptr.get(), img_temp);
    // Send Data
    queue.enqueueWriteBuffer(img_work_buff, CL_TRUE, 0,  sizeof(unsigned char) * WORK_AREA, &imageData_ptr.get()[0]);
    queue.enqueueWriteBuffer(img_temp_buff, CL_TRUE, 0,  sizeof(unsigned char) * TEMPLATE_AREA, &templateData_ptr.get()[0]);

    // Image 2D
    NDRange gRM = NDRange(RESULT_WIDTH, RESULT_HEIGHT);
    queue.enqueueNDRangeKernel(tmml_cl_kernel, NullRange, gRM, NullRange );
    queue.finish();
    queue.enqueueReadBuffer(img_result_buff, CL_TRUE, 0, sizeof(cl_float) * RESULT_AREA, &mData_ptr[0]);
    Mat img_result_cpu(RESULT_WIDTH, RESULT_HEIGHT, CV_32F, mData_ptr.get());
    minMaxLoc(img_result_cpu, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    max_pix.x = maxLoc.x;
    max_pix.y = maxLoc.y;
    max_pix.bright = mData_ptr.get()[maxLoc.y * RESULT_HEIGHT + maxLoc.x];
}// END work_tmml

#ifdef KernelFromFile
string tmml_cl::loadKernelFile(const string & program)
{
    ifstream f(program);
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}// END tmml_cl::loadKernelFile
#endif
void tmml_cl::initDevice(bool & init_OK)
{
    Platform::get(&all_platforms);
    if(!all_platforms.size())
    {
        cout<<" No platforms found. Check OpenCL installation!\n";
        init_OK = false;
    }// END if(all_platforms.size() == 0)
    default_platform=Platform(all_platforms[0]);
    cout << "Using CL platform: \t"<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0)
    {
        cout<<" No devices found. Check OpenCL installation!\n";
        init_OK = false;
    }// END if (all_devices.size() == 0)
    default_device=Device(all_devices[0]);
    cout<< "Using CL device: \t"<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    context=Context(default_device);
    queue=CommandQueue(context, default_device);
    init_OK = true;
}// END initDevice

void tmml_cl::loadAndBuildProgram(bool & init_OK, const string & programFile)
{
    Program::Sources sources;
    #ifdef KernelFromFile
        string kernel_source = loadKernelFile(programFile);
    #endif
    #ifndef KernelFromFile
        string kernel_source = tmml_cl::programm_CL;
    #endif

//    cout<<"kernel_source = "<<kernel_source<<endl;
    pair<const char*, ::size_t> src(kernel_source.c_str(), kernel_source.length());
    sources.push_back(src);
    program=Program(context, sources);
    vector<Device> devices;
    devices.push_back(default_device);
    if(program.build(devices) != CL_SUCCESS)
    {
        cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        init_OK = false;
    }// END if(program.build(devices)!=CL_SUCCESS)
    cout<<"building_CL OK\n";
}// END loadAndBuildProgram

void tmml_cl::loadDataMatToUchar(unsigned char *data, const Mat &image)
{
    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < height; ++y)
    {
        int posY = y * width;
        for (int x = 0 ; x < width ; ++x)
        {
            data[posY + x ] = image.at<unsigned char>(y, x);
        }// END for (int x = 0 ; x < width ; x++)
    }// END for (int y=0; y < height; y++)
}// END loadDataMatToUchar

void tmml_cl::uintToMat(const unsigned int *data, Mat &image)
{
    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < height; ++y)
    {
        int posY = y * width;
        for (int x = 0 ; x < width ; ++x)
        {
            image.at<uint>(y,x) = data[posY + x];
        }// END for (int x = 0 ; x < width ; ++x)
    }// END for (int y = 0; y < height; ++y)
}// END uintToMat

