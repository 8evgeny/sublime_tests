#include "sobel.h"
#include "sobel_kernel.h"
#include <math.h>
#define OPENCL_1_2
using std::cout;
using std::cin;
using std::endl;


ImageFilter::ImageFilter(const string &_filename)
{

    cout <<   "\n/*********************************************/ " << "\n";
    cout <<	    "     Image Filter - Sobel Filter                "   << "\n";
    cout <<	    "/*********************************************/ " << "\n\n";
    host_image = NULL;
    filename = _filename;
    load_bmp_image();
    setup_filter();
}

void ImageFilter::setup_filter( )
{
    float lFilter_x_gradient[WINDOW_SIZE*WINDOW_SIZE] = {  -1.0f,   0.0f,    1.0f,
                                                           -2.0f,   0.0f,    2.0f,
                                                           -1.0f,   0.0f,    1.0f  };
    float lFilter_y_gradient[WINDOW_SIZE*WINDOW_SIZE] = {  -1.0f,  -2.0f,   -1.0f,
                                                            0.0f,   0.0f,    0.0f,
                                                            1.f,    2.f,     1.f  };
    memcpy(filter, lFilter_x_gradient, WINDOW_SIZE*WINDOW_SIZE*sizeof(float));
    memcpy(filter, lFilter_y_gradient, WINDOW_SIZE*WINDOW_SIZE*sizeof(float));
}

void ImageFilter::load_bmp_image( )
{
    ReadBMPGrayscaleImageFloat(filename, &image);
}

void ImageFilter::write_bmp_image( )
{
    std::string filteredFileName("sobel_filtered.bmp") ;
    WriteBMPGrayscaleImageFloat(filteredFileName, &image, GPU_output);
}

void ImageFilter::read_GPU_filtered_image()
{
    size_t origin[3];
    size_t region[3];
    cl_int status = 0;
    origin[0] = origin[1] = origin[2] = 0;
    region[0] = image->width; region[1] = image->height; region[2] = 1;
    status = clEnqueueReadImage(commandQueue, ocl_filtered_image, CL_TRUE, origin, region, 0, 0, GPU_output, 0, NULL, NULL);
    LOG_OCL_ERROR(status, "Error # clEnqueueReadImage" );
}

void ImageFilter::load_GPU_raw_image()
{
    size_t origin[3];
    size_t region[3];
    cl_int status = 0;
    origin[0] = origin[1] = origin[2] = 0;
    region[0] = image->width; region[1] = image->height; region[2] = 1;
    status = clEnqueueWriteImage(commandQueue, ocl_raw, CL_TRUE, origin, region, 0, 0, image->pixels, 0, NULL, NULL);
    LOG_OCL_ERROR(status, "Error # clEnqueueReadImage" );
}

void ImageFilter::print_GPU_Timer()
{
    printf("GPU execution time is.......... %lf (ms)\n", 1000*timer_GPU.GetElapsedTime());
}

void ImageFilter::cleanup()
{
    free(host_image);
    ReleaseBMPImage(&image);
    cout << "Cleaned up!\n";
}

void ImageFilter::init_GPU_OpenCL( )
{
    //Allocate GPU output image memory
    GPU_output = NULL;
    GPU_output = (float*) calloc(1, image->height*image->width*sizeof(float) );

    setupOCLPlatform();
    setupOCLProgram();
    setupOCLkernels();
    setupOCLbuffers();

    gwsize[0] = image->width;
    gwsize[1] = image->height;
    lwsize[0] = lwsize[1] = 16;
}

void ImageFilter::setupOCLPlatform()
{
    cl_int status;
    //Setup the OpenCL Platform,
    //Get the first available platform. Use it as the default platform
    status = clGetPlatformIDs(1, &platform, NULL);
    LOG_OCL_ERROR(status, "Error # clGetPlatformIDs" );

    //Get the first available device
    status = clGetDeviceIDs (platform, deviceType, 1, &device, NULL);
    LOG_OCL_ERROR(status, "Error # clGetDeviceIDs" );

    //Create an execution context for the selected platform and device.
    cl_context_properties cps[3] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platform,
        0
    };
    context = clCreateContextFromType(
        cps,
        deviceType,
        NULL,
        NULL,
        &status);
    LOG_OCL_ERROR(status, "Error # clCreateContextFromType" );

    // Create command queue
    commandQueue = clCreateCommandQueue(context,
                                        device,
                                        0,
                                        &status);
    LOG_OCL_ERROR(status, "Error # clCreateCommandQueue" );
}

cl_int ImageFilter::setupOCLProgram()
{
    cl_int status;
    program = clCreateProgramWithSource(context, 1,
                (const char **)&sobel_kernel, NULL, &status);
    LOG_OCL_ERROR(status, "clCreateProgramWithSource Failed" );

    // Build the program
    status = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    if(status != CL_SUCCESS)
    {
        if(status == CL_BUILD_PROGRAM_FAILURE)
            LOG_OCL_COMPILER_ERROR(program, device);
        LOG_OCL_ERROR(status, "clBuildProgram Failed" );
    }
    return status;

}

