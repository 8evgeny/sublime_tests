//#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include <string>
#include <sstream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "PNG.h"

std::string readFile(std::string fileName)
{
    std::ifstream t(fileName);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}

int main(int arg, char* args[])
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.size() == 0)
    {
        std::cout << "No OpenCL platforms found" << std::endl;//This means you do not have an OpenCL compatible platform on your system.
        exit(1);
    }
    std::vector<cl::Device> devices;
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);
    cl::Device device = devices[0];
    std::cout << "Using device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    std::cout << "Using platform: " << platforms[0].getInfo<CL_PLATFORM_NAME>() << std::endl;
    cl::Context context(device);

    //load our image
    PNG inPng("image");

    //store width and height so we can use them for our output image later
    const unsigned int w = inPng.w;
    const unsigned int h = inPng.h;

    //input image
    const cl::ImageFormat format(CL_RGBA, CL_UNSIGNED_INT8);
    cl::Image2D in(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, format, w, h, 0, &inPng.data[0]);

    //we are done with the image so free up its memory
    inPng.Free();

    //output image
    cl::Image2D out(context, CL_MEM_WRITE_ONLY, format, w, h, 0, NULL);

    cl::Program::Sources sources;
    std::string kernel_code = readFile("kernel");
    //Add your program source
    sources.push_back({ kernel_code.c_str(),kernel_code.length() });

    //Create your OpenCL program and build it.
    cl::Program program(context, sources);
    if (program.build({ device }) != CL_SUCCESS)
    {
        std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;//print the build log to find any issues with your source
        exit(1);//Quit if your program doesn't compile
    }

    //set the kernel arguments
    cl::Kernel kernelCopy(program, "copy");
    kernelCopy.setArg(0, in);
    kernelCopy.setArg(1, out);

    //create command queue
    cl::CommandQueue queue(context, device, 0, NULL);

    //execute kernel
    queue.enqueueNDRangeKernel(kernelCopy, cl::NullRange, cl::NDRange(w, h), cl::NullRange);

    //wait for kernel to finish
    queue.finish();

    //start and end coordinates for reading our image (I really do not like how the c++ wrapper does this)
    cl::size_t<3> origin;
    cl::size_t<3> size;
    origin[0] = 0;
    origin[1] = 0;
    origin[2] = 0;
    size[0] = w;
    size[1] = h;
    size[2] = 1;

    //output png
    PNG outPng;
    //create the image with the same width and height as original
    outPng.Create(w, h);

    //temporary array to store the result from opencl
    auto tmp = new unsigned char[w * h * 4];
    //CL_TRUE means that it waits for the entire image to be copied before continuing
    queue.enqueueReadImage(out, CL_TRUE, origin, size, 0, 0, tmp);

    //copy the data from the temp array to the png
    std::copy(&tmp[0], &tmp[w * h * 4], std::back_inserter(outPng.data));

    //write the image to file
    outPng.Save("output.png");
    //free the iamge's resources since we are done with it
    outPng.Free();

    cv::Mat image = cv::imread("output.png");
    cv::imshow("output.png", image);
    cv::waitKey(-1);
    image.release();


    //free the temp array
    delete[] tmp;

    return 0;
}



////
//// Book:      OpenCL(R) Programming Guide
//// Authors:   Aaftab Munshi, Benedict Gaster, Timothy Mattson, James Fung, Dan Ginsburg
//// ISBN-10:   0-321-74964-2
//// ISBN-13:   978-0-321-74964-2
//// Publisher: Addison-Wesley Professional
//// URLs:      http://safari.informit.com/9780132488006/
////            http://www.openclprogrammingguide.com
////
 
//// ImageFilter2D.cpp
////
////    This example demonstrates performing gaussian filtering on a 2D image using
////    OpenCL
////
////    Requires FreeImage library for image I/O:
////      http://freeimage.sourceforge.net/
 
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string.h>
//#include <opencv.hpp>
 
//#ifdef __APPLE__
//#include <OpenCL/cl.h>
//#else
//#include <CL/cl.h>
//#endif
 
//#include "FreeImage.h"
 
