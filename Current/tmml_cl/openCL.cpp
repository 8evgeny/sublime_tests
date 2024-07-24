#include "openCL.hpp"

using namespace std;
using namespace cv;
using namespace chrono;
using namespace cl;

tmml_cl::tmml_cl(int temp_left, int temp_top)
{
    temp_leftOK = temp_left;
    temp_topOK = temp_top;
    result res;
}

tmml_cl::~tmml_cl()
{
}

int tmml_cl::initOpenCL(const Mat& img_work, const Mat& img_temp, int match_method )
{
    initDevice();
    loadAndBuildProgram(KERNEL_FILE);
    imageData = make_unique<cl_uchar[]>(img_work.cols * img_work.rows);
    templateData = make_unique<cl_uchar[]>(img_temp.cols * img_temp.rows);
    mData = make_unique<cl_uint[]>((img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1));
    for (int i = 0; i < (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1);++i)
    {
        mData[i]=0;
    }

    loadDataMatToUchar(imageData.get(), img_work, 1);
    loadDataMatToUchar(templateData.get(), img_temp, 1);
    res.tm_result = 10000;
    res.xpos=0;
    res.ypos=0;

    clInputImg=Buffer(context,CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_work.cols * img_work.rows);
    clInputTemp=Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_temp.rows * img_temp.cols);
    clInputRes=Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(result));
    clInputMinVal=Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
    clInputMaxVal=Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
    clMatchMethod=Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(int));
    clmData=Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1));

    // Kernels
    int iclError = 0;
    clkProcess=Kernel(program, KERNEL_NAME, &iclError );
    if (iclError != 0 )
    {
        cout<<"iclError"<<endl;
        return -1;
    }

    // Send Data
    queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * img_work.cols * img_work.rows, &imageData.get()[0]);
    queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * img_temp.rows * img_temp.cols, &templateData.get()[0]);
    queue.enqueueWriteBuffer(clInputRes, CL_TRUE, 0,  sizeof(result), &res);
    queue.enqueueWriteBuffer(clInputMinVal, CL_TRUE, 0,  sizeof(cl_int), &minVal);
    queue.enqueueWriteBuffer(clInputMaxVal, CL_TRUE, 0,  sizeof(cl_int), &maxVal);
    queue.enqueueWriteBuffer(clMatchMethod, CL_TRUE, 0,  sizeof(int), &match_method);
    queue.enqueueWriteBuffer(clmData, CL_TRUE, 0,  sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1), &mData[0]);

    // Init Kernel arguments
    clkProcess.setArg(0,clInputImg);
    clkProcess.setArg(1,clInputTemp);
    clkProcess.setArg(2,clInputRes);

    clkProcess.setArg(3, (int)img_work.cols);
    clkProcess.setArg(4, (int)img_work.rows);
    clkProcess.setArg(5, (int)img_temp.cols);
    clkProcess.setArg(6, (int)img_temp.rows);
    clkProcess.setArg(7, clInputMinVal);
    clkProcess.setArg(8, clInputMaxVal);
    clkProcess.setArg(9, match_method);
    clkProcess.setArg(10, clmData);

    return 0;
}

int tmml_cl::matchingCL(const Mat& img_work, const Mat& img_temp )
{
    // Image 2D
    NDRange gRM=NDRange((img_work.cols - img_temp.cols + 1), (img_work.rows - img_temp.rows + 1));

    queue.enqueueNDRangeKernel(clkProcess, NullRange, gRM, NullRange );
    queue.finish();
    queue.enqueueReadBuffer(clInputMinVal, CL_TRUE, 0, sizeof(cl_int),&minVal);
    queue.enqueueReadBuffer(clInputMaxVal, CL_TRUE, 0, sizeof(cl_int),&maxVal);
    queue.enqueueReadBuffer(clInputRes, CL_TRUE, 0, sizeof(result),&res);
    queue.enqueueReadBuffer(clmData, CL_TRUE, 0, sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1) ,&mData[0]);
    return 0;
}//--END-- int matchingCL(const Mat& img_work, const Mat& img_temp, Mat& img_result_CL, int match_method, int iter_num, result & res )

string tmml_cl::loadKernelFile(string program)
{
    ifstream t(program);
    return string((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
}//--END-- string loadKernelFile(string program)

int tmml_cl::initDevice()
{
    Platform::get(&all_platforms);
    if(all_platforms.size()==0)
    {
        cout<<" No platforms found. Check OpenCL installation!\n";
        return -1;
    }//--END-- if(all_platforms.size()==0)
    default_platform=Platform(all_platforms[0]);
    //cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0)
    {
        cout<<" No devices found. Check OpenCL installation!\n";
        return -1;
    }//--END-- if (all_devices.size() == 0)
    default_device=Device(all_devices[0]);
    //cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    context=Context(default_device);
    queue=CommandQueue(context, default_device);
    return 0;
}//--END-- int initDevice()

int tmml_cl::loadAndBuildProgram(string programFile)
{
    Program::Sources sources;
    string kernel_source = loadKernelFile(programFile);
    pair<const char*, ::size_t> src(kernel_source.c_str(), kernel_source.length());
    sources.push_back(src);
    program=Program(context, sources);
    vector<Device> devices;
    devices.push_back(default_device);
    if(program.build(devices)!=CL_SUCCESS)
    {
        cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        return -1;
    }//--END-- if(program.build(devices)!=CL_SUCCESS)

    return 0;
}//--END-- int loadAndBuildProgram(string programFile)

void tmml_cl::loadDataMatToUchar(uchar *data, const Mat &image, int nchannels)
{
    int width = image.cols;
    int height = image.rows;
    for (int y=0; y < height; y++)
    {
        auto posY = (long)y * (long)width * (long)nchannels;
        for (int x = 0 ; x < width ; x++)
        {
            data[posY + (long)x * nchannels + 0] = image.at<uchar>(y,x);
            if (nchannels == 3)
            {
                data[posY + (long)x * nchannels + 1] = image.at<uchar>(y,x);
                data[posY + (long)x * nchannels + 2] = image.at<uchar>(y,x);
            }//--END-- if (nchannels==3)
        }//--END-- for (int x = 0 ; x < width ; x++)
    }//--END-- for (int y=0; y < height; y++)
}//--END-- void loadDataMatToUchar(uchar *data, const Mat &image, int nchannels)

void tmml_cl::uintToMat(uint *data, Mat &image)
{
    for (int y=0; y<image.rows;y++)
    {
        auto posY = (long)y * (long)image.cols;
        for (int x = 0 ; x<image.cols ; x++)
        {
            image.at<uint>(y,x) = data[posY + x] ;
        }
    }//--END-- void uintToMat(uint *data, Mat &image)
}//--END-- void uintToMat(uint *data, Mat &image)