cl_int ImageFilter::setupOCLkernels()
{
    cl_int status;
    // Create the OpenCL kernel
    kernel = clCreateKernel(program, "sobel_filter_kernel", &status);
    LOG_OCL_ERROR(status, "clCreateKernel Failed" );

    return status;
}

cl_int ImageFilter::setupOCLbuffers()
{
    cl_int status;
    //Intermediate reusable cl buffers
    cl_image_format image_format;
    image_format.image_channel_data_type = CL_FLOAT;
    image_format.image_channel_order = CL_R;

#ifdef OPENCL_1_2
    cl_image_desc image_desc;
    image_desc.image_type = CL_MEM_OBJECT_IMAGE2D;
    image_desc.image_width = image->width;
    image_desc.image_height = image->height;
    image_desc.image_depth = 1;
    image_desc.image_array_size = 1;
    //Note when the host_ptr is NULL row_pitch and slice_pith should be set to 0;
    //Otherwise you will get a CL_INVALID_IMAGE_DESCRIPTOR error
    image_desc.image_row_pitch = 0;
    image_desc.image_slice_pitch = 0;
    image_desc.num_mip_levels = 0;
    image_desc.num_samples = 0;
    image_desc.buffer= NULL;
#endif
#ifdef OPENCL_1_2
    ocl_raw = clCreateImage(
#else
    ocl_raw = clCreateImage2D(
#endif
        context,
        CL_MEM_READ_ONLY,
        &image_format,
#ifdef OPENCL_1_2
        &image_desc,
#else
        image->width, image->height, 0, 	
#endif
        NULL,
        &status);
    LOG_OCL_ERROR(status, "clCreateImage Failed" );

#ifdef OPENCL_1_2
    //Note when the host_ptr is NULL row_pitch and slice_pith should be set to 0;
    //Otherwise you will get a CL_INVALID_IMAGE_DESCRIPTOR error
    image_desc.image_row_pitch = 0;
    image_desc.image_slice_pitch = 0;
    ocl_filtered_image = clCreateImage(
#else
    ocl_filtered_image = clCreateImage2D(
#endif
        context,
        CL_MEM_WRITE_ONLY,
        &image_format,
#ifdef OPENCL_1_2
        &image_desc,
#else
        image->width, image->height, 0, 	
#endif
        NULL,
        &status);
    LOG_OCL_ERROR(status, "clCreateImage Failed" );

    ocl_filter_x_gradient = clCreateBuffer(
        context,
        CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
        WINDOW_SIZE*WINDOW_SIZE*sizeof(float),
        filter,
        &status);
    LOG_OCL_ERROR(status, "clCreateBuffer Failed" );

    ocl_filter_y_gradient = clCreateBuffer(
        context,
        CL_MEM_READ_WRITE|CL_MEM_USE_HOST_PTR,
        WINDOW_SIZE*WINDOW_SIZE*sizeof(float),
        filter,
        &status);
    LOG_OCL_ERROR(status, "clCreateBuffer Failed" );
    //Create OpenCL device output buffer
    return status;
}

void ImageFilter::run_GPU()
{
    load_GPU_raw_image();
    run_gaussian_filter_kernel();
    read_GPU_filtered_image();
}

void ImageFilter::run_gaussian_filter_kernel()
{
    cl_event	wlist[2];
    cl_int status;

    int windowSize = WINDOW_SIZE;
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&ocl_raw);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&ocl_filtered_image);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&ocl_filter_x_gradient);
    status = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&ocl_filter_y_gradient);
    status = clSetKernelArg(kernel, 4, sizeof(int), (void*)&windowSize);
    status = clEnqueueNDRangeKernel(
                        commandQueue,
                        kernel,
                        2,
                        NULL,
                        gwsize,
                        lwsize,
                        0,
                        NULL,
                        &wlist[0]);
    LOG_OCL_ERROR(status, "clEnqueueNDRangeKernel Failed" );
    clWaitForEvents(1, &wlist[0]);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: chapter9.sobel.exe sample.bmp\n";
        std::cout << "The file sample.bmp is available in the input_images directory. This \n";
        std::cout << "This should be a grayscale image. and the height and width should be amultiple of 16 pixels\n";
        return 0;
    }

    ImageFilter*	img_filter;
    img_filter = new ImageFilter(string(argv[1]));
    unsigned int num_of_frames = 0;
    try
    {
        img_filter->init_GPU_OpenCL();
        img_filter->start_GPU_Timer();
        img_filter->run_GPU();
        img_filter->stop_GPU_Timer();
        img_filter->print_GPU_Timer();
        img_filter-> write_bmp_image( );
        delete(img_filter);
    }
#ifdef __CL_ENABLE_EXCEPTIONS
    catch(cl::Error err)
    {
        std::cout << "Error: " << err.what() << "(" << err.err() << ")" << std::endl;
        cout << "Please check CL/cl.h for error code" << std::endl;
        delete(img_filter);
    }
#endif
    catch(string msg)
    {
        std::cout << "Exception caught: " << msg << std::endl;
        delete(img_filter);
    }

    return 0;
}