/////
////  Create an OpenCL context on the first available platform using
////  either a GPU or CPU depending on what is available.
////
//cl_context CreateContext()
//{
//	cl_int errNum;
//	cl_uint numPlatforms;
//	cl_platform_id firstPlatformId;
//	cl_context context = NULL;
 
//	// First, select an OpenCL platform to run on.  For this example, we
//	// simply choose the first available platform.  Normally, you would
//	// query for all available platforms and select the most appropriate one.
//	errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
//	if (errNum != CL_SUCCESS || numPlatforms <= 0)
//	{
//		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
//		return NULL;
//	}
 
//	// Next, create an OpenCL context on the platform.  Attempt to
//	// create a GPU-based context, and if that fails, try to create
//	// a CPU-based context.
//	cl_context_properties contextProperties[] =
//	{
//		CL_CONTEXT_PLATFORM,
//		(cl_context_properties)firstPlatformId,
//		0
//	};
//	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU,
//		NULL, NULL, &errNum);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cout << "Could not create GPU context, trying CPU..." << std::endl;
//		context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
//			NULL, NULL, &errNum);
//		if (errNum != CL_SUCCESS)
//		{
//			std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
//			return NULL;
//		}
//	}
 
//	return context;
//}
 
/////
////  Create a command queue on the first device available on the
////  context
////
//cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device)
//{
//	cl_int errNum;
//	cl_device_id *devices;
//	cl_command_queue commandQueue = NULL;
//	size_t deviceBufferSize = -1;
 
//	// First get the size of the devices buffer
//	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &deviceBufferSize);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Failed call to clGetContextInfo(...,GL_CONTEXT_DEVICES,...)";
//		return NULL;
//	}
 
//	if (deviceBufferSize <= 0)
//	{
//		std::cerr << "No devices available.";
//		return NULL;
//	}
 
//	// Allocate memory for the devices buffer
//	devices = new cl_device_id[deviceBufferSize / sizeof(cl_device_id)];
//	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, devices, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Failed to get device IDs";
//		return NULL;
//	}
 
//	// In this example, we just choose the first available device.  In a
//	// real program, you would likely use all available devices or choose
//	// the highest performance device based on OpenCL device queries
//	commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
//	if (commandQueue == NULL)
//	{
//		std::cerr << "Failed to create commandQueue for device 0";
//		return NULL;
//	}
 
//	*device = devices[0];
//	delete[] devices;
//	return commandQueue;
//}
 
/////
////  Create an OpenCL program from the kernel source file
////
//cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName)
//{
//	cl_int errNum;
//	cl_program program;
 
//	std::ifstream kernelFile(fileName, std::ios::in);
//	if (!kernelFile.is_open())
//	{
//		std::cerr << "Failed to open file for reading: " << fileName << std::endl;
//		return NULL;
//	}
 
//	std::ostringstream oss;
//	oss << kernelFile.rdbuf();
 
//	std::string srcStdStr = oss.str();
//	const char *srcStr = srcStdStr.c_str();
//	program = clCreateProgramWithSource(context, 1,
//		(const char**)&srcStr,
//		NULL, NULL);
//	if (program == NULL)
//	{
//		std::cerr << "Failed to create CL program from source." << std::endl;
//		return NULL;
//	}
 
//	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		// Determine the reason for the error
//		char buildLog[16384];
//		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
//			sizeof(buildLog), buildLog, NULL);
 
//		std::cerr << "Error in kernel: " << std::endl;
//		std::cerr << buildLog;
//		clReleaseProgram(program);
//		return NULL;
//	}
 
//	return program;
//}
 
 
/////
////  Cleanup any created OpenCL resources
////
//void Cleanup(cl_context context, cl_command_queue commandQueue,
//	cl_program program, cl_kernel kernel, cl_mem imageObjects[2],
//	cl_sampler sampler)
//{
//	for (int i = 0; i < 2; i++)
//	{
//		if (imageObjects[i] != 0)
//			clReleaseMemObject(imageObjects[i]);
//	}
//	if (commandQueue != 0)
//		clReleaseCommandQueue(commandQueue);
 
//	if (kernel != 0)
//		clReleaseKernel(kernel);
 
//	if (program != 0)
//		clReleaseProgram(program);
 
