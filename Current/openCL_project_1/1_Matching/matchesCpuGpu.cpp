#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
#include <fstream>
#include "templateMatch.h"

extern int const match_method;

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
cl::Buffer clInputImg, clInputTemp, clInputVar, clInputAux;
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

int gpuProcess(TemplateMatch tmM, cv::Mat _template, int t_rows, int t_cols, uchar* imageData, uchar* templateData, result & r)
{

    // Data
    result res;
    res.SAD = 100000000;
    res.xpos=0;
    res.ypos=0;
    int w = tmM.WIDTH;
    int h = tmM.HEIGHT;

    uint aux = 1000000;


    clInputImg=cl::Buffer(context,CL_MEM_READ_ONLY,sizeof(unsigned char)*w*h);
    clInputTemp=cl::Buffer(context,CL_MEM_READ_ONLY,sizeof(unsigned char)*t_rows*t_cols);
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
    iclError = queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * t_rows * t_cols, &templateData[0]);
    iclError = queue.enqueueWriteBuffer(clInputVar, CL_TRUE, 0,  sizeof(result), &res);
    iclError = queue.enqueueWriteBuffer(clInputAux, CL_TRUE, 0,  sizeof(int), &aux);

    //--- Init Kernel arguments ---------------------------------------------------
    iclError |= clkProcess.setArg(0,clInputImg);
    iclError |= clkProcess.setArg(1,clInputTemp);
    iclError |= clkProcess.setArg(2,clInputVar);

    iclError |= clkProcess.setArg(3,(int)w);
    iclError |= clkProcess.setArg(4,(int)h);
    iclError |= clkProcess.setArg(5,(int)t_cols);
    iclError |= clkProcess.setArg(6,(int)t_rows);
    iclError |= clkProcess.setArg(7,clInputAux);


    // Image 1D
    //cl::NDRange gRM=cl::NDRange((w-t_cols)*(h-t_rows));
    //cl::NDRange lRW=cl::NDRange(localWGrp);

    // Image 2D
    cl::NDRange gRM=cl::NDRange((w-t_cols),(h-t_rows));
    //El work group dejo que lo asigne automaticamente


    iclError |= queue.enqueueNDRangeKernel(clkProcess,cl::NullRange,gRM,cl::NullRange);
    iclError |= queue.finish();

    queue.enqueueReadBuffer(clInputAux, CL_TRUE,0, sizeof(int),&aux);
    queue.enqueueReadBuffer(clInputVar, CL_TRUE,0, sizeof(result),&res);

    r=res;

    return 0;
}

result TemplateMatch::matchesCPU(cv::Mat _template, int t_rows, int t_cols)
{

    uchar* imageData = new uchar[imageIn.cols * imageIn.rows];
    uchar* templateData = new uchar[_template.cols * _template.rows];

    int outW = WIDTH - t_cols + 1;
    int outH = HEIGHT - t_rows + 1;

    cout <<"outW "<<outW<<" outH "<<outW<<endl;
    uchar* outData = new uchar[outW * outH];

    result res;
    res.SAD = 100000000;
    WIDTH = imageIn.cols;
    HEIGHT = imageIn.rows;


    loadDataMatToUchar(imageData,imageIn,1);
    loadDataMatToUchar(templateData,_template,1);

    time_start_Serial = chrono::high_resolution_clock::now();

// loop through the search image

    for ( int y = 0; y <= HEIGHT - t_rows; y++ )
    {
        if (endSerial)
            break;
        for ( int x =0; x <= WIDTH - t_cols; x++ )
        {
           float SAD = 0.0;

        // loop through the template image
            for ( int y1 = 0; y1 < t_rows; y1++ )
            {
                for ( int x1 = 0; x1 < t_cols; x1++ )
                {
                    int p_SearchIMG = imageData[(y+y1) * WIDTH + (x+x1)];
                    int p_TemplateIMG = templateData[y1 *  t_cols + x1];
                    SAD += abs( p_SearchIMG - p_TemplateIMG );
                }
            }

            outData[y * outW + x] = SAD;

            // save the best found position
            if ( SAD == 0)
            {
                endSerial = true;
                res.SAD = SAD;
                res.xpos = x;
                res.ypos = y;
                std::cout<< " x "<< x <<" y "<<y << " SAD "<< SAD << "\n";
            }

            if ( !endSerial && res.SAD > SAD )
            {
                res.SAD = SAD;
                // give me min SAD
                res.xpos = x;
                res.ypos = y;
                std::cout<< " x "<< x <<" y "<<y << " SAD "<< SAD << "\n";
            }
        }//END -- for ( int x =0; x <= WIDTH - t_cols; x++ )
    }//END -- for ( int y = 0; y <= HEIGHT - t_rows; y++ )
    time_end_Serial = chrono::high_resolution_clock::now();

    cv::Mat outImg;
    ucharToMat(outData, outImg);

//    cv::imshow("Serial result", outImg);
//    cv::waitKey(-1);
//    outImg.release();



    delete[] imageData;
    delete[] templateData;
    delete[] outData;
    return res;
}

