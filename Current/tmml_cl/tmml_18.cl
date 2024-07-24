typedef struct tag_result
{
    int xpos;
    int ypos;
    unsigned int tm_result;
}result;

//Возможные способы ускорения:
// - Передавать image2D
// - Запускать сразу несколько kernel
// - перейти на short

// метод  COMBINED
__kernel void tmml_cl(__global unsigned char * imData,
                     __global unsigned char * tmData,
                     __global result* res,
                     int IMG_WIDTH,
                     int IMG_HEIGHT,
                     int TEMPLATE_WIDTH,
                     int TEMPLATE_HEIGHT,
                     __global int* k_float_to_int,
                     __global int* maxVal,
                     __global int* matchData )
{
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * (IMG_HEIGHT - TEMPLATE_HEIGHT + 1)  + work_item_X);
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int diff_roi_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int sum_roi_temp_2 = 0;
    int dev_result_array_bright = 0;
    unsigned char roi = 0;
    unsigned char temp = 0;
    const int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;
    const float TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;

    for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y += 1 )
    {
        int tmp1 = (work_item_Y + Y) * IMG_WIDTH + work_item_X ;
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
    dev_result_array_bright = *k_float_to_int * (ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2);

    matchData[ iGID ] = dev_result_array_bright;
    atomic_max(maxVal, dev_result_array_bright);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*maxVal) == dev_result_array_bright )
    {
        (*res).tm_result = dev_result_array_bright;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }// END if ( (*maxVal) == dev_result_array_bright )
}// END __kernel void tmml_cl


