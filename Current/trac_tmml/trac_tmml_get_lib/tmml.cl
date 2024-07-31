//Возможные способы ускорения:
// - Передавать image2D
// - Запускать сразу несколько kernel
// - перейти на short

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

__kernel void work_cl_2(__global unsigned char * imData, __global unsigned char * tmData, __global float* matchData )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * RESULT_HEIGHT  + work_item_X);
    int diff_roi_temp = 0;
    int sum_roi_temp_2 = 0;
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
            sum_roi_temp_2 += (roi + temp);
        }// END for ( int X = 0; X < TEMPLATE_WIDTH; X +=1 )
    }// END for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    matchData[ iGID ] = (float) diff_roi_temp / sum_roi_temp_2;
}// END work_cl_2_no_img

__kernel void work_cl_6(__global unsigned char * imData, __global unsigned char * tmData, __global float* matchData )
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
    matchData[ iGID ] = ch / sqrt(zn1 * zn2);;
}// END void work_cl_6

__kernel void work_cl_8(__global unsigned char * imData, __global unsigned char * tmData, __global float* matchData )
{
    int work_X = get_global_id(0);
    int work_Y = get_global_id(1);
    int iGID = (work_Y * RESULT_HEIGHT  + work_X);
    int sum_roi_temp = 0;
    int sum_roi_temp_2 = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    for ( int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y )
    {
        int row_in_roi = (work_Y + tmp_y) * WORK_WIDTH + work_X ;
        int row_in_templ = tmp_y * TEMPLATE_WIDTH;
        for ( int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x )
        {
            roi = imData[ row_in_roi + tmp_x  ];
            temp = tmData[ row_in_templ + tmp_x ];
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
    matchData[ iGID ] = ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2;
}// END tmml_cl_8
