#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
#include <fstream>
#include <iostream>

extern int const match_method;
extern bool enable_Serial_stop_after_find_zero;
using namespace std;
using namespace cv;

int initDevice();
int loadAndBuildProgram(std::string programFile);

std::string kernel_source;
chrono::high_resolution_clock::time_point time_start_OpenCV, time_end_OpenCV, time_start_GPU, time_end_GPU;
cl::Kernel clkProcess;
cl::Buffer clInputImg, clInputTemp, clInputVar, clInputAux,  clResults;
cl::CommandQueue queue;
cl::Context context;
cl::Program program;
cl::Program::Sources sources;
cl::Device default_device;
std::vector<cl::Device> all_devices;
cl::Platform default_platform;
std::vector<cl::Platform> all_platforms;
int aux=0;
size_t max_workgroup_size, global_size;


int matchesGPU()
{
    cv::Mat tmpl = cv::imread("template");
    cv::Mat imageIn = cv::imread("image");

    if (tmpl.channels() == 3)
        cv::cvtColor(tmpl, tmpl, cv::COLOR_BGR2GRAY);
    if (imageIn.channels() == 3)
        cv::cvtColor(imageIn, imageIn, cv::COLOR_BGR2GRAY);

    initDevice();


    loadAndBuildProgram(KERNEL_FILE);

    cl_uchar* imageData = new cl_uchar[imageIn.cols * imageIn.rows];
    cl_uchar* templateData = new cl_uchar[tmpl.rows*tmpl.cols];

    loadDataMatToUchar(imageData, imageIn, 1);
    loadDataMatToUchar(templateData, tmpl, 1);

    result res;
    res.SAD = 10000;
    res.xpos=0;
    res.ypos=0;
    cl_short aux = 10000;

    time_start_GPU = chrono::high_resolution_clock::now();

    for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)
    {
        clInputImg=cl::Buffer(context,CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * imageIn.cols * imageIn.rows);
        clInputTemp=cl::Buffer(context,CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(unsigned char) * tmpl.rows * tmpl.cols);
        clInputVar=cl::Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(result));
        clInputAux=cl::Buffer(context,CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_short));

        // Kernels
        int iclError = 0;
        clkProcess=cl::Kernel(program, KERNEL_NAME, &iclError );

        if (iclError != 0 )
        {
            cout<<"iclError"<<endl;
            return -1;
        }
        // Send Data
        queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * imageIn.cols * imageIn.rows, &imageData[0]);
        queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * tmpl.rows * tmpl.cols, &templateData[0]);
        queue.enqueueWriteBuffer(clInputVar, CL_TRUE, 0,  sizeof(result), &res);
        queue.enqueueWriteBuffer(clInputAux, CL_TRUE, 0,  sizeof(cl_short), &aux);


        //--- Init Kernel arguments ---------------------------------------------------
        clkProcess.setArg(0,clInputImg);
        clkProcess.setArg(1,clInputTemp);
        clkProcess.setArg(2,clInputVar);

        clkProcess.setArg(3,(int)imageIn.cols);
        clkProcess.setArg(4,(int)imageIn.rows);
        clkProcess.setArg(5,(int)tmpl.cols);
        clkProcess.setArg(6,(int)tmpl.rows);
        clkProcess.setArg(7,clInputAux);

        // Image 2D
        cl::NDRange gRM=cl::NDRange((imageIn.cols - tmpl.cols), (imageIn.rows - tmpl.rows));

        queue.enqueueNDRangeKernel(
                    clkProcess,
                    cl::NullRange,
                    gRM,
                    cl::NullRange
                    );
        queue.finish();
        queue.enqueueReadBuffer(clInputAux, CL_TRUE,0, sizeof(cl_short),&aux);
        queue.enqueueReadBuffer(clInputVar, CL_TRUE,0, sizeof(result),&res);


    }//End -- for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)

    time_end_GPU = chrono::high_resolution_clock::now();

    delete[] imageData;
    delete[] templateData;

    string mm;
    switch (match_method)
    {
        case matchMetod::TM_CCOEFF:
        {
            mm = "TM_CCOEFF";break;
        }
        case matchMetod::TM_CCOEFF_NORMED:
        {
            mm = "TM_CCOEFF_NORMED";break;
        }
        case matchMetod::TM_CCORR:
        {
            mm = "TM_CCORR";break;
        }
        case matchMetod::TM_CCORR_NORMED:
        {
            mm = "TM_CCORR_NORMED";break;
        }
        case matchMetod::TM_SQDIFF:
        {
            mm = "TM_SQDIFF";break;
        }
        case matchMetod::TM_SQDIFF_NORMED:
        {
            mm = "TM_SQDIFF_NORMED";break;
        }
    }

    auto time_matching_OpenCV = std::chrono::duration_cast<chrono::microseconds>(time_end_OpenCV - time_start_OpenCV);
    printf("\nTime matching OpenCV  \t\t\t%.2f ms (%s)\n", (float)time_matching_OpenCV.count()/1000, mm.c_str());

    auto time_matching_GPU = std::chrono::duration_cast<chrono::microseconds>(time_end_GPU - time_start_GPU);
    printf("Time matching GPU  \t\t\t%.2f ms \n", (float)time_matching_GPU.count()/(1000 * NUM_ITERATIONS_GPU));

    cv::cvtColor(imageIn,imageIn,cv::COLOR_GRAY2BGR);
    cv::rectangle(imageIn, cv::Point(res.xpos, res.ypos), cv::Point(res.xpos+tmpl.cols, res.ypos+tmpl.rows),cv::Scalar(0,0,255),3);
    const char* parallel_window = "Parallel matching";
    namedWindow( parallel_window, WINDOW_AUTOSIZE );
    moveWindow(parallel_window, 900,450);
    imshow(parallel_window, imageIn);

    cout<<"\nPosition"<<", x: "<<res.xpos<<", y: "<<res.ypos<<"\n";
    cv::waitKey(-1);

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
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

    //get default device of the default platform

    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        return -1;
    }
    default_device=cl::Device(all_devices[0]);
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

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
