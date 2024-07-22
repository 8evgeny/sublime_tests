typedef struct tag_result
{
    int xpos, ypos;
    uint tm_result;
}result;

enum matchMetod
{
    TM_SQDIFF = 0,
    TM_SQDIFF_NORMED,
    TM_CCORR,
    TM_CCORR_NORMED,
    TM_CCOEFF,
    TM_CCOEFF_NORMED,
    TM_COMBINED
};


//wokrItem передает сигнал о завершении (если к примеру SAD < 100)
//Передавать image2D
//__Local
//Запускать сразу 4  kernel

__kernel void matching(__global uchar* imData,
                     __global uchar* tmData,
                     __global result* res,
                     int IMG_WIDTH,
                     int IMG_HEIGHT,
                     int TEMPLATE_WIDTH,
                     int TEMPLATE_HEIGHT,
                     __global uint* minVal,
                     __global uint* maxVal,
                     int method,
                     __global uint* matchData
                     )
{
    // get index into global data array
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * (IMG_HEIGHT - TEMPLATE_HEIGHT + 1)  + work_item_X);
    uint sum_roi_temp = 0;
    uint sum_temp_temp = 0;
    uint sum_roi_roi = 0;
    uint sum_roi = 0;
    uint sum_temp = 0;
    uint dev_result_array_bright;
    uint step_y = 1;
    uint step_x = 1;
    uchar I;
    uchar T;
    uint TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;

    if (method == TM_SQDIFF_NORMED)
    {
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                I = imData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                T = tmData[ Y * TEMPLATE_WIDTH + X ];
                sum_roi_temp += ( I - T ) * ( I - T );
            }
        }

        atomic_max(maxVal, sum_roi_temp);
        barrier(CLK_GLOBAL_MEM_FENCE);

        atomic_min(minVal, sum_roi_temp);
        barrier(CLK_GLOBAL_MEM_FENCE);

        matchData[ iGID ] = sum_roi_temp ;
        barrier(CLK_GLOBAL_MEM_FENCE);


        if ( (*minVal) == sum_roi_temp )
        {
            (*res).tm_result = sum_roi_temp;
            (*res).xpos = work_item_X;
            (*res).ypos = work_item_Y;
        }

    }

    if (method == TM_CCOEFF_NORMED)
    {
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                I = imData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                T = tmData[ Y * TEMPLATE_WIDTH + X ];
                sum_roi_temp += I * T;
                sum_temp_temp += T * T;
                sum_roi_roi += I * I;
                sum_roi += I;
                sum_temp += T;
            }
        }

//        const long long ch  = (long long)TEMPLATE_AREA * sum_roi_temp - (long long)sum_roi * sum_temp;
//        const long long zn1 = (long long)TEMPLATE_AREA * sum_temp_temp - (long long)sum_temp * sum_temp;
//        const long long zn2 = (long long)TEMPLATE_AREA * sum_roi_roi - (long long)sum_roi * sum_roi;
//        const double sq1 = sqrt((double)zn1);
//        const double sq2 = sqrt((double)zn2);
//        dev_result_array_bright = (double)ch / (sq1 * sq2);
//        matchData[ iGID ] = dev_result_array_bright ;

//        float tmp = (float) sum_roi_temp / *maxVal;
//        matchData[ iGID ] = tmp * 255 ;



        matchData[ iGID ] = sum_roi_temp;
        dev_result_array_bright = sum_roi_temp;
        atomic_max(maxVal, dev_result_array_bright);




        atomic_max(maxVal, dev_result_array_bright);
        barrier(CLK_GLOBAL_MEM_FENCE);
        if ( (*maxVal) == dev_result_array_bright )
        {
            (*res).tm_result = dev_result_array_bright;
            (*res).xpos = work_item_X;
            (*res).ypos = work_item_Y;
        }
    }

}


