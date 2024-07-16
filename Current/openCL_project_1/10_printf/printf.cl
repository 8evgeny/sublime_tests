__kernel void _printf_(void)
{
    printf( "Hello from work item %lu!\n", (ulong) get_global_id(0) );
}

