#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#include <CL/opencl.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <array>

int main(void)
{
    // Set up platform, device and context
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device> devices;
    cl::Device default_device;
    cl::Platform::get(&platforms);

    if (platforms.size() == 0)
    {
        std::cout << "No OpenCL platform found, check installation!" << std::endl;
        exit(-1);
    }
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);

    if (devices.size() == 0)
    {
        std::cout << "No devices found in platform, check installation!" << std::endl;
        exit(-1);
    }
    default_device = devices[0];
    cl::Context context(default_device);

    std::ifstream program_file("kernel");
    std::string program_string(std::istreambuf_iterator<char>(program_file), (std::istreambuf_iterator<char>()));
    cl::Program::Sources source { program_string };
    cl::Program program(context, source);
    if (program.build()!=CL_SUCCESS)
    {
        std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<< std::endl;
        exit(-1);
    }
    cl::Kernel kernel(program, "read_write_image");
    cl::CommandQueue queue(context, default_device);

    // Set up dummy grayscale image
    std::vector<float> InputData(256, 0.0);
    for(int i=0; i<256; i++)
    {
        InputData[i] = 255.0f - i;
    }
    // Set up empty target image
    std::vector<float> OutputData(256, 0.0);

    cl::ImageFormat grayscale(CL_R, CL_FLOAT);
    cl::Image2D Input_Image(context, CL_MEM_READ_ONLY, grayscale, 16, 16);
    cl::Image2D Output_Image(context, CL_MEM_WRITE_ONLY, grayscale, 16, 16);

    std::array<cl::size_type, 3> origin {0,0,0};
    std::array<cl::size_type, 3> region {16, 16, 1};

    queue.enqueueWriteImage(Input_Image, CL_TRUE, origin, region, 0, 0, &InputData[0]);

    kernel.setArg(0, Input_Image);
    kernel.setArg(1, Output_Image);

    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(16,16), cl::NullRange, NULL);
    queue.enqueueReadImage(Output_Image, CL_TRUE, origin, region, 0, 0, &OutputData[0]);

    for(int i=0; i<256; i++)
    {
        std::cout << OutputData[i] << "  ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
