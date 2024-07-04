#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
#include <fstream>
#include "templateMatch.h"

extern QElapsedTimer eTimer;
extern quint64 timeParallel;

using namespace std;

std::string kernel_source;

void loadKernelFile(std::string program)
{
    if (ifstream(program.c_str()))
    {
        std::ifstream infile;
        infile.open(program.c_str(), std::ifstream::in);
        char c = infile.get();
        while (!infile.eof())
        {
            kernel_source.push_back(c);
            c = infile.get();
        }
        infile.close();
    }
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
clock_t timeCPU;
clock_t timeGPU;
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

int gpuProcess(TemplateMatch tmM, cv::Mat _template, int t_rows, int t_cols, result & r)
{
    if (initDevice() < 0 )
          return -1;
    // kernel
    if ( loadAndBuildProgram("Lab4.cl") < 0)
         return -1;

    // Data
    result res;
    res.SAD = 100000000;
    res.xpos=0;
    res.ypos=0;
    int w = tmM.WIDTH;
    int h = tmM.HEIGHT;

    int aux=10000000;

    uchar* imageData = new uchar[w*h];
    uchar* templateData = new uchar[t_rows*t_cols];

    timeGPU = clock();    //start timer

    loadDataMatToUchar(imageData,tmM.image,1);
    loadDataMatToUchar(templateData,_template,1);

    clInputImg=cl::Buffer(context,CL_MEM_READ_WRITE,sizeof(unsigned char)*w*h);
    clInputTemp=cl::Buffer(context,CL_MEM_READ_WRITE,sizeof(unsigned char)*t_rows*t_cols);
    clInputVar=cl::Buffer(context,CL_MEM_READ_WRITE,sizeof(result));
    clInputAux=cl::Buffer(context,CL_MEM_READ_WRITE,sizeof(int));

    // Kernels
    int iclError = 0;

    clkProcess=cl::Kernel(program,"matching", &iclError );

    if (iclError != 0 )
    {
        delete[] imageData;
        delete[] templateData;
        return -1;
    }
    // Send Data
    iclError = queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char)*w*h, &imageData[0]);
    iclError = queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char)*t_rows*t_cols, &templateData[0]);
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




int parallelMatches(QImage &imageIn, QImage &imageTempl, QImage &imageOut)
{
    cv::Mat tmpl = cv::imread("template");
    if (tmpl.rows == 0)
    {
        std::cout<< "template.jpg  error \n";
        return -1;
    }

    cv::Mat image = cv::imread("image");
    if (image.rows == 0)
    {
        std::cout<< "image.jpg  error \n";
        return -1;
    }

    if (tmpl.channels() == 3)
        cv::cvtColor(tmpl, tmpl, cv::COLOR_BGR2GRAY);

    if (image.channels() == 3)
        cv::cvtColor(image,image,cv::COLOR_BGR2GRAY);

    cv::imshow("Result", image);

    TemplateMatch tmM(image);
    result r;

    timeCPU = clock();    //start timer
    r = tmM.check(tmpl, tmpl.rows, tmpl.cols);
    timeCPU = clock() - timeCPU;

    gpuProcess(tmM, tmpl, tmpl.rows, tmpl.cols,r);
    timeGPU = clock() - timeGPU;


    double time_matchingCPU = ((double)timeCPU)/*/CLOCKS_PER_SEC*/;
    double time_matchingGPU = ((double)timeGPU)/*/CLOCKS_PER_SEC*/;

    printf("\nTime matching CPU = %.3f ms \n", time_matchingCPU/1000);
    printf("Time matching GPU = %.3f ms \n", time_matchingGPU/1000);
    printf("Time matching CPU / Time matching GPU  = %.d \n\n"
           "", (int)(time_matchingCPU/time_matchingGPU));
    cv::cvtColor(image,image,cv::COLOR_GRAY2BGR);

    cv::rectangle(image,cv::Point(r.xpos, r.ypos), cv::Point(r.xpos+tmpl.cols, r.ypos+tmpl.rows),cv::Scalar(0,0,255),3);

    cv::imshow("Result", image);

    cout<<"Position"<<", x: "<<r.xpos<<", y: "<<r.ypos<<"\n";
    cv::waitKey(-1);


return 0;
}





