__kernel void reduction(int lenght, __global const float* Input, __global float* result)
{    
    int lid = get_local_id(0);
    int gid = get_global_id(0);
    int group_size = get_local_size(0);


} 
