#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"

extern QElapsedTimer eTimer;
extern quint64 timeParallel;

int parallelMatches(QImage &imageIn, QImage &imageTempl, QImage &imageOut)
{










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