// Этот код не работает
//inline void calculateNDRange(int size, int groupSize,
//                             int *bSize, int *bGroupSize, int *oSize)
//{
//    if (size <= groupSize)
//        groupSize = 1 << int(log(size) / log(2));
//    else
//        groupSize = 1 << int(log(groupSize) / log(2));

//    if (size % groupSize)
//        size = size + groupSize - size % groupSize;

//    *bSize = size;
//    *bGroupSize = groupSize;
//    *oSize = size / groupSize;
//}

//int workParallelMatches(QImage &imageIn, QImage &imageOut)
//{
//    // Query platforms
//    VECTOR_CLASS<cl::Platform> platforms;

//    if (cl::Platform::get(&platforms) != CL_SUCCESS)
//    {
//        qDebug() << "Cann't query platforms";
//        return -1;
//    }

//    if (platforms.size() < 1)
//    {
//        qDebug() << "No platforms available";
//        return -1;
//    }

//    // Query devices
//    cl::Platform platform = platforms[0];
//    VECTOR_CLASS<cl::Device> devices;

//    if (platform.getDevices(CL_DEVICE_TYPE_ALL, &devices) != CL_SUCCESS)
//    {
//        qDebug() << "No devices available";
//        return -1;
//    }

//    // Create OpenCL context
//    cl::Context context(devices);

//    // Load OpenCL program
//    QFile kernelFile("matches.cl");
//    kernelFile.open(QIODevice::ReadOnly | QIODevice::Text);
//    cl::Program program(context, kernelFile.readAll().toStdString());
//    kernelFile.close();

//    // Compile kernels
//    cl_int error = program.build();

//    if (error != CL_SUCCESS)
//    {
//        cl::STRING_CLASS buildLog;
//        program.getBuildInfo(devices[0], CL_PROGRAM_BUILD_LOG, &buildLog);
//        qDebug() << buildLog.c_str();
//        return -1;
//    }

//    imageIn = imageIn.convertToFormat(QImage::Format_RGBA8888);
//    cl::CommandQueue commandQueue(context, devices[0]);
//    // Obtain a reference to the kernel
//    cl::make_kernel<cl::Image2D &, cl::Image2D &> matches(program, "matches");

//    // Create image buffers
//    cl::Image2D clImageIn(context,
//                          CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
//                          cl::ImageFormat(CL_RGBA, CL_UNSIGNED_INT8),
//                          imageIn.width(),
//                          imageIn.height(),
//                          imageIn.bytesPerLine(),
//                          imageIn.bits());

//    cl::Image2D clImageOut(context,
//                           CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
//                           cl::ImageFormat(CL_RGBA, CL_UNSIGNED_INT8),
//                           imageOut.width(),
//                           imageOut.height(),
//                           imageOut.bytesPerLine(),
//                           imageOut.bits());

//    eTimer.restart();

//    int rangeX;
//    int rangeY;
//    int groupSizeX;
//    int groupSizeY;
//    int oSize;

//    // Calgulate range values
//    calculateNDRange(imageIn.width(), WORKGROUPSIZE,
//                     &rangeX, &groupSizeX, &oSize);

//    calculateNDRange(imageIn.height(), WORKGROUPSIZE,
//                     &rangeY, &groupSizeY, &oSize);

//    // Apply kernel
//    matches(cl::EnqueueArgs(commandQueue,
//                          cl::NDRange(0, 0),
//                          cl::NDRange(rangeX, rangeY),
//                          cl::NDRange(groupSizeX, groupSizeY)),
//          clImageIn, clImageOut);




//    cl::size_t<3> origin;
//    origin[0] = 0;
//    origin[1] = 0;
//    origin[2] = 0;

//    cl::size_t<3> region;
//    region[0] = imageOut.width();
//    region[1] = imageOut.height();
//    region[2] = 1;

//    // Retrieve output image
//    commandQueue.enqueueReadImage(clImageOut, CL_TRUE, origin, region, 0, 0, imageOut.bits());

//    timeParallel = eTimer.nsecsElapsed();
//    imageOut.save("matches-paralell.png");
//    return 0;
//}
