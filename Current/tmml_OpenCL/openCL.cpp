#include "openCL.hpp"

using namespace std;
using namespace cv;

extern int match_method;
extern Mat img_work, img_temp;
extern int iter_num;
extern Mat img_result_CL;
std::string kernel_source;
chrono::high_resolution_clock::time_point time_start_OpenCL, time_end_OpenCL;
cl::Kernel clkProcess;
cl::Buffer clInputImg, clInputTemp, clInputRes, clInputMinVal,  clResults, clMatchMethod, clmData;
cl::CommandQueue queue;
cl::Context context;
cl::Program program;
cl::Program::Sources sources;
cl::Device default_device;
std::vector<cl::Device> all_devices;
cl::Platform default_platform;
std::vector<cl::Platform> all_platforms;
int minVal = 0;
size_t max_workgroup_size, global_size;

int matchingOpenCL()
{
    initDevice();
    loadAndBuildProgram(KERNEL_FILE);

    cl_uchar* imageData = new cl_uchar[img_work.cols * img_work.rows];

    cl_uchar* templateData = new cl_uchar[img_temp.cols * img_temp.rows];
    cl_uint* mData = new cl_uint[(img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1)];

    for (int i = 0; i < (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1);++i)
    {
        mData[i]=0;
    }

    loadDataMatToUchar(imageData, img_work, 1);
    loadDataMatToUchar(templateData, img_temp, 1);

    result res;
    res.tm_result = 10000;
    res.xpos=0;
    res.ypos=0;
    cl_short aux = 10000;

    time_start_OpenCL = chrono::high_resolution_clock::now();

    for (int i = 0; i < iter_num; ++i)
    {
        clInputImg=cl::Buffer(context,CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_work.cols * img_work.rows);
        clInputTemp=cl::Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * img_temp.rows * img_temp.cols);
        clInputRes=cl::Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(result));
        clInputMinVal=cl::Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int));
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
        queue.enqueueWriteBuffer(clMatchMethod, CL_TRUE, 0,  sizeof(int), &match_method);
        queue.enqueueWriteBuffer(clmData, CL_TRUE, 0,  sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1), &mData[0]);

        //--- Init Kernel arguments ---------------------------------------------------
        clkProcess.setArg(0,clInputImg);
        clkProcess.setArg(1,clInputTemp);
        clkProcess.setArg(2,clInputRes);

        clkProcess.setArg(3, (int)img_work.cols);
        clkProcess.setArg(4, (int)img_work.rows);
        clkProcess.setArg(5, (int)img_temp.cols);
        clkProcess.setArg(6, (int)img_temp.rows);
        clkProcess.setArg(7, clInputMinVal);
        clkProcess.setArg(8, match_method);
        clkProcess.setArg(9, clmData);

        // Image 2D
        cl::NDRange gRM=cl::NDRange((img_work.cols - img_temp.cols + 1), (img_work.rows - img_temp.rows + 1));

        queue.enqueueNDRangeKernel(
                    clkProcess,
                    cl::NullRange,
                    gRM,
                    cl::NullRange
                    );
        queue.finish();
        queue.enqueueReadBuffer(clInputMinVal, CL_TRUE, 0, sizeof(cl_int),&minVal);
        queue.enqueueReadBuffer(clInputRes, CL_TRUE, 0, sizeof(result),&res);
        queue.enqueueReadBuffer(clmData, CL_TRUE, 0,
                                sizeof(cl_uint) * (img_work.cols-img_temp.cols + 1) * (img_work.rows-img_temp.rows + 1) ,&mData[0]);

    }//End -- for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)
    time_end_OpenCL = chrono::high_resolution_clock::now();
    uintToMat(mData, img_result_CL);

    cout<<endl;
    for (int i = res.xpos  + res.ypos * (img_work.cols - img_temp.cols + 1);
         i < res.xpos + res.ypos * (img_work.cols - img_temp.cols + 1) + 10; ++i)
//    for (int i = 0; i < (img_work.cols - img_temp.cols + 1)*(img_work.rows - img_temp.rows + 1); ++i)
    {
        cout<<mData[i]<<"  ";
    }
    cout<<endl;
    cout << "minVal = " <<minVal<<endl;



    delete[] imageData;
    delete[] templateData;
    delete[] mData;

    auto time_matching_GPU = std::chrono::duration_cast<chrono::milliseconds>(time_end_OpenCL - time_start_OpenCL);
    printf("Duration OpenCL =  \t%.2f ms \n", (float)time_matching_GPU.count()/iter_num );

    cv::cvtColor(img_work,img_work,cv::COLOR_GRAY2BGR);
    cv::rectangle(img_work, cv::Point(res.xpos, res.ypos), cv::Point(res.xpos+img_temp.cols, res.ypos+img_temp.rows),cv::Scalar(0,0,255),3);
    const char* OpenCL = "matchingOpenCL";
    namedWindow( OpenCL, WINDOW_AUTOSIZE );
    moveWindow(OpenCL, 1300,400);
    imshow(OpenCL, img_work);



    cout << "openCL xy =\t\t[" << res.xpos << ", " << res.ypos << "] " /*<<"   bright= " << tm->max_pix.bright*/ << endl;

return 0;
}

int loadKernelFile(std::string program)
{
    QFile kernelFile(program.c_str());
    if (!kernelFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout <<"error kernel file"<<endl;
        return -1;
    }
    kernel_source = kernelFile.readAll().toStdString();
    kernelFile.close();

    return 0;
}

int initDevice()
{
    //get all platforms (drivers)

    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        return -1;
    }
    default_platform=cl::Platform(all_platforms[0]);
//    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

    //get default device of the default platform

    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        return -1;
    }
    default_device=cl::Device(all_devices[0]);
//    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

    context=cl::Context(default_device);

    queue=cl::CommandQueue(context, default_device);
    return 0;
}

int loadAndBuildProgram(std::string programFile)
{
    loadKernelFile(programFile);

    std::pair<const char*, ::size_t> src(kernel_source.c_str(), kernel_source.length());
    sources.push_back(src);

    program=cl::Program(context, sources);
    VECTOR_CLASS<cl::Device> devices;
    devices.push_back(default_device);

    if(program.build(devices)!=CL_SUCCESS)
    {
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        return -1;
    }

    return 0;
}


void loadDataMatToUchar(uchar *data, cv::Mat &image, int nchannels)
{
    int width = image.cols;
    int height = image.rows;
    for (int y=0; y<height;y++)
    {
        for (int x = 0 ; x<width ; x++)
        {
            data[(long)y * (long)width * (long)nchannels + (long)x*nchannels + 0] = image.at<uchar>(y,x);
            if (nchannels==3)
            {
                data[(long)y * (long)width * (long)nchannels + (long)x*nchannels + 1] = image.at<uchar>(y,x);
                data[(long)y * (long)width * (long)nchannels + (long)x*nchannels + 2] = image.at<uchar>(y,x);
            }
        }
    }
}
void ucharToMat(uchar *data,cv::Mat &image)
{
    for (int y=0; y<image.rows;y++)
    {
        for (int x = 0 ; x<image.cols ; x++)
        {
            image.at<uchar>(y,x) = data[(long)y * (long)image.cols + x] ;
        }
    }
}

void uintToMat(uint *data,cv::Mat &image)
{
    for (int y=0; y<image.rows;y++)
    {
        for (int x = 0 ; x<image.cols ; x++)
        {
            image.at<uint>(y,x) = data[(long)y * (long)image.cols + x] ;
        }
    }
}




