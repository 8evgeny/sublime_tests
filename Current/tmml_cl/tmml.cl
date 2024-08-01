__constant int TEMPLATE_WIDTH = 48;
__constant int TEMPLATE_HEIGHT = 48;
__constant int EXT_VAL = 5;
__constant int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
__constant int SOURCE_HEIGHT = EXT_VAL * TEMPLATE_HEIGHT;
__constant int WORK_WIDTH = SOURCE_WIDTH - 1;
__constant int WORK_HEIGHT = SOURCE_HEIGHT - 1;
__constant int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;
__constant int RESULT_HEIGHT = WORK_HEIGHT - TEMPLATE_HEIGHT + 1;
__constant int RESULT_AREA = RESULT_WIDTH * RESULT_HEIGHT;
__constant int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;
__constant float RESULT_AREA_1 = 1.f / RESULT_AREA;
__constant float TEMPLATE_WIDTH_1 = 1.f / TEMPLATE_WIDTH;
__constant float TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;
__constant int k_float_to_int = 1000000;
typedef struct tag_result
{
    int xpos;
    int ypos;
    unsigned int tm_result;
}result;
__kernel void work_cl_2(__global unsigned char * imData, __global unsigned char * tmData, __global result* res, __global int* maxVal, __global int* matchData )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * RESULT_HEIGHT  + work_item_X);
    int diff_roi_temp = 0;
    int sum_roi_temp = 0;

    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    {
        int tmp1 = (work_item_Y + Y) * WORK_WIDTH + work_item_X ;
        int tmp2 = Y * TEMPLATE_WIDTH;
        for ( int X = 0; X < TEMPLATE_WIDTH; X += 1 )
        {
            roi = imData[ tmp1 + X  ];
            temp = tmData[ tmp2 + X ];
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp += roi + temp;
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    dev_result_array_bright = k_float_to_int * diff_roi_temp / sum_roi_temp;
    matchData[ iGID ] = dev_result_array_bright;
    atomic_min(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END void work_cl_2
__kernel void work_cl_2_no_img(__global unsigned char * imData, __global unsigned char * tmData, __global result* res, __global int* maxVal)
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * RESULT_HEIGHT  + work_item_X);
    int diff_roi_temp = 0;
    int sum_roi_temp = 0;

    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;

    for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    {
        int tmp1 = (work_item_Y + Y) * WORK_WIDTH + work_item_X ;
        int tmp2 = Y * TEMPLATE_WIDTH;
        for ( int X = 0; X < TEMPLATE_WIDTH; X += 1 )
        {
            roi = imData[ tmp1 + X  ];
            temp = tmData[ tmp2 + X ];
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp += roi + temp;
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )

    dev_result_array_bright = k_float_to_int * diff_roi_temp / sum_roi_temp;

    atomic_min(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END void work_cl_2_no_img
__kernel void work_cl_6(__global unsigned char * imData, __global unsigned char * tmData, __global result* res, __global int* maxVal, __global int* matchData )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * RESULT_HEIGHT  + work_item_X);
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    {
        int tmp1 = (work_item_Y + Y) * WORK_WIDTH + work_item_X ;
        int tmp2 = Y * TEMPLATE_WIDTH;
        for ( int X = 0; X < TEMPLATE_WIDTH; X += 1 )
        {
            roi = imData[ tmp1 + X  ];
            temp = tmData[ tmp2 + X ];
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    dev_result_array_bright = k_float_to_int * ch / sqrt(zn1 * zn2);
    matchData[ iGID ] = dev_result_array_bright;
    atomic_max(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END void work_cl_6
__kernel void work_cl_6_no_img(__global unsigned char * imData, __global unsigned char * tmData, __global result* res, __global int* maxVal )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int Y = 0; Y < TEMPLATE_HEIGHT; ++Y )
    {
        int tmp1 = (work_item_Y + Y) * WORK_WIDTH + work_item_X ;
        int tmp2 = Y * TEMPLATE_WIDTH;
        for ( int X = 0; X < TEMPLATE_WIDTH; ++X )
        {
            roi = imData[ tmp1 + X  ];
            temp = tmData[ tmp2 + X ];
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    dev_result_array_bright = k_float_to_int * ch / sqrt(zn1 * zn2);
    atomic_max(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END work_cl_6_no_img
__kernel void work_cl_8(__global unsigned char * imData, __global unsigned char * tmData, __global result* res, __global int* maxVal, __global int* matchData )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * RESULT_HEIGHT  + work_item_X);
    int sum_roi_temp = 0;
    int sum_roi_temp_2 = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    {
        int tmp1 = (work_item_Y + Y) * WORK_WIDTH + work_item_X ;
        int tmp2 = Y * TEMPLATE_WIDTH;
        for ( int X = 0; X < TEMPLATE_WIDTH; X += 1 )
        {
            roi = imData[ tmp1 + X  ];
            temp = tmData[ tmp2 + X ];
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp_2 += (roi + temp);
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    dev_result_array_bright = k_float_to_int * (ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2);
    matchData[ iGID ] = dev_result_array_bright;
    atomic_max(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END tmml_cl_8
__kernel void work_cl_8_no_img(__global unsigned char * imData, __global unsigned char * tmData, __global result* res, __global int* maxVal )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int sum_roi_temp = 0;
    int sum_roi_temp_2 = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    {
        int tmp1 = (work_item_Y + Y) * WORK_WIDTH + work_item_X ;
        int tmp2 = Y * TEMPLATE_WIDTH;
        for ( int X = 0; X < TEMPLATE_WIDTH; X += 1 )
        {
            roi = imData[ tmp1 + X  ];
            temp = tmData[ tmp2 + X ];
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp_2 += (roi + temp);
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    dev_result_array_bright = k_float_to_int * (ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2);
    atomic_max(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END work_cl_8_no_img
__kernel void work_cl_return_float(__global unsigned char * img_work, __global unsigned char * img_temp, __global float* matchData )
{
    int result_x = get_global_id(0);
    int result_y = get_global_id(1);
    int iGID = (result_y * RESULT_HEIGHT  + result_x);

    int sum_roi_temp = 0;
    int sum_roi_temp_2 = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    double dev_result_array_bright0 = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y )
    {
        int roi_y = result_y + tmp_y;
        for ( int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x )
        {
            int tmp_id = tmp_y * TEMPLATE_WIDTH + tmp_x;
            temp = img_temp[tmp_id];
            int roi_x = result_x + tmp_x;
            int roi_id = roi_y * WORK_WIDTH + roi_x;
            roi = img_work[roi_id];
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp_2 += (roi + temp);
        }// END for ( int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x )
    }// END for ( int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y )
    const double sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const double sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const double sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const double sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const double sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const double ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const double zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const double zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    matchData[ iGID ] = ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2;
}// END void work_cl_return_float