//	if (sampler != 0)
//		clReleaseSampler(sampler);
 
//	if (context != 0)
//		clReleaseContext(context);
 
//}
 
/////
////  Load an image using the FreeImage library and create an OpenCL
////  image out of it
////
//cl_mem LoadImage(cl_context context, char *fileName, int &width, int &height)
//{
//	//FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName, 0);
//	//FIBITMAP* image = FreeImage_Load(format, fileName);
 
//	//// Convert to 32-bit image
//	//FIBITMAP* temp = image;
//	//image = FreeImage_ConvertTo32Bits(image);
//	//FreeImage_Unload(temp);
 
//	//width = FreeImage_GetWidth(image);
//	//height = FreeImage_GetHeight(image);
//	/*char *buffer = new char[width * height * 4];
//	memcpy(buffer, FreeImage_GetBits(image), width * height * 4);
//	FreeImage_Unload(image);*/
//	cv::Mat image1 = cv::imread(fileName);
//	width = image1.cols;
//	height = image1.rows;
//	char *buffer = new char[width * height * 4];
//	int w = 0;
//	for (int v = height - 1; v >= 0; v--)
//	{
//		for (int u = 0; u <width; u++)
//		{
//			buffer[w++] = image1.at<cv::Vec3b>(v, u)[0];
//			buffer[w++] = image1.at<cv::Vec3b>(v, u)[1];
//			buffer[w++] = image1.at<cv::Vec3b>(v, u)[2];
//			w++;
//		}
//	}
	
 
//	// Create OpenCL image
//	cl_image_format clImageFormat;
//	clImageFormat.image_channel_order = CL_RGBA;
//	clImageFormat.image_channel_data_type = CL_UNORM_INT8;
 
//	cl_int errNum;
//	cl_mem clImage;
//	clImage = clCreateImage2D(context,
//		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//		&clImageFormat,
//		width,
//		height,
//		0,
//		buffer,
//		&errNum);
 
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error creating CL image object" << std::endl;
//		return 0;
//	}
 
//	return clImage;
//}
 
/////
////  Save an image using the FreeImage library
////
//bool SaveImage(char *fileName, char *buffer, int width, int height)
//{
//	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(fileName);
//	FIBITMAP *image = FreeImage_ConvertFromRawBits((BYTE*)buffer, width,
//		height, width * 4, 32,
//		0xFF000000, 0x00FF0000, 0x0000FF00);
//	return FreeImage_Save(format, image, fileName);
//}
 
/////
////  Round up to the nearest multiple of the group size
////
//size_t RoundUp(int groupSize, int globalSize)
//{
//	int r = globalSize % groupSize;
//	if (r == 0)
//	{
//		return globalSize;
//	}
//	else
//	{
//		return globalSize + groupSize - r;
//	}
//}
 
/////
////	main() for HelloBinaryWorld example
////
//int main(int argc, char** argv)
//{
//	cl_context context = 0;
//	cl_command_queue commandQueue = 0;
//	cl_program program = 0;
//	cl_device_id device = 0;
//	cl_kernel kernel = 0;
//	cl_mem imageObjects[2] = { 0, 0 };
//	cl_sampler sampler = 0;
//	cl_int errNum;
 
 
//	/*if (argc != 3)
//	{
//		std::cerr << "USAGE: " << argv[0] << " <inputImageFile> <outputImageFiles>" << std::endl;
//		return 1;
//	}*/
 
//	// Create an OpenCL context on first available platform
//	context = CreateContext();
//	if (context == NULL)
//	{
//		std::cerr << "Failed to create OpenCL context." << std::endl;
//		return 1;
//	}
 
