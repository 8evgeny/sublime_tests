
__kernel void vecsum(float k,
                      __global float *aBuffer,
                      __global float *bBuffer,
                      __global float *cBuffer,
                      int size)
{
    size_t globalId = get_global_id(0);

    if (globalId < size)
        cBuffer[globalId] = k * aBuffer[globalId] + bBuffer[globalId];
}
