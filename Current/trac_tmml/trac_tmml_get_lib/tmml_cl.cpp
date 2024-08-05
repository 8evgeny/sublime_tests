#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace cl;

tmml_cl::tmml_cl(bool& ok, float& min_max_Val0)
{
    cout << "START Constructor tmml_cl\n";
    img_result = Mat(Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, Scalar(0));
    min_max_Val = min_max_Val0;
    min_max_Val2 = min_max_Val0 * min_max_Val0;
    initDevice(ok);
    if(!ok){cout << "error initDevice!!!\n"; return;}
    loadAndBuildProgram(ok, string(KERNEL_FILE));
    if(!ok){cout << "error loadAndBuildProgram!!!\n"; return;}

    // ================================================= work_cl_1:
    img_work_buff = Buffer(context, CL_MEM_READ_WRITE  | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * WORK_AREA);
    img_temp_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * TEMPLATE_AREA);
    img_result_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(float) * RESULT_AREA);
    maxVal_int_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(int));
    max_pix_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(Pix));
    int clError1 = 0;
    tmml_cl_kernel1 = Kernel(program, KERNEL_tmml_cl_NAME1, &clError1);
    if(clError1 != 0)
    {
        cout << "clError1=" << clError1 << "; KERNEL_tmml_cl_NAME1=" << KERNEL_tmml_cl_NAME1 << " =============== !!!" << endl;
        ok = false;
        return;
    } // END if(clError1 != 0)
    tmml_cl_kernel1.setArg(0, img_work_buff);
    tmml_cl_kernel1.setArg(1, img_temp_buff);
    tmml_cl_kernel1.setArg(2, img_result_buff);
    tmml_cl_kernel1.setArg(3, maxVal_int_buff);
    tmml_cl_kernel1.setArg(4, max_pix_buff);

    // ================================================= work_cl_max:
//    img_result_bright_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(float) * RESULT_WIDTH);
//    img_result_x_buff = Buffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * RESULT_WIDTH);
//    int clError2 = 0;
//        tmml_cl_kernel2 = Kernel(program, KERNEL_tmml_cl_NAME2, &clError2);
//        if(clError2 != 0)
//        {
//            cout << "clError2=" << clError2 << "; KERNEL_tmml_cl_NAME2=" << KERNEL_tmml_cl_NAME2 << " =============== !!!" << endl;
//            ok = false;
//            return;
//        } // END if(clError2 != 0)
//    tmml_cl_kernel2.setArg(0, img_result_buff);
//    tmml_cl_kernel2.setArg(1, img_result_bright_buff);
//    tmml_cl_kernel2.setArg(2, img_result_x_buff);
    ok = true;
    cout << "Constructor tmml_cl ok=" << ok << endl;
} // END tmml_cl

tmml_cl::~tmml_cl()
{
    cout << "Destructor tmml_cl\n";
} // END ~tmml_cl