//	// Create a command-queue on the first device available
//	// on the created context
//	commandQueue = CreateCommandQueue(context, &device);
//	if (commandQueue == NULL)
//	{
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	// Make sure the device supports images, otherwise exit
//	cl_bool imageSupport = CL_FALSE;
//	clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(cl_bool),
//		&imageSupport, NULL);
//	if (imageSupport != CL_TRUE)
//	{
//		std::cerr << "OpenCL device does not support images." << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	// Load input image from file and load it into
//	// an OpenCL image object
//	int width, height;
//	char *src0 = "C:/Users/jiang/Desktop/image/tu1.jpg";
//	imageObjects[0] = LoadImage(context, src0, width, height);
//	if (imageObjects[0] == 0)
//	{
//		std::cerr << "Error loading: " << std::string(src0) << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	// Create ouput image object
//	cl_image_format clImageFormat;
//	clImageFormat.image_channel_order = CL_RGBA;
//	clImageFormat.image_channel_data_type = CL_UNORM_INT8;
//	imageObjects[1] = clCreateImage2D(context,
//		CL_MEM_WRITE_ONLY,
//		&clImageFormat,
//		width,
//		height,
//		0,
//		NULL,
//		&errNum);
 
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error creating CL output image object." << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
 
//	// Create sampler for sampling image object
//	sampler = clCreateSampler(context,
//		CL_FALSE, // Non-normalized coordinates
//		CL_ADDRESS_CLAMP_TO_EDGE,
//		CL_FILTER_NEAREST,
//		&errNum);
 
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error creating CL sampler object." << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	// Create OpenCL program
//	//program = CreateProgram(context, device, "ImageFilter2D.cl");
//	program = CreateProgram(context, device, "Sobel.cl");
//	if (program == NULL)
//	{
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
//	// Create OpenCL kernel
//	kernel = clCreateKernel(program, "sobel_rgb", NULL);
//	if (kernel == NULL)
//	{
//		std::cerr << "Failed to create kernel" << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	// Set the kernel arguments
//	errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &imageObjects[0]);
//	errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &imageObjects[1]);
//	/*errNum |= clSetKernelArg(kernel, 2, sizeof(cl_sampler), &sampler);
//	errNum |= clSetKernelArg(kernel, 3, sizeof(cl_int), &width);
//	errNum |= clSetKernelArg(kernel, 4, sizeof(cl_int), &height);*/
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error setting kernel arguments." << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	size_t localWorkSize[2] = { 16, 16 };
//	size_t globalWorkSize[2] = { RoundUp(localWorkSize[0], width),
//		RoundUp(localWorkSize[1], height) };
 
//	// Queue the kernel up for execution
//	errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL,
//		globalWorkSize, localWorkSize,
//		0, NULL, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error queuing kernel for execution." << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	// Read the output buffer back to the Host
//	char *buffer = new char[width * height * 4];
//	size_t origin[3] = { 0, 0, 0 };
//	size_t region[3] = { width, height, 1 };
//	errNum = clEnqueueReadImage(commandQueue, imageObjects[1], CL_TRUE,
//		origin, region, 0, 0, buffer,
//		0, NULL, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error reading result buffer." << std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		return 1;
//	}
 
//	std::cout << std::endl;
//	std::cout << "Executed program succesfully." << std::endl;
 
//	//memset(buffer, 0xff, width * height * 4);
//	// Save the image out to disk
//	char *saveImage = "C:/Users/jiang/Desktop/image/tu2.jpg";
//	//std::cout << buffer << std::endl;
//	cv::Mat imageColor = cv::imread(src0);
//	cv::Mat imageColor2;
//	imageColor2.create(imageColor.rows, imageColor.cols, imageColor.type());
//	int w = 0;
//	for (int v = imageColor2.rows-1; v >=0; v--)
//	{
//		for (int u =0 ; u <imageColor2.cols; u++)
//		{
//			imageColor2.at<cv::Vec3b>(v, u)[0] = buffer[w++];
//			imageColor2.at<cv::Vec3b>(v, u)[1] = buffer[w++];
//			imageColor2.at<cv::Vec3b>(v, u)[2] = buffer[w++];
//			w++;
//		}
//	}
//	cv::imshow("image", imageColor2);
//	cv::imwrite(saveImage, imageColor2);
//	cv::waitKey(0);
//	/*if (!SaveImage(saveImage, buffer, width, height))
//	{
//		std::cerr << "Error writing output image: " << saveImage<< std::endl;
//		Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//		delete[] buffer;
//		return 1;
//	}*/
 
//	delete[] buffer;
//	Cleanup(context, commandQueue, program, kernel, imageObjects, sampler);
//	return 0;
//}
