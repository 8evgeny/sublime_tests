#include <stdio.h>
#include <CL/cl.h>
#include <CL/cl_ext.h>


const char *opencl =

"\n#ifdef cl_arm_printf\n"
"#pragma OPENCL EXTENSION cl_arm_printf: enable\n"
"#endif\n"

"__kernel void hello() \n"
"{\n"
" printf(\"Hello, World!\\n\");\n"
"}\n";


void callback( const char *buffer, unsigned int length, size_t final, void *user_data)
{
printf("%.*s", length, buffer);
}


int main()
{
cl_platform_id platform;
cl_device_id device;
cl_context context;

cl_context_properties context_properties[] =
{
CL_PRINTF_CALLBACK_ARM, (cl_context_properties)callback,
CL_PRINTF_BUFFERSIZE_ARM, 0x100000,
CL_CONTEXT_PLATFORM, 0,
0
};

cl_command_queue queue;
cl_program program;
cl_kernel kernel;

clGetPlatformIDs(1, &platform, NULL);

context_properties[5] = (cl_context_properties)platform;

clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

context = clCreateContext(context_properties, 1, &device, NULL, NULL, NULL);

queue = clCreateCommandQueue(context, device, 0, NULL);

program = clCreateProgramWithSource(context, 1, &opencl, NULL, NULL);
kernel = clCreateKernel(program, "hello", NULL);
clEnqueueTask(queue, kernel, 0, NULL, NULL);

clFinish(queue);
clReleaseKernel(kernel);
clReleaseProgram(program);
clReleaseCommandQueue(queue);
clReleaseContext(context);

return 0;
}