int matches()
{
    cv::Mat tmpl = cv::imread("template");
    if (tmpl.rows == 0)
    {
        std::cout<< "template  error \n";
        return -1;
    }

    cv::Mat imageIn = cv::imread("image");
    if (imageIn.rows == 0)
    {
        std::cout<< "image  error \n";
        return -1;
    }

    if (tmpl.channels() == 3)
        cv::cvtColor(tmpl, tmpl, cv::COLOR_BGR2GRAY);

    if (imageIn.channels() == 3)
        cv::cvtColor(imageIn, imageIn, cv::COLOR_BGR2GRAY);

    TemplateMatch tmM(imageIn);

    //Time matching CPU
    tmM.matchesCPU(tmpl, tmpl.rows, tmpl.cols);

//Time matching GPU
    if (initDevice() < 0 )
    {
        cout<<"initDevice error"<<endl;
          return -1;
    }
    else
    {
//        cout<<"initDevice OK"<<endl;
    }

    // kernel
    if ( loadAndBuildProgram("kernel") < 0)
    {
        cout<<"load and Build error"<<endl;
          return -1;
    }
    else
    {
//        cout<<"load and Build OK"<<endl;
    }



    uchar* imageData = new uchar[tmM.WIDTH*tmM.HEIGHT];
    uchar* templateData = new uchar[tmpl.rows*tmpl.cols];

    loadDataMatToUchar(imageData,tmM.imageIn,1);
    loadDataMatToUchar(templateData, tmpl,1);

    time_start_GPU = chrono::high_resolution_clock::now();
    result r_GPU;
for (int i = 0; i < NUM_ITERATIONS_GPU; ++i)
{
    int retGpu = gpuProcess(tmM, tmpl, tmpl.rows, tmpl.cols, imageData, templateData, r_GPU);
    if (retGpu != 0)
    {
        cout<<"error gpuProcess "<< retGpu <<endl;
        return -1;
    }
}

    delete[] imageData;
    delete[] templateData;

    time_end_GPU = chrono::high_resolution_clock::now();

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
            mm = "TM_CCOEFF";break;
        }
        case matchMetod::TM_SQDIFF:
        {
            mm = "TM_CCOEFF_NORMED";break;
        }
        case matchMetod::TM_SQDIFF_NORMED:
        {
            mm = "TM_CCORR";break;
        }
    }


    auto time_matching_CPU = std::chrono::duration_cast<chrono::microseconds>(time_end_Serial - time_start_Serial);
    if (endSerial)
        printf("\nTime matching CPU(full natching)  \t%.2f ms ", (float)time_matching_CPU.count()/1000);
    if (!endSerial)
        printf("\nTime matching CPU  \t\t%.2f ms ", (float)time_matching_CPU.count()/1000);
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


