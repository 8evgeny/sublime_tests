
__const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE
                            | CLK_ADDRESS_CLAMP_TO_EDGE
                            | CLK_FILTER_NEAREST;

__kernel void edges(__read_only image2d_t imageInk,
                    __write_only image2d_t imageOutk)
{
    size_t x = get_global_id(0);
    size_t y = get_global_id(1);

    if (x >= get_image_width(imageInk)
        || y >= get_image_height(imageInk))
        return;

    uint4 gx = read_imageui(imageInk, sampler, (int2)(x + 1, y - 1))
              + 2 * read_imageui(imageInk, sampler, (int2)(x + 1, y))
              + read_imageui(imageInk, sampler, (int2)(x + 1, y + 1))
              - read_imageui(imageInk, sampler, (int2)(x - 1, y - 1))
              - 2 * read_imageui(imageInk, sampler, (int2)(x - 1, y))
              - read_imageui(imageInk, sampler, (int2)(x - 1, y + 1));

    uint4 gy = read_imageui(imageInk, sampler, (int2)(x - 1, y + 1))
              + 2 * read_imageui(imageInk, sampler, (int2)(x, y + 1))
              + read_imageui(imageInk, sampler, (int2)(x + 1, y + 1))
              - read_imageui(imageInk, sampler, (int2)(x - 1, y - 1))
              - 2 * read_imageui(imageInk, sampler, (int2)(x, y - 1))
              - read_imageui(imageInk, sampler, (int2)(x + 1, y - 1));

    uint4 pixel = convert_uint4(sqrt(convert_float4(gx * gx + gy * gy)));
    pixel = clamp(pixel, (uint4)(0), (uint4)(255));
//    printf("r = %d, g = %d, b = %d, a = %d\n", pixel.s0, pixel.s1, pixel.s2, pixel.s3);
    pixel.s3 = 255;
    write_imageui(imageOutk, (int2)(x, y), pixel);
}
