//__constant int TEMPLATE_WIDTH = 48;
//__constant int EXT_VAL = 5;
//__constant int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
//__constant int WORK_WIDTH = SOURCE_WIDTH - 1;
//__constant int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;
//__constant int RESULT_AREA = RESULT_WIDTH * RESULT_WIDTH;
//__constant int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_WIDTH;
//__constant float TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;

//MAGIC_INT.s0 = 48;  //TEMPLATE_WIDTH
//MAGIC_INT.s1 = 239; //WORK_WIDTH  5 * 48-1
//MAGIC_INT.s2 = 192; //RESULT_WIDTH  239 - 48 + 1
//MAGIC_FLOAT.s0 = 0.000434028f // TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;

__constant int4 MAGIC_INT = (int4)(48, 239, 192, 0);
__constant float4 MAGIC_FLOAT = (float4)(0.000434028f, 0, 0, 0);

struct Pix
{
    unsigned char x;
    unsigned char y;
    float bright;
}; // END Pix

__kernel void work_cl_6(__global uchar * img_work,
                        __global uchar * img_temp,
                        __global float * img_result,
                        __global int * maxVal_int,
                        __global struct Pix * pix_max)
{
    int4 result = (int4)(get_global_id(0) % MAGIC_INT.s2, get_global_id(0) / MAGIC_INT.s2, get_global_id(0), 0);
    int8 sum_roi_temp = 0;
    int8 sum_temp_temp = 0;
    int8 sum_roi_roi = 0;
    int8 sum_roi = 0;
    int8 sum_temp = 0;
    int temp_id = 0;
    for(int tmp_y = 0; tmp_y < MAGIC_INT.s0; ++tmp_y)
    {
        int8 roi_id0 = (int8)((result.y + tmp_y) * MAGIC_INT.s1 + result.x, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 1,
                              (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 2, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 3,
                              (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 4, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 5,
                              (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 6, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 7);

        for(int tmp_x = 0; tmp_x < MAGIC_INT.s0; tmp_x += 8, temp_id += 8)
        {
            int8 temp = (int8)(img_temp[temp_id], img_temp[temp_id + 1], img_temp[temp_id + 2], img_temp[temp_id + 3],
                               img_temp[temp_id + 4], img_temp[temp_id + 5], img_temp[temp_id + 6], img_temp[temp_id + 7] );

            int8 roi = (int8)(img_work[roi_id0.s0 + tmp_x], img_work[roi_id0.s1 + tmp_x], img_work[roi_id0.s2 + tmp_x], img_work[roi_id0.s3 + tmp_x],
                              img_work[roi_id0.s4 + tmp_x], img_work[roi_id0.s5 + tmp_x], img_work[roi_id0.s6 + tmp_x], img_work[roi_id0.s7 + tmp_x]);

            sum_roi_temp.s0 += roi.s0 * temp.s0;
            sum_roi_temp.s1 += roi.s1 * temp.s1;
            sum_roi_temp.s2 += roi.s2 * temp.s2;
            sum_roi_temp.s3 += roi.s3 * temp.s3;
            sum_roi_temp.s4 += roi.s4 * temp.s4;
            sum_roi_temp.s5 += roi.s5 * temp.s5;
            sum_roi_temp.s6 += roi.s6 * temp.s6;
            sum_roi_temp.s7 += roi.s7 * temp.s7;

            sum_temp_temp.s0 += temp.s0 * temp.s0;
            sum_temp_temp.s1 += temp.s1 * temp.s1;
            sum_temp_temp.s2 += temp.s2 * temp.s2;
            sum_temp_temp.s3 += temp.s3 * temp.s3;
            sum_temp_temp.s4 += temp.s4 * temp.s4;
            sum_temp_temp.s5 += temp.s5 * temp.s5;
            sum_temp_temp.s6 += temp.s6 * temp.s6;
            sum_temp_temp.s7 += temp.s7 * temp.s7;

            sum_roi_roi.s0 += roi.s0 * roi.s0;
            sum_roi_roi.s1 += roi.s1 * roi.s1;
            sum_roi_roi.s2 += roi.s2 * roi.s2;
            sum_roi_roi.s3 += roi.s3 * roi.s3;
            sum_roi_roi.s4 += roi.s4 * roi.s4;
            sum_roi_roi.s5 += roi.s5 * roi.s5;
            sum_roi_roi.s6 += roi.s6 * roi.s6;
            sum_roi_roi.s7 += roi.s7 * roi.s7;

            sum_roi.s0 += roi.s0;
            sum_roi.s1 += roi.s1;
            sum_roi.s2 += roi.s2;
            sum_roi.s3 += roi.s3;
            sum_roi.s4 += roi.s4;
            sum_roi.s5 += roi.s5;
            sum_roi.s6 += roi.s6;
            sum_roi.s7 += roi.s7;

            sum_temp.s0 += temp.s0;
            sum_temp.s1 += temp.s1;
            sum_temp.s2 += temp.s2;
            sum_temp.s3 += temp.s3;
            sum_temp.s4 += temp.s4;
            sum_temp.s5 += temp.s5;
            sum_temp.s6 += temp.s6;
            sum_temp.s7 += temp.s7;

        } // END for(int tmp_x = 0; tmp_x < MAGIC_INT.s0; ++tmp_x)
    } // END for(int tmp_y = 0; tmp_y < MAGIC_INT.s0; ++tmp_y)
    const float sum_roi_temp1  = MAGIC_FLOAT.s0 * (sum_roi_temp.s0 + sum_roi_temp.s1 + sum_roi_temp.s2 + sum_roi_temp.s3 +
                                                   sum_roi_temp.s4 + sum_roi_temp.s5 + sum_roi_temp.s6 + sum_roi_temp.s7);

    const float sum_roi1 = MAGIC_FLOAT.s0 * (sum_roi.s0 + sum_roi.s1 + sum_roi.s2 + sum_roi.s3 +
                                             sum_roi.s4 + sum_roi.s5 + sum_roi.s6 + sum_roi.s7);

    const float sum_temp1 = MAGIC_FLOAT.s0 * (sum_temp.s0 + sum_temp.s1 + sum_temp.s2 + sum_temp.s3 +
                                              sum_temp.s4 + sum_temp.s5 + sum_temp.s6 + sum_temp.s7);

    const float sum_roi_roi1 = MAGIC_FLOAT.s0 * (sum_roi_roi.s0 + sum_roi_roi.s1 + sum_roi_roi.s2 + sum_roi_roi.s3 +
                                                 sum_roi_roi.s4 + sum_roi_roi.s5 + sum_roi_roi.s6 + sum_roi_roi.s7);

    const float sum_temp_temp1 = MAGIC_FLOAT.s0 * (sum_temp_temp.s0 + sum_temp_temp.s1 + sum_temp_temp.s2 + sum_temp_temp.s3 +
                                                   sum_temp_temp.s4 + sum_temp_temp.s5 + sum_temp_temp.s6 + sum_temp_temp.s7);

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
        (*pix_max).x = result.x;
        (*pix_max).y = result.y;
    } // END if((*maxVal_int) == img_result_int)

    img_result[result.z] = img_result_float;
} // END void work_cl_6


__kernel void work_cl_8(__global  uchar * img_work,
                        __global  uchar * img_temp,
                        __global  float * img_result,
                        __global  int * maxVal_int,
                        __global  struct Pix * pix_max)
{
    int4 result = (int4)(get_global_id(0) % MAGIC_INT.s2, get_global_id(0) / MAGIC_INT.s2, get_global_id(0), 0);
    int8 sum_roi_temp = 0;
    int8 sum_roi_temp_2 = 0;
    int8 sum_temp_temp = 0;
    int8 diff_roi_temp = 0;
    int8 sum_roi_roi = 0;
    int8 sum_roi = 0;
    int8 sum_temp = 0;
    int temp_id = 0;
    for(int tmp_y = 0; tmp_y < MAGIC_INT.s0; ++tmp_y)
    {
        int8 roi_id0 = (int8)((result.y + tmp_y) * MAGIC_INT.s1 + result.x, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 1,
                              (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 2, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 3,
                              (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 4, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 5,
                              (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 6, (result.y + tmp_y) * MAGIC_INT.s1 + result.x + 7);
        for(int tmp_x = 0; tmp_x < MAGIC_INT.s0; tmp_x += 8, temp_id += 8)
        {
            int8 temp = (int8)(img_temp[temp_id], img_temp[temp_id + 1], img_temp[temp_id + 2], img_temp[temp_id + 3],
                               img_temp[temp_id + 4], img_temp[temp_id + 5], img_temp[temp_id + 6], img_temp[temp_id + 7] );

            int8 roi = (int8)(img_work[roi_id0.s0 + tmp_x], img_work[roi_id0.s1 + tmp_x], img_work[roi_id0.s2 + tmp_x], img_work[roi_id0.s3 + tmp_x],
                              img_work[roi_id0.s4 + tmp_x], img_work[roi_id0.s5 + tmp_x], img_work[roi_id0.s6 + tmp_x], img_work[roi_id0.s7 + tmp_x]);

            sum_roi_temp.s0 += roi.s0 * temp.s0;
            sum_roi_temp.s1 += roi.s1 * temp.s1;
            sum_roi_temp.s2 += roi.s2 * temp.s2;
            sum_roi_temp.s3 += roi.s3 * temp.s3;
            sum_roi_temp.s4 += roi.s4 * temp.s4;
            sum_roi_temp.s5 += roi.s5 * temp.s5;
            sum_roi_temp.s6 += roi.s6 * temp.s6;
            sum_roi_temp.s7 += roi.s7 * temp.s7;

            sum_temp_temp.s0 += temp.s0 * temp.s0;
            sum_temp_temp.s1 += temp.s1 * temp.s1;
            sum_temp_temp.s2 += temp.s2 * temp.s2;
            sum_temp_temp.s3 += temp.s3 * temp.s3;
            sum_temp_temp.s4 += temp.s4 * temp.s4;
            sum_temp_temp.s5 += temp.s5 * temp.s5;
            sum_temp_temp.s6 += temp.s6 * temp.s6;
            sum_temp_temp.s7 += temp.s7 * temp.s7;

            sum_roi_roi.s0 += roi.s0 * roi.s0;
            sum_roi_roi.s1 += roi.s1 * roi.s1;
            sum_roi_roi.s2 += roi.s2 * roi.s2;
            sum_roi_roi.s3 += roi.s3 * roi.s3;
            sum_roi_roi.s4 += roi.s4 * roi.s4;
            sum_roi_roi.s5 += roi.s5 * roi.s5;
            sum_roi_roi.s6 += roi.s6 * roi.s6;
            sum_roi_roi.s7 += roi.s7 * roi.s7;

            sum_roi.s0 += roi.s0;
            sum_roi.s1 += roi.s1;
            sum_roi.s2 += roi.s2;
            sum_roi.s3 += roi.s3;
            sum_roi.s4 += roi.s4;
            sum_roi.s5 += roi.s5;
            sum_roi.s6 += roi.s6;
            sum_roi.s7 += roi.s7;

            sum_temp.s0 += temp.s0;
            sum_temp.s1 += temp.s1;
            sum_temp.s2 += temp.s2;
            sum_temp.s3 += temp.s3;
            sum_temp.s4 += temp.s4;
            sum_temp.s5 += temp.s5;
            sum_temp.s6 += temp.s6;
            sum_temp.s7 += temp.s7;

            diff_roi_temp.s0 += abs(roi.s0 - temp.s0);
            diff_roi_temp.s1 += abs(roi.s1 - temp.s1);
            diff_roi_temp.s2 += abs(roi.s2 - temp.s2);
            diff_roi_temp.s3 += abs(roi.s3 - temp.s3);
            diff_roi_temp.s4 += abs(roi.s4 - temp.s4);
            diff_roi_temp.s5 += abs(roi.s5 - temp.s5);
            diff_roi_temp.s6 += abs(roi.s6 - temp.s6);
            diff_roi_temp.s7 += abs(roi.s7 - temp.s7);

            sum_roi_temp_2.s0 += (roi.s0 + temp.s0);
            sum_roi_temp_2.s1 += (roi.s1 + temp.s1);
            sum_roi_temp_2.s2 += (roi.s2 + temp.s2);
            sum_roi_temp_2.s3 += (roi.s3 + temp.s3);
            sum_roi_temp_2.s4 += (roi.s4 + temp.s4);
            sum_roi_temp_2.s5 += (roi.s5 + temp.s5);
            sum_roi_temp_2.s6 += (roi.s6 + temp.s6);
            sum_roi_temp_2.s7 += (roi.s7 + temp.s7);

        } // END for(int tmp_x = 0; tmp_x < MAGIC_INT.s0; ++tmp_x)
    } // END for(int tmp_y = 0; tmp_y < MAGIC_INT.s0; ++tmp_y)

    const float sum_roi_temp1  = MAGIC_FLOAT.s0 * (sum_roi_temp.s0 + sum_roi_temp.s1 + sum_roi_temp.s2 + sum_roi_temp.s3 +
                                                   sum_roi_temp.s4 + sum_roi_temp.s5 + sum_roi_temp.s6 + sum_roi_temp.s7);

    const float sum_roi1 = MAGIC_FLOAT.s0 * (sum_roi.s0 + sum_roi.s1 + sum_roi.s2 + sum_roi.s3 +
                                             sum_roi.s4 + sum_roi.s5 + sum_roi.s6 + sum_roi.s7);

    const float sum_temp1 = MAGIC_FLOAT.s0 * (sum_temp.s0 + sum_temp.s1 + sum_temp.s2 + sum_temp.s3 +
                                              sum_temp.s4 + sum_temp.s5 + sum_temp.s6 + sum_temp.s7);

    const float sum_roi_roi1 = MAGIC_FLOAT.s0 * (sum_roi_roi.s0 + sum_roi_roi.s1 + sum_roi_roi.s2 + sum_roi_roi.s3 +
                                                 sum_roi_roi.s4 + sum_roi_roi.s5 + sum_roi_roi.s6 + sum_roi_roi.s7);

    const float sum_temp_temp1 = MAGIC_FLOAT.s0 * (sum_temp_temp.s0 + sum_temp_temp.s1 + sum_temp_temp.s2 + sum_temp_temp.s3 +
                                                   sum_temp_temp.s4 + sum_temp_temp.s5 + sum_temp_temp.s6 + sum_temp_temp.s7);

    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;

    const float img_result_float = ch / sqrt(zn1 * zn2) -
            (float)(diff_roi_temp.s0 + diff_roi_temp.s1 + diff_roi_temp.s2 + diff_roi_temp.s3 +
                    diff_roi_temp.s4 + diff_roi_temp.s5 + diff_roi_temp.s6 + diff_roi_temp.s7) /
                    (sum_roi_temp_2.s0 + sum_roi_temp_2.s1 + sum_roi_temp_2.s2 + sum_roi_temp_2.s3 +
                     sum_roi_temp_2.s4 + sum_roi_temp_2.s5 + sum_roi_temp_2.s6 + sum_roi_temp_2.s7);

    const int img_result_int = img_result_float * 1000000;

    atomic_max(maxVal_int, img_result_int);
    barrier(CLK_GLOBAL_MEM_FENCE);

    if((*maxVal_int) == img_result_int)
    {
        (*pix_max).bright = img_result_float;
        (*pix_max).x = result.x;
        (*pix_max).y = result.y;
    } // END if((*maxVal_int) == img_result_int)

    img_result[result.s2] = img_result_float;

} // END tmml_cl_8

