
__kernel void parsum(__global int *inputBuffer,
                     __global int *outputBuffer,
                     int size)
{
    size_t globalId = get_global_id(0);
    size_t localId = get_local_id(0);

    // Create temporal buffers.
    __local int buffer[WORKGROUPSIZE];

    // Initialize buffers.
    buffer[localId] = inputBuffer[globalId];
    barrier(CLK_LOCAL_MEM_FENCE);

    for (int offset = get_local_size(0) >> 1; offset > 0; offset >>= 1) {
        if (localId < offset
            && globalId + offset < size)
            buffer[localId] += buffer[localId + offset];

        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // Write result to the output buffer.
    if (localId == 0)
        outputBuffer[get_group_id(0)] = buffer[0];
}
