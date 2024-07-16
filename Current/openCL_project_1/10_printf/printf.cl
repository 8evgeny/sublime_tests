__kernel void printf(void)
{
    printf( "Hello from work item %lu!\n", (ulong) get_global_id(0) );
}

