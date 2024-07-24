#include "tmml_cl.hpp"

using namespace std;
using namespace cv;
using namespace cl;

tmml_cl::tmml_cl(bool & init_OK, const int temp_left, const int temp_top, const Mat & img_work, const Mat & img_temp)
{
    temp_leftOK = temp_left;
    temp_topOK = temp_top;
    result res;

    initDevice(init_OK);
    loadAndBuildProgram(init_OK, string(KERNEL_FILE));

    imageData_ptr = make_unique<cl_uchar[]>(img_work.cols * img_work.rows);
    templateData_ptr = make_unique<cl_uchar[]>(img_temp.cols * img_temp.rows);
    mData_ptr = make_unique<cl_uint[]>((img_work.cols - img_temp.cols + 1) * (img_work.rows - img_temp.rows + 1));

    loadDataMatToUchar(imageData_ptr.get(), img_work, 1);
    loadDataMatToUchar(templateData_ptr.get(), img_temp, 1);

    clInputImg = Buffer(context,CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_work.cols * img_work.rows);
    clInputTemp = Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_temp.rows * img_temp.cols);
    clInputRes = Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(result));
    clInputK_FLOAT_TO_INT = Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
    clInputMaxVal = Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
    clmData = Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_uint) * (img_work.cols - img_temp.cols + 1) * (img_work.rows - img_temp.rows + 1));

    // Kernels
    int clError = 0;
    clkProcess=Kernel(program, KERNEL_NAME, &clError );
    if (clError != 0 )
    {
        cout<<"clError"<<endl;
        init_OK = false;
    }// END if (clError != 0 )

    // Send Data
    queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * img_work.cols * img_work.rows, &imageData_ptr.get()[0]);
    queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * img_temp.rows * img_temp.cols, &templateData_ptr.get()[0]);
    queue.enqueueWriteBuffer(clInputRes, CL_TRUE, 0,  sizeof(result), &res);
    queue.enqueueWriteBuffer(clInputK_FLOAT_TO_INT, CL_TRUE, 0,  sizeof(cl_int), &k_float_to_int);
    queue.enqueueWriteBuffer(clInputMaxVal, CL_TRUE, 0,  sizeof(cl_int), &maxVal);
    queue.enqueueWriteBuffer(clmData, CL_TRUE, 0,  sizeof(cl_uint) * (img_work.cols - img_temp.cols + 1) * (img_work.rows - img_temp.rows + 1), &mData_ptr[0]);

    // Init Kernel arguments
    clkProcess.setArg(0, clInputImg);
    clkProcess.setArg(1, clInputTemp);
    clkProcess.setArg(2, clInputRes);
    clkProcess.setArg(3, (int)img_work.cols);
    clkProcess.setArg(4, (int)img_work.rows);
    clkProcess.setArg(5, (int)img_temp.cols);
    clkProcess.setArg(6, (int)img_temp.rows);
    clkProcess.setArg(7, clInputK_FLOAT_TO_INT);
    clkProcess.setArg(8, clInputMaxVal);
    clkProcess.setArg(9, clmData);
}

tmml_cl::~tmml_cl()
{
    cout <<"Destructor tmml_cl\n";
}

int tmml_cl::matchingCL(const Mat& img_work, const Mat& img_temp )
{
    // Image 2D
    NDRange gRM=NDRange((img_work.cols - img_temp.cols + 1), (img_work.rows - img_temp.rows + 1));

    queue.enqueueNDRangeKernel(clkProcess, NullRange, gRM, NullRange );
    queue.finish();
    queue.enqueueReadBuffer(clInputMaxVal, CL_TRUE, 0, sizeof(cl_int),&maxVal);
    queue.enqueueReadBuffer(clInputRes, CL_TRUE, 0, sizeof(result),&res);
    queue.enqueueReadBuffer(clmData, CL_TRUE, 0, sizeof(cl_uint) * (img_work.cols - img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1), &mData_ptr[0]);
    return 0;
}// END int matchingCL

string tmml_cl::loadKernelFile(const string program)
{
    ifstream f(program);
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}// END string loadKernelFile

void tmml_cl::initDevice(bool & init_OK)
{
    Platform::get(&all_platforms);
    if(all_platforms.size() == 0)
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
}// END int initDevice()

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
}// END int loadAndBuildProgram(string programFile)

void tmml_cl::loadDataMatToUchar(unsigned char *data, const Mat &image, const int nchannels)
{
    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < height; ++y)
    {
        int posY = y * width * nchannels;
        for (int x = 0 ; x < width ; ++x)
        {
            data[posY + x * nchannels + 0] = image.at<unsigned char>(y, x);
            if (nchannels == 3)
            {
                data[posY + x * nchannels + 1] = image.at<unsigned char>(y, x);
                data[posY + x * nchannels + 2] = image.at<unsigned char>(y, x);
            }// END if (nchannels==3)
        }// END for (int x = 0 ; x < width ; x++)
    }// END for (int y=0; y < height; y++)
}// END void loadDataMatToUchar

void tmml_cl::uintToMat(const unsigned int *data, Mat &image)
{
    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < image.rows; ++y)
    {
        int posY = y * width;
        for (int x = 0 ; x < height ; ++x)
        {
            image.at<uint>(y,x) = data[posY + x];
        }
    }// END void uintToMat(uint *data, Mat &image)
}// END void uintToMat(uint *data, Mat &image)




