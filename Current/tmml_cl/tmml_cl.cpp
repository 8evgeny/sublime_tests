#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace cl;

tmml_cl::tmml_cl(bool& ok, float& min_max_Val0)
{
    cout <<"START Construktor tmml_cl\n";
    result res;
    initDevice(ok);
    if(!ok){cout<< "error initDevice!!!\n"; return;}
    loadAndBuildProgram(ok, string(KERNEL_FILE));
    if(!ok){cout<< "error loadAndBuildProgram!!!\n"; return;}
    imageData_ptr = make_unique<cl_uchar[]>(WORK_AREA);
    templateData_ptr = make_unique<cl_uchar[]>(TEMPLATE_AREA);
    mData_ptr = make_unique<cl_uint[]>(RESULT_AREA);

    clInputImg = Buffer(context, CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * WORK_AREA);
    clInputTemp = Buffer(context, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * TEMPLATE_AREA);
    clInputRes = Buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(result));
    clInputMaxVal = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
#ifdef find_diff_result
    clmData = Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_uint) * RESULT_AREA);
#endif
    // Kernels
    int clError = 0;
    clkProcess = Kernel(program, KERNEL_NAME, &clError );
    if(clError != 0 )
    {
        cout << "clError!!!" << endl;
        ok = false;
        return;
    }// END if (clError != 0 )
#ifdef find_diff_result
    queue.enqueueWriteBuffer(clmData, CL_TRUE, 0,  sizeof(cl_uint) * RESULT_AREA, &mData_ptr[0]);
#endif

    // Init Kernel arguments
    clkProcess.setArg(0, clInputImg);
    clkProcess.setArg(1, clInputTemp);
    clkProcess.setArg(2, clInputRes);
    clkProcess.setArg(3, clInputMaxVal);
#ifdef find_diff_result
    clkProcess.setArg(4, clmData);
#endif
    ok = true;
    cout <<"Constructor tmml_cl ok=" << ok << endl;
}// END tmml_cl::tmml_cl

tmml_cl::~tmml_cl()
{
    cout <<"Destructor tmml_cl\n";
}// END tmml_cl::~tmml_cl

int tmml_cl::work_tmml(const Mat& img_work, const Mat& img_temp, Pix& max_pix )
{
    loadDataMatToUchar(imageData_ptr.get(), img_work);
    loadDataMatToUchar(templateData_ptr.get(), img_temp);
    // Send Data
    queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * WORK_AREA, &imageData_ptr.get()[0]);
    queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * TEMPLATE_AREA, &templateData_ptr.get()[0]);

    // Image 2D
    NDRange gRM = NDRange(RESULT_WIDTH, RESULT_HEIGHT);
    queue.enqueueNDRangeKernel(clkProcess, NullRange, gRM, NullRange );
    queue.finish();
    queue.enqueueReadBuffer(clInputRes, CL_TRUE, 0, sizeof(result),&res);
#ifdef find_diff_result
    queue.enqueueReadBuffer(clmData, CL_TRUE, 0, sizeof(cl_uint) * RESULT_AREA, &mData_ptr[0]);
#endif
    max_pix.x = res.xpos;
    max_pix.y = res.ypos;
    max_pix.bright = (float)res.tm_result;
    return 0;
}// END work_tmml

string tmml_cl::loadKernelFile(const string program)
{
    ifstream f(program);
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}// END tmml_cl::loadKernelFile

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
    string kernel_source = loadKernelFile(programFile);
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


