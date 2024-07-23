#include "openCL.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

string kernel_source;
cl::Kernel clkProcess;
cl::Buffer clInputImg, clInputTemp, clInputRes, clInputMinVal, clInputMaxVal, clResults, clMatchMethod, clmData;
cl::CommandQueue queue;
cl::Context context;
cl::Program program;
cl::Device default_device;
std::vector<cl::Device> all_devices;
cl::Platform default_platform;
vector<cl::Platform> all_platforms;

tmml_cl::tmml_cl()
{
}

tmml_cl::~tmml_cl()
{
}

int tmml_cl::matchingOpenCL(unique_ptr<tmml_cl> & tm_cl, const cv::Mat& img_work, const cv::Mat& img_temp, cv::Mat& img_result_CL, int match_method, int iter_num, PixCL & pixOK, result & res )
{

    high_resolution_clock::time_point time_start_OpenCL, time_end_OpenCL;
    int minVal = 0;
    int maxVal = 0;
    tm_cl->initDevice();
    tm_cl->loadAndBuildProgram(KERNEL_FILE);

    cl_uchar* imageData = new cl_uchar[img_work.cols * img_work.rows];

    cl_uchar* templateData = new cl_uchar[img_temp.cols * img_temp.rows];
    cl_uint* mData = new cl_uint[(img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1)];

    for (int i = 0; i < (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1);++i)
    {
        mData[i]=0;
    }

    tm_cl->loadDataMatToUchar(imageData, img_work, 1);
    tm_cl->loadDataMatToUchar(templateData, img_temp, 1);

    res.tm_result = 10000;
    res.xpos=0;
    res.ypos=0;
    cl_short aux = 10000;

    time_start_OpenCL = chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iter_num ; ++iter)
    {
        clInputImg=cl::Buffer(context,CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_work.cols * img_work.rows);
        clInputTemp=cl::Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_temp.rows * img_temp.cols);
        clInputRes=cl::Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(result));
        clInputMinVal=cl::Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
        clInputMaxVal=cl::Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
        clMatchMethod=cl::Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(int));
        clmData=cl::Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1));

        // Kernels
        int iclError = 0;
        clkProcess=cl::Kernel(program, KERNEL_NAME, &iclError );

        if (iclError != 0 )
        {
            cout<<"iclError"<<endl;
            delete[] imageData;
            delete[] templateData;
            delete[] mData;
            return -1;
        }
        // Send Data
        queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * img_work.cols * img_work.rows, &imageData[0]);
        queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * img_temp.rows * img_temp.cols, &templateData[0]);
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

        // Image 2D
        cl::NDRange gRM=cl::NDRange((img_work.cols - img_temp.cols + 1), (img_work.rows - img_temp.rows + 1));

        queue.enqueueNDRangeKernel(clkProcess, cl::NullRange, gRM, cl::NullRange );
        queue.finish();
        queue.enqueueReadBuffer(clInputMinVal, CL_TRUE, 0, sizeof(cl_int),&minVal);
        queue.enqueueReadBuffer(clInputMaxVal, CL_TRUE, 0, sizeof(cl_int),&maxVal);
        queue.enqueueReadBuffer(clInputRes, CL_TRUE, 0, sizeof(result),&res);
        queue.enqueueReadBuffer(clmData, CL_TRUE, 0, sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1) ,&mData[0]);

        if ((res.xpos != pixOK.x) || (res.ypos != pixOK.y)) { cout << "CL iter " << iter << " error !!!" << endl; break; }

    }//-- END -- for (int i = 0; i < iter_num; ++i)
    time_end_OpenCL = high_resolution_clock::now();

    tm_cl->uintToMat(mData, img_result_CL);

    delete[] imageData;
    delete[] templateData;
    delete[] mData;

    auto time_matching_CL = std::chrono::duration_cast<chrono::microseconds>(time_end_OpenCL - time_start_OpenCL);
    printf("Duration OpenCL =  \t%.2f mks \n", (float)time_matching_CL.count() / iter_num );
    cout << "openCL xy =\t\t[" << res.xpos << ", " << res.ypos << "] " /*<<"   bright= " << tm->max_pix.bright*/ << endl<<endl;

    return 0;
}//--END-- int matchingOpenCL(const cv::Mat& img_work, const cv::Mat& img_temp, cv::Mat& img_result_CL, int match_method, int iter_num, result & res )

string tmml_cl::loadKernelFile(string program)
{
    std::ifstream t(program);
    return std::string((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
}//--END-- string loadKernelFile(string program)

int tmml_cl::initDevice()
{
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0)
    {
        cout<<" No platforms found. Check OpenCL installation!\n";
        return -1;
    }//--END-- if(all_platforms.size()==0)
    default_platform=cl::Platform(all_platforms[0]);
    //cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0)
    {
        cout<<" No devices found. Check OpenCL installation!\n";
        return -1;
    }//--END-- if (all_devices.size() == 0)
    default_device=cl::Device(all_devices[0]);
    //std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    context=cl::Context(default_device);
    queue=cl::CommandQueue(context, default_device);
    return 0;
}//--END-- int initDevice()

int tmml_cl::loadAndBuildProgram(std::string programFile)
{
    cl::Program::Sources sources;
    string kernel_source = loadKernelFile(programFile);
    pair<const char*, ::size_t> src(kernel_source.c_str(), kernel_source.length());
    sources.push_back(src);
    program=cl::Program(context, sources);
    VECTOR_CLASS<cl::Device> devices;
    devices.push_back(default_device);
    if(program.build(devices)!=CL_SUCCESS)
    {
        cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        return -1;
    }//--END-- if(program.build(devices)!=CL_SUCCESS)

    return 0;
}//--END-- int loadAndBuildProgram(std::string programFile)

void tmml_cl::loadDataMatToUchar(uchar *data, const cv::Mat &image, int nchannels)
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
}//--END-- void loadDataMatToUchar(uchar *data, const cv::Mat &image, int nchannels)

void tmml_cl::uintToMat(uint *data, cv::Mat &image)
{
    for (int y=0; y<image.rows;y++)
    {
        auto posY = (long)y * (long)image.cols;
        for (int x = 0 ; x<image.cols ; x++)
        {
            image.at<uint>(y,x) = data[posY + x] ;
        }
    }//--END-- void uintToMat(uint *data, cv::Mat &image)
}//--END-- void uintToMat(uint *data, cv::Mat &image)




