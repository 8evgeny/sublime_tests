__kernel void reduction(int lenght, __global const float* in_data, __global float* out_data)
{    
    int lid = get_local_id(0);
    int gid = get_global_id(0);
    int group_size = get_local_size(0);

    float v1 = gid * 2 < lenght ? in_data[gid * 2] : 0;
    float v2 = gid * 2 + 1 < lenght ? in_data[gid * 2 + 1] : 0;

    __local float partial_sums[256];
    partial_sums[lid] = v1 + v2;

    barrier(CLK_LOCAL_MEM_FENCE);

    for(int i = 2; i < group_size; i <<= 1)
    {
        if(lid % i == 0)
            partial_sums[lid] += partial_sums[lid + (i>>1)];
        barrier(CLK_LOCAL_MEM_FENCE);
    }
    if(lid == 0)
    {
        out_data[get_group_id(0)] = partial_sums[0];
    }
} 