void tmml_cl::work_tmml(const Mat & img_work, const Mat & img_temp, Pix & max_pix)
{
    // ================================================= work_cl_1:
//    int temp_id = 0;
//    for(int y = 0; y < TEMPLATE_WIDTH; ++y)
//    {
//        for(int x = 0; x < TEMPLATE_WIDTH; ++x)
//        {
//            //const uchar * data = img_temp.ptr<uchar>(0);
//            //uchar px = data[y*img_temp.cols + x];
//            if(TEMPLATE_WIDTH != img_temp.cols){cout << "img_temp.cols=" << img_temp.cols << "; img_temp.rows=" << img_temp.rows << "!!!\n";}
//            img_temp_arr[temp_id] = img_temp.data[y*img_temp.cols + x];// img_temp.at<unsigned char>(y, x);
//            temp_id++;
//        } // END for(int x = 0; x < TEMPLATE_WIDTH; x++)
//    } // END for(int y = 0; y < TEMPLATE_WIDTH; y++)

//    int work_id = 0;
//    for(int y = 0; y < WORK_WIDTH; ++y)
//    {
//        for(int x = 0; x < WORK_WIDTH; ++x)
//        {
//            //const uchar * data = img_work.ptr<uchar>(0);
//            //uchar px = data[y*img_work.cols + x];
//            if(WORK_WIDTH != img_work.cols){cout << "WORK_WIDTH=" << WORK_WIDTH << "; img_work.cols=" << img_work.cols << "!!!\n";}
//            img_work_arr[work_id] = img_work.data[y*WORK_WIDTH + x];// img_work.at<unsigned char>(y, x);
//            work_id++;
//        } // END for(int x = 0; x < TEMPLATE_WIDTH; x++)
//    } // END for(int y = 0; y < TEMPLATE_WIDTH; y++)

    qu.enqueueWriteBuffer(maxVal_int_buff, CL_TRUE, 0, sizeof(int), &maxVal_int);
    qu.enqueueWriteBuffer(img_work_buff, CL_TRUE, 0, sizeof(unsigned char) * WORK_AREA, &img_work.data[0]);
    qu.enqueueWriteBuffer(img_temp_buff, CL_TRUE, 0, sizeof(unsigned char) * TEMPLATE_AREA, &img_temp.data[0]);
    qu.enqueueNDRangeKernel(tmml_cl_kernel1, NullRange, NDRange(RESULT_AREA), NullRange);
    qu.finish();
    qu.enqueueReadBuffer(max_pix_buff, CL_TRUE, 0, sizeof(Pix), &max_pix);
#if defined(find_diff_result)
    qu.enqueueReadBuffer(img_result_buff, CL_TRUE, 0, sizeof(float) * RESULT_AREA, &img_result.data[0]);
#endif // END #if defined(find_diff_result)

// =====================
//    minMaxLoc(img_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//    max_pix.x = maxLoc.x;
//    max_pix.y = maxLoc.y;
//    max_pix.bright = maxVal;
// =======================
// ================================================= work_cl_max:
//    qu.enqueueNDRangeKernel(tmml_cl_kernel2, NullRange, NDRange(RESULT_WIDTH), NullRange);
//    qu.finish();
//    qu.enqueueReadBuffer(img_result_bright_buff, CL_TRUE, 0, sizeof(float) * RESULT_WIDTH, &img_result_bright[0]);
//    qu.enqueueReadBuffer(img_result_x_buff, CL_TRUE, 0, sizeof(unsigned char) * RESULT_WIDTH, &img_result_x[0]);
//    max_pix = max_pix0;
//    for(int y = 0; y < RESULT_WIDTH; ++y)
//    {
//        if(img_result_bright[y] > max_pix.bright)
//        {
//            max_pix.x = img_result_x[y];
//            max_pix.y = y;
//            max_pix.bright = img_result_bright[y];
//        } // END if(img_result_bright[y] > max_pix.bright)
//    } // END for(int y = 0; y < RESULT_WIDTH; ++y)
} // END work_tmml

string tmml_cl::loadKernelFile(const string & program)
{
    ifstream f(program);
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
} // END loadKernelFile

void tmml_cl::initDevice(bool & init_OK)
{
    Platform::get(&all_platforms);
    if(!all_platforms.size())
    {
        cout << "No platforms found. Check OpenCL installation!\n";
        init_OK = false;
    } // END if(!all_platforms.size())
    default_platform=Platform(all_platforms[0]);
    cout << "Using CL platform: \t" << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(!all_devices.size())
    {
        cout << "No devices found. Check OpenCL installation!\n";
        init_OK = false;
        return;
    } // END if(!all_devices.size())
    default_device = Device(all_devices[0]);
    cout << "Using CL device: \t" << default_device.getInfo<CL_DEVICE_NAME>() << "\n";
    context = Context(default_device);
    qu = CommandQueue(context, default_device);
    init_OK = true;
} // END initDevice

void tmml_cl::loadAndBuildProgram(bool & init_OK, const string & programFile)
{
    Program::Sources sources;
    string kernel_source = loadKernelFile(programFile);
    pair<const char*, ::size_t> src(kernel_source.c_str(), kernel_source.length());
    sources.push_back(src);
    program = Program(context, sources);
    vector<Device> devices;
    devices.push_back(default_device);
    if(program.build(devices) != CL_SUCCESS)
    {
        cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
        init_OK = false;
        return;
    } // END if(program.build(devices) != CL_SUCCESS)
    init_OK = true;
} // END loadAndBuildProgram

