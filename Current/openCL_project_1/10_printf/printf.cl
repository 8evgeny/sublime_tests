#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel void _printf_(void)
{
    printf( "Hello from work item %lu!\n", (ulong) get_global_id(0) );
}

