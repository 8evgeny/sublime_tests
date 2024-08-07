//Возможные способы ускорения:
// - Передавать image2D
// - Запускать сразу несколько kernel
// - перейти на short
__constant int TEMPLATE_WIDTH = 48;
__constant int EXT_VAL = 5;
__constant int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
__constant int WORK_WIDTH = SOURCE_WIDTH - 1;
__constant int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;
__constant int RESULT_AREA = RESULT_WIDTH * RESULT_WIDTH;
__constant int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_WIDTH;
__constant float RESULT_AREA_1 = 1.f / RESULT_AREA;
__constant float TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;

struct Pix
{
    unsigned char x;
    unsigned char y;
    float bright;
}; // END Pix


__kernel void work_cl_6(__global unsigned char * img_work,
                        __global unsigned char * img_temp,
                        __global float * img_result,
                        __global int * maxVal_int,
                        __global struct Pix * pix_max)
{
    int result_id = get_global_id(0);
    int result_y = result_id / RESULT_WIDTH;
    int result_x = result_id % RESULT_WIDTH;
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int temp_id = 0;
    for(int tmp_y = 0; tmp_y < TEMPLATE_WIDTH; ++tmp_y)
    {
        int roi_id0 = (result_y + tmp_y) * WORK_WIDTH + result_x;
        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
        {
            unsigned char temp = img_temp[temp_id];
            unsigned char roi = img_work[roi_id0 + tmp_x];
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
            temp_id++;
        } // END for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
    } // END for(int tmp_y = 0; tmp_y < TEMPLATE_WIDTH; ++tmp_y)
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    const float img_result_float = ch / sqrt(zn1 * zn2);
    const int img_result_int = img_result_float * 1000000;
    atomic_max(maxVal_int, img_result_int);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if((*maxVal_int) == img_result_int)
    {
        (*pix_max).bright = img_result_float;
        (*pix_max).x = result_x;
        (*pix_max).y = result_y;
    } // END if((*maxVal_int) == img_result_int)
    img_result[result_id] = img_result_float;
} // END void work_cl_6


__kernel void work_cl_8(__global uchar * img_work,
                        __global uchar * img_temp,
                        __global float * img_result,
                        __global int * maxVal_int,
                        __global struct Pix * pix_max)
{
    int result_id = get_global_id(0);
    int result_y = result_id / RESULT_WIDTH;
    int result_x = result_id % RESULT_WIDTH;
    int4 sum_roi_temp = 0;
    int4 sum_roi_temp_2 = 0;
    int4 sum_temp_temp = 0;
    int4 diff_roi_temp = 0;
    int4 sum_roi_roi = 0;
    int4 sum_roi = 0;
    int4 sum_temp = 0;
    int temp_id = 0;
    for(int tmp_y = 0; tmp_y < TEMPLATE_WIDTH; ++tmp_y)
    {
        int roi_id0 = (result_y + tmp_y) * WORK_WIDTH + result_x;
        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; tmp_x += 4, temp_id += 4)
        {
            int4 temp = (int4)(img_temp[temp_id], img_temp[temp_id + 1], img_temp[temp_id + 2], img_temp[temp_id + 3]);
            int4 roi = (int4)(img_work[roi_id0 + tmp_x], img_work[roi_id0 + tmp_x + 1], img_work[roi_id0 + tmp_x + 2], img_work[roi_id0 + tmp_x + 3]);

            sum_roi_temp.x += roi.x * temp.x;
            sum_roi_temp.y += roi.y * temp.y;
            sum_roi_temp.z += roi.z * temp.z;
            sum_roi_temp.w += roi.w * temp.w;

            sum_temp_temp.x += temp.x * temp.x;
            sum_temp_temp.y += temp.y * temp.y;
            sum_temp_temp.z += temp.z * temp.z;
            sum_temp_temp.w += temp.w * temp.w;

            sum_roi_roi.x += roi.x * roi.x;
            sum_roi_roi.y += roi.y * roi.y;
            sum_roi_roi.z += roi.z * roi.z;
            sum_roi_roi.w += roi.w * roi.w;

            sum_roi.x += roi.x;
            sum_roi.y += roi.y;
            sum_roi.z += roi.z;
            sum_roi.w += roi.w;

            sum_temp.x += temp.x;
            sum_temp.y += temp.y;
            sum_temp.z += temp.z;
            sum_temp.w += temp.w;

            diff_roi_temp.x += abs(roi.x - temp.x);
            diff_roi_temp.y += abs(roi.y - temp.y);
            diff_roi_temp.z += abs(roi.z - temp.z);
            diff_roi_temp.w += abs(roi.w - temp.w);

            sum_roi_temp_2.x += (roi.x + temp.x);
            sum_roi_temp_2.y += (roi.y + temp.y);
            sum_roi_temp_2.z += (roi.z + temp.z);
            sum_roi_temp_2.w += (roi.w + temp.w);

        } // END for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
    } // END for(int tmp_y = 0; tmp_y < TEMPLATE_WIDTH; ++tmp_y)
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * (sum_roi_temp.x + sum_roi_temp.y + sum_roi_temp.z + sum_roi_temp.w);
    const float sum_roi1 = TEMPLATE_AREA_1 * (sum_roi.x + sum_roi.y + sum_roi.z + sum_roi.w);
    const float sum_temp1 = TEMPLATE_AREA_1 * (sum_temp.x + sum_temp.y + sum_temp.z + sum_temp.w);
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * (sum_roi_roi.x + sum_roi_roi.y + sum_roi_roi.z + sum_roi_roi.w);
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * (sum_temp_temp.x + sum_temp_temp.y + sum_temp_temp.z + sum_temp_temp.w);
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    const float img_result_float = ch / sqrt(zn1 * zn2)
            - (float)(diff_roi_temp.x + diff_roi_temp.y + diff_roi_temp.z + diff_roi_temp.w) /
            (sum_roi_temp_2.x + sum_roi_temp_2.y + sum_roi_temp_2.z + sum_roi_temp_2.w);
    const int img_result_int = img_result_float * 1000000;
    atomic_max(maxVal_int, img_result_int);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if((*maxVal_int) == img_result_int)
    {
        (*pix_max).bright = img_result_float;
        (*pix_max).x = result_x;
        (*pix_max).y = result_y;
    } // END if((*maxVal_int) == img_result_int)
    img_result[result_id] = img_result_float;
} // END tmml_cl_8


__kernel void work_cl_max(__global float * img_result,
                          __global float * img_result_bright,
                        __global unsigned char * img_result_x)
{
    int y = get_global_id(0);
    int result_id0 = y * RESULT_WIDTH;
    float result_bright_max = 0;
    int x_max = 0;
    for(int x = 0; x < RESULT_WIDTH; ++x)
    {
        float bright = img_result[result_id0 + x];
        if(bright > result_bright_max)
        {
            result_bright_max = bright;
            x_max = x;
        } // END if(bright > result_bright_max)
    } // END for(int x = 0; x < RESULT_WIDTH; ++x)
    img_result_bright[y] = result_bright_max;
    img_result_x[y] = x_max;
} // END work_cl_max
