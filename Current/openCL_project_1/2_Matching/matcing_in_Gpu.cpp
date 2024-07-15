#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
#include <fstream>
#include "templateMatch.h"

extern int const match_method;
extern bool enable_Serial_stop_after_find_zero;
using namespace std;
using namespace cv;


std::string kernel_source;
chrono::high_resolution_clock::time_point
    time_start_Serial, time_end_Serial,
    time_start_OpenCV, time_end_OpenCV,
    time_start_GPU, time_end_GPU;
    bool endSerial = false; // При нахождении полного соответствия

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
    if ( loadKernelFile(programFile) != 0)
    {
        cout<<"loadKernelFile error"<<endl;
          return -1;
    }
    else
    {
//        cout<<"loadKernelFile OK"<<endl;
    }

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


int matchesGPU()
{
    cv::Mat tmpl = cv::imread("template");

    cv::Mat imageIn = cv::imread("image");

    if (tmpl.channels() == 3)
        cv::cvtColor(tmpl, tmpl, cv::COLOR_BGR2GRAY);

    if (imageIn.channels() == 3)
        cv::cvtColor(imageIn, imageIn, cv::COLOR_BGR2GRAY);

    TemplateMatch tmM(imageIn);

    initDevice();

    // kernel
    loadAndBuildProgram("kernel");

    uchar* imageData = new uchar[tmM.WIDTH*tmM.HEIGHT];
    uchar* templateData = new uchar[tmpl.rows*tmpl.cols];

    loadDataMatToUchar(imageData,tmM.imageIn,1);
    loadDataMatToUchar(templateData, tmpl,1);

    result r_GPU;

    time_start_GPU = chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)
    {

        // Data
        result res;
        res.SAD = 100000000;
        res.xpos=0;
        res.ypos=0;
        int w = tmM.WIDTH;
        int h = tmM.HEIGHT;

        uint aux = 1000000;

        clInputImg=cl::Buffer(context,CL_MEM_READ_ONLY,sizeof(unsigned char) * w * h);
        clInputTemp=cl::Buffer(context,CL_MEM_READ_ONLY,sizeof(unsigned char) * tmpl.rows * tmpl.cols);
        clInputVar=cl::Buffer(context,CL_MEM_WRITE_ONLY,sizeof(result));
        clInputAux=cl::Buffer(context,CL_MEM_READ_WRITE,sizeof(int));

        // Kernels
        int iclError = 0;

        clkProcess=cl::Kernel(program,"matching", &iclError );

        if (iclError != 0 )
        {
            cout<<"iclError"<<endl;
            return -1;
        }
        // Send Data
        iclError = queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * w * h, &imageData[0]);
        iclError = queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * tmpl.rows * tmpl.cols, &templateData[0]);
        iclError = queue.enqueueWriteBuffer(clInputVar, CL_TRUE, 0,  sizeof(result), &res);
        iclError = queue.enqueueWriteBuffer(clInputAux, CL_TRUE, 0,  sizeof(int), &aux);


        //--- Init Kernel arguments ---------------------------------------------------
        iclError |= clkProcess.setArg(0,clInputImg);
        iclError |= clkProcess.setArg(1,clInputTemp);
        iclError |= clkProcess.setArg(2,clInputVar);

        iclError |= clkProcess.setArg(3,(int)w);
        iclError |= clkProcess.setArg(4,(int)h);
        iclError |= clkProcess.setArg(5,(int)tmpl.cols);
        iclError |= clkProcess.setArg(6,(int)tmpl.rows);
        iclError |= clkProcess.setArg(7,clInputAux);
    //    iclError |= clkProcess.setArg(8,clResults);

        // Image 1D
        //cl::NDRange gRM=cl::NDRange((w-t_cols)*(h-t_rows));
        //cl::NDRange lRW=cl::NDRange(localWGrp);

        // Image 2D
        cl::NDRange gRM=cl::NDRange((w-tmpl.cols),(h-tmpl.rows));
        //El work group dejo que lo asigne automaticamente

        cl::Event event;

        iclError |= queue.enqueueNDRangeKernel(
                    clkProcess,
                    cl::NullRange,
                    gRM,
                    cl::NullRange,
                    NULL,
                    &event
                    );

        event.wait();

        iclError |= queue.finish();

        queue.enqueueReadBuffer(clInputAux, CL_TRUE,0, sizeof(int),&aux);
        queue.enqueueReadBuffer(clInputVar, CL_TRUE,0, sizeof(result),&res);

    }
    time_end_GPU = chrono::high_resolution_clock::now();

    delete[] imageData;
    delete[] templateData;

//    print_results();

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
    printf("Time matching GPU  \t\t\t%.2f ms \n", (float)time_matching_GPU.count()/(1000*NUM_ITERATIONS_GPU));

    cv::cvtColor(imageIn,imageIn,cv::COLOR_GRAY2BGR);
    cv::rectangle(imageIn, cv::Point(r_GPU.xpos, r_GPU.ypos), cv::Point(r_GPU.xpos+tmpl.cols, r_GPU.ypos+tmpl.rows),cv::Scalar(0,0,255),3);
    const char* parallel_window = "Parallel matching";
    namedWindow( parallel_window, WINDOW_AUTOSIZE );
    moveWindow(parallel_window, 900,450);
    imshow(parallel_window, imageIn);

    cout<<"\nPosition"<<", x: "<<r_GPU.xpos<<", y: "<<r_GPU.ypos<<"\n";
    cv::waitKey(-1);

return 0;
}


