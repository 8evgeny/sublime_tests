
__kernel void horizontalIntegral(__read_only image2d_t image,
                                 __global uint3 *integralImage,
                                 __global ulong3 *integralImage2)
{
    size_t globalId = get_global_id(0);

    if (globalId >= get_image_height(image))
        return;

    int width = get_image_width(image);
    int offset = globalId * width;

    uint3 sum = (uint3)(0);
    ulong3 sum2 = (ulong3)(0);
    uint3 pixel;
    ulong3 pixel2;

    for (int x = 0; x < width; x++) {
        pixel = read_imageui(image, (int2)(x, globalId)).s012;
        pixel2 = convert_ulong3(pixel);

        sum += pixel;
        sum2 += pixel2 * pixel2;

        integralImage[offset] = sum;
        integralImage2[offset] = sum2;

        offset++;
    }
}

__kernel void verticalIntegral(int width, int height,
                               __global uint3 *integralImage,
                               __global ulong3 *integralImage2)
{
    size_t globalId = get_global_id(0);

    if (globalId >= width)
        return;

    int offset = globalId;
    int cur;

    for (int y = 1; y < height; y++) {
        cur = offset + width;

        integralImage[cur] += integralImage[offset];
        integralImage2[cur] += integralImage2[offset];

        offset = cur;
    }
}
