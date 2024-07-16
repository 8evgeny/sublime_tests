#define _CRT_SECURE_NO_WARNINGS
#define PROGRAM_FILE "printf.cl"

#define NUM_KERNELS 1

#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <CL/cl_ext.h>

using namespace std;

/* Find a GPU or CPU associated with the first available platform */
cl_device_id create_device()
{
   cl_platform_id platform;
   cl_device_id dev;
   int err;

   /* Identify a platform */
   err = clGetPlatformIDs(1, &platform, NULL);
   if(err < 0) {
      perror("Couldn't identify a platform");
      exit(1);
   }

   /* Access a device */
   err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
   if(err == CL_DEVICE_NOT_FOUND) {
      err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
   }
   if(err < 0) {
      perror("Couldn't access any devices");
      exit(1);
   }

   return dev;
}

/* Create program from a file and compile it */
cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename)
{
   cl_program program;
   FILE *program_handle;
   char *program_buffer, *program_log;
   size_t program_size, log_size;
   int err;

   /* Read program file and place content into buffer */
   program_handle = fopen(filename, "r");
   if(program_handle == NULL) {
      perror("Couldn't find the program file");
      exit(1);
   }
   fseek(program_handle, 0, SEEK_END);
   program_size = ftell(program_handle);
   rewind(program_handle);
   program_buffer = (char*)malloc(program_size + 1);
   program_buffer[program_size] = '\0';
   fread(program_buffer, sizeof(char), program_size, program_handle);
   fclose(program_handle);

   /* Create program from file */
   program = clCreateProgramWithSource(ctx, 1,
      (const char**)&program_buffer, &program_size, &err);
   if(err < 0) {
      perror("Couldn't create the program");
      exit(1);
   }
   free(program_buffer);

   /* Build program */
   err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   if(err < 0) {

      /* Find size of log and print to std output */
      clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG,
            0, NULL, &log_size);
      program_log = (char*) malloc(log_size + 1);
      program_log[log_size] = '\0';
      clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG,
            log_size + 1, program_log, NULL);
      printf("%s\n", program_log);
      free(program_log);
      exit(1);
   }

   return program;
}

/* Define a printf callback function. */
void printf_callback( const char *buffer, size_t len, size_t complete, void *user_data )
{
    printf( "%.*s", len, buffer );
}


int main()
{
   /* OpenCL structures */
   cl_device_id device;
   cl_context context;
   cl_program program;
   cl_kernel kernel[NUM_KERNELS];
   cl_command_queue queue;
   cl_event prof_event;
   cl_int i, j, err;
   size_t max_workgroup_size, global_size;
   char kernel_names[NUM_KERNELS][20] = {"_printf_"};

   /* Data and buffers */
   float sum_from_gpu, serial_sum, *scalar_sum, *vector_sum;
   cl_mem data_buffer, scalar_sum_buffer, vector_sum_buffer;
   cl_int num_groups;
   cl_ulong time_start, time_end, total_time;


   cl_platform_id *platforms;
   cl_uint num_platforms;
   clGetPlatformIDs(1, NULL, &num_platforms);
   platforms = (cl_platform_id*)
      malloc(sizeof(cl_platform_id) * num_platforms);
   clGetPlatformIDs(num_platforms, platforms, NULL);


   /* Create device and determine local size */
   device = create_device();
   err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE,
         sizeof(max_workgroup_size), &max_workgroup_size, NULL);
   if(err < 0)
   {
      perror("Couldn't obtain device information");
      exit(1);
   }
   printf("max_work_group_size = %d\n", (int)max_workgroup_size);

   /* Create a context */
   /* Create a cl_context with a printf_callback and user specified buffer size. */
   cl_context_properties properties[] =
   {
       /* Enable a printf callback function for this context. */
       CL_PRINTF_CALLBACK_ARM,   (cl_context_properties) printf_callback,

       /* Request a minimum printf buffer size of 4MiB for devices in the
          context that support this extension. */
       CL_PRINTF_BUFFERSIZE_ARM, (cl_context_properties) 0x100000,

       CL_CONTEXT_PLATFORM,      (cl_context_properties) platforms, 0
   };



   context = clCreateContext( properties, 1, &device, NULL, NULL, &err );
//   context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
   if(err < 0) {
      perror("Couldn't create a context");
      exit(1);
   }






   /* Build program */
   program = build_program(context, device, PROGRAM_FILE);


   /* Create a command queue */
   queue = clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE, &err);
   if(err < 0) {
      perror("Couldn't create a command queue");
      exit(1);
   };

   for(i=0; i < NUM_KERNELS; i++)
   {
        /* Create a kernel */
        kernel[i] = clCreateKernel(program, kernel_names[i], &err);
        if(err < 0)
        {
            perror("Couldn't create a kernel");
            exit(1);
        }


        err = clEnqueueNDRangeKernel(queue, kernel[i], 1, NULL, NULL, NULL, 0, NULL, &prof_event);


        if(err < 0)
        {
            perror("Couldn't enqueue the kernel");
            exit(1);
        }

        /* Finish processing the queue and get profiling information */
        clFinish(queue);

        clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
        clGetEventProfilingInfo(prof_event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
        total_time = time_end - time_start;

        printf("Total time = %lu\n\n", total_time);

        /* Deallocate event */
        clReleaseEvent(prof_event);

   }// END -- for(i=0; i < NUM_KERNELS; i++)

   /* Deallocate resources */

   for(i=0; i<NUM_KERNELS; i++)
   {
      clReleaseKernel(kernel[i]);
   }
    clReleaseMemObject(scalar_sum_buffer);
    clReleaseMemObject(vector_sum_buffer);
    clReleaseMemObject(data_buffer);
    clReleaseCommandQueue(queue);
    clReleaseProgram(program);
    clReleaseContext(context);

    return 0;
}
