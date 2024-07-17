#include <CL/cl.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "main.hpp"

#define PROGRAM_NAME "matching.cl"
#define KERNEL_NAME "matching"

result res;
cl_uint aux = 1000000;

using namespace cv;
using namespace std;

size_t align(int x, int y)
{
    return (x + y - 1) / y * y;
}


cl_device_id create_device()
{
    cl_platform_id platform;
    cl_device_id dev;
    cl_int err = 0;
    err |= clGetPlatformIDs(1, &platform, NULL);
    err |= clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
    if (err == CL_DEVICE_NOT_FOUND) {
        err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
    }
    if (err) throw;
    return dev;
}

std::string get_program_text()
{
    std::ifstream t(PROGRAM_NAME);
    return std::string((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
}

cl_program build_program(cl_context ctx, cl_device_id dev)
{
    int err;

    std::string src = get_program_text();
    const char* src_text = src.data();
    size_t src_length = src.size();
    cl_program program = clCreateProgramWithSource(ctx, 1, &src_text, &src_length, &err);
    err |= clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    if (err != 0) cout <<"error build"<<endl;
    // тут желательно получить лог компиляции через clGetProgramBuildInfo
    if (err) throw;

    return program;
}

int matchesGPU()
{
    cl_mem imageBuff;
    cl_mem templateBuff;


    cv::Mat tmpl = cv::imread("template");
    cv::Mat imageIn = cv::imread("image");

    if (tmpl.channels() == 3)
        cv::cvtColor(tmpl, tmpl, cv::COLOR_BGR2GRAY);
    if (imageIn.channels() == 3)
        cv::cvtColor(imageIn, imageIn, cv::COLOR_BGR2GRAY);

    uchar* imageData = new uchar[imageIn.cols * imageIn.rows];
    uchar* templateData = new uchar[tmpl.rows*tmpl.cols];

    loadDataMatToUchar(imageData, imageIn, 1);
    loadDataMatToUchar(templateData, tmpl, 1);

    res.SAD = 100000000;
    res.xpos=0;
    res.ypos=0;

    cl_int err;
    cl_device_id device = create_device();
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

    cl_program program = build_program(context, device);
    cl_kernel kernel = clCreateKernel(program, KERNEL_NAME, &err);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);

    imageBuff = clCreateBuffer(context,
                                CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                sizeof(int) * imageIn.cols * imageIn.rows,
                                imageData,
                                &err);

    templateBuff = clCreateBuffer(context,
                                CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                sizeof(int) * tmpl.cols * tmpl.rows,
                                templateData,
                                &err);

    cl_mem resultBuff = clCreateBuffer(context,
                                CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
                                sizeof(result),
                                &res,
                                &err);

    cl_mem auxBuff = clCreateBuffer(context,
                                CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                                sizeof(cl_uint),
                                &aux,
                                &err);

    err |= clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&imageBuff);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&templateBuff);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&resultBuff);
    err |= clSetKernelArg(kernel, 3, sizeof(int) , (void*)&imageIn.cols);
    err |= clSetKernelArg(kernel, 4, sizeof(int), (void*)&imageIn.rows);
    err |= clSetKernelArg(kernel, 5, sizeof(int), (void*)&tmpl.cols);
    err |= clSetKernelArg(kernel, 6, sizeof(int), (void*)&tmpl.rows);
    err |= clSetKernelArg(kernel, 7, sizeof(cl_mem), (void*)&auxBuff);

    size_t local_size[2] = { 256, 1 };

    size_t global_size[2] = { align(imageIn.cols, local_size[0]), align(imageIn.rows, local_size[1]) };

    // запускаем двумерную задачу
    err |= clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global_size, local_size, 0, NULL, NULL);

    // читаем результат
    err |= clEnqueueReadBuffer(queue, resultBuff, CL_TRUE, 0, sizeof(result), &res, 0, NULL, NULL);
    err |= clEnqueueReadBuffer(queue, auxBuff, CL_TRUE, 0, sizeof(int), &aux, 0, NULL, NULL);

    // ждём завершения всех операций
    clFinish(queue);

    if (err != 0) cout <<"error..."<<endl;
    cout<<"\nPosition"<<", x: "<<res.xpos<<", y: "<<res.ypos<<"\n";

    waitKey(0);

    /* Deallocate resources */
    clReleaseKernel(kernel);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);
    clReleaseMemObject(imageBuff);
    clReleaseMemObject(templateBuff);
    clReleaseMemObject(resultBuff);
    clReleaseMemObject(auxBuff);
    delete[] imageData;
    delete[] templateData;


    return 0;
}
