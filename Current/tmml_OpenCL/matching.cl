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
    uint step_y = 1;
    uint step_x = 1;
    uchar I;
    uchar T;

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
        float I2 = 0, T2 = 0;
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                I = imData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                T = tmData[ Y * TEMPLATE_WIDTH + X ];
                sum_roi_temp += I * T;
                I2 += I * I;
                T2 += T * T;

            }
        }

//        sum_roi_temp /= sqrt (I2 * T2);

        atomic_max(maxVal, sum_roi_temp);
        barrier(CLK_GLOBAL_MEM_FENCE);

//        float tmp = (float) sum_roi_temp / *maxVal;
//        matchData[ iGID ] = tmp * 255 ;

        matchData[ iGID ] = sum_roi_temp ;

        barrier(CLK_GLOBAL_MEM_FENCE);
        if ( (*maxVal) == sum_roi_temp )
        {
            (*res).tm_result = sum_roi_temp;
            (*res).xpos = work_item_X;
            (*res).ypos = work_item_Y;
        }
    }

}


