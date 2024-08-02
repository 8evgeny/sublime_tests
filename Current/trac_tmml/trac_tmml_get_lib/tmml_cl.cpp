#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace cl;

tmml_cl::tmml_cl(bool& ok, float& min_max_Val0)
{
    cout <<"START Construktor tmml_cl\n";
    img_result = Mat(Size(RESULT_WIDTH, RESULT_HEIGHT), CV_32FC1, Scalar(0));
    min_max_Val = min_max_Val0;
    min_max_Val2 = min_max_Val0 * min_max_Val0;
    initDevice(ok);
    if(!ok){cout<< "error initDevice!!!\n"; return;}
    loadAndBuildProgram(ok, string(KERNEL_FILE));
    if(!ok){cout<< "error loadAndBuildProgram!!!\n"; return;}
    img_work_buff = Buffer(context, CL_MEM_READ_WRITE  | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * WORK_AREA);
    img_temp_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * TEMPLATE_AREA);
    img_result_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(float) * RESULT_AREA);
    // Kernels
    int clError = 0;
    tmml_cl_kernel = Kernel(program, KERNEL_NAME, &clError);
    if(clError != 0)
    {
        cout << "clError=" << clError << "; KERNEL_tmml_cl_NAME1=" << KERNEL_NAME << " =============== !!!" << endl;
        ok = false;
        return;
    } // END if(clError != 0)
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
    int temp_id = 0;
    for(int y = 0; y < TEMPLATE_HEIGHT; ++y)
    {
        for(int x = 0; x < TEMPLATE_WIDTH; ++x)
        {
            img_temp_arr[temp_id] = img_temp.at<unsigned char>(y, x);
            temp_id++;
        } // END for(int x = 0; x < TEMPLATE_WIDTH; x++)
    } // END for(int y = 0; y < TEMPLATE_HEIGHT; y++)

    int work_id = 0;
    for(int y = 0; y < WORK_HEIGHT; ++y)
    {
        for(int x = 0; x < WORK_WIDTH; ++x)
        {
            img_work_arr[work_id] = img_work.at<unsigned char>(y, x);
            work_id++;
        } // END for(int x = 0; x < TEMPLATE_WIDTH; x++)
    } // END for(int y = 0; y < TEMPLATE_HEIGHT; y++)

    queue.enqueueWriteBuffer(img_work_buff, CL_TRUE, 0, sizeof(unsigned char) * WORK_AREA, &img_work_arr[0]);
    queue.enqueueWriteBuffer(img_temp_buff, CL_TRUE, 0, sizeof(unsigned char) * TEMPLATE_AREA, &img_temp_arr[0]);

    // Image 1D
    NDRange gRM = NDRange(RESULT_WIDTH * RESULT_HEIGHT);
    queue.enqueueNDRangeKernel(tmml_cl_kernel, NullRange, gRM, NullRange );
    queue.finish();
    queue.enqueueReadBuffer(img_result_buff, CL_TRUE, 0, sizeof(float) * RESULT_AREA, &img_result.data[0]);
    minMaxLoc(img_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    max_pix.x = maxLoc.x;
    max_pix.y = maxLoc.y;
    max_pix.bright = maxVal;
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
