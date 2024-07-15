#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
#include <fstream>
#include <iostream>

extern int match_method;
using namespace std;
using namespace cv;

int initDevice();
int loadAndBuildProgram(std::string programFile);

std::string kernel_source;
chrono::high_resolution_clock::time_point time_start_GPU, time_end_GPU;
extern chrono::high_resolution_clock::time_point time_start_OpenCV, time_end_OpenCV;
cl::Kernel clkProcess;
cl::Buffer InputImg, InputTemp, Result, Aux, min_SAD_in_group;
cl::CommandQueue queue;
cl::Context context;
cl::Program program;
cl::Program::Sources sources;
cl::Device default_device;
std::vector<cl::Device> all_devices;
cl::Platform default_platform;
std::vector<cl::Platform> all_platforms;
int aux=0;
cl_uint global_size, local_size;


int matchesGPU()
{
    cv::Mat tmpl = cv::imread("template");
    cv::Mat imageIn = cv::imread("image");

    if (tmpl.channels() == 3)
        cv::cvtColor(tmpl, tmpl, cv::COLOR_BGR2GRAY);
    if (imageIn.channels() == 3)
        cv::cvtColor(imageIn, imageIn, cv::COLOR_BGR2GRAY);

    initDevice();

    global_size = (imageIn.rows - tmpl.rows)*(imageIn.cols - tmpl.cols);
    local_size = WORKGROUPSIZE_MAX;

    loadAndBuildProgram("kernel");

    uchar* imageData = new uchar[imageIn.cols * imageIn.rows];
    uchar* templateData = new uchar[tmpl.rows*tmpl.cols];
    uchar* min_SAD_in_groupData = new uchar[global_size / local_size];
    loadDataMatToUchar(imageData, imageIn, 1);
    loadDataMatToUchar(templateData, tmpl, 1);

    result res;
    res.SAD = 100000000;
    res.xpos=0;
    res.ypos=0;
    uint aux = 1000000;

    time_start_GPU = chrono::high_resolution_clock::now();
//    for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)
//    {
        InputImg=cl::Buffer(context,CL_MEM_READ_ONLY,sizeof(unsigned char) * imageIn.cols * imageIn.rows);
        InputTemp=cl::Buffer(context,CL_MEM_READ_ONLY,sizeof(unsigned char) * tmpl.rows * tmpl.cols);
        Result=cl::Buffer(context,CL_MEM_WRITE_ONLY,sizeof(result));
        Aux=cl::Buffer(context,CL_MEM_READ_WRITE,sizeof(int));
        min_SAD_in_group=cl::Buffer(context,CL_MEM_WRITE_ONLY,sizeof(uchar) * (global_size / local_size));

        // Kernels
        int iclError = 0;
        clkProcess=cl::Kernel(program,"matching", &iclError );

        if (iclError != 0 )
        {
            cout<<"iclError"<<endl;
            return -1;
        }
        // Send Data
        queue.enqueueWriteBuffer(InputImg, CL_TRUE, 0,  sizeof(unsigned char) * imageIn.cols * imageIn.rows, &imageData[0]);
        queue.enqueueWriteBuffer(InputTemp, CL_TRUE, 0,  sizeof(unsigned char) * tmpl.rows * tmpl.cols, &templateData[0]);
        queue.enqueueWriteBuffer(Result, CL_TRUE, 0,  sizeof(result), &res);
        queue.enqueueWriteBuffer(Aux, CL_TRUE, 0,  sizeof(int), &aux);
        queue.enqueueWriteBuffer(min_SAD_in_group, CL_TRUE, 0,  sizeof(uchar)* (global_size / local_size), &min_SAD_in_groupData[0]);

        //--- Init Kernel arguments ---------------------------------------------------
        clkProcess.setArg(0,InputImg);
        clkProcess.setArg(1,InputTemp);
        clkProcess.setArg(2,Result);

        clkProcess.setArg(3,(int)imageIn.cols);
        clkProcess.setArg(4,(int)imageIn.rows);
        clkProcess.setArg(5,(int)tmpl.cols);
        clkProcess.setArg(6,(int)tmpl.rows);
        clkProcess.setArg(7,Aux);
        clkProcess.setArg(8,min_SAD_in_group);

        // Image 2D
        cl::NDRange gRM=cl::NDRange((imageIn.cols - tmpl.cols), (imageIn.rows - tmpl.rows));

        queue.enqueueNDRangeKernel(
                    clkProcess,
                    cl::NullRange,
                    gRM,
                    cl::NullRange
                    );

        queue.finish();

        queue.enqueueReadBuffer(Aux, CL_TRUE,0, sizeof(int),&aux);
        queue.enqueueReadBuffer(Result, CL_TRUE,0, sizeof(result),&res);

//    }//End -- for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)
    time_end_GPU = chrono::high_resolution_clock::now();

    delete[] imageData;
    delete[] templateData;
    delete[] min_SAD_in_groupData;

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
    printf("Time matching GPU  \t\t\t%.2f ms \n", (float)time_matching_GPU.count()/(1000 /** NUM_ITERATIONS_GPU*/));

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
