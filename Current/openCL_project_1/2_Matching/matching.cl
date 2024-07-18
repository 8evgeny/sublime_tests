typedef struct tag_result
{
    int xpos, ypos;
    uint tm_result;
}result;

enum matchMetod
{
    TM_SQDIFF = 0,
    TM_SQDIFF_NORMED,
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
                     __global uint* var,
                     int method
                     )
{
    // get index into global data array
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * IMG_WIDTH + IMG_HEIGHT);
    uint tm_result = 0;
    uint step_y = 8;
    uint step_x = 8;
    if ( iGID >= IMG_WIDTH * IMG_HEIGHT)
    {
        return;
    }
    uchar I;
    uchar T;

    if (method == TM_SQDIFF)
    {
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                I = imData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                T = tmData[ Y * TEMPLATE_WIDTH + X ];
                tm_result += ( I - T ) * ( I - T );
            }
        }

        atomic_min(var, tm_result);
        barrier(CLK_GLOBAL_MEM_FENCE);
        if ( (*var) == tm_result )
        {
            (*res).tm_result = tm_result;
            (*res).xpos = work_item_X;
            (*res).ypos = work_item_Y;
        }
    }

    if (method == TM_SQDIFF_NORMED)
    {
        long long I2 = 0;
        long long T2 = 0;
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                I = imData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                T = tmData[ Y * TEMPLATE_WIDTH + X ];
                I2 += I*I;
                T2 += T*T;
                tm_result += ( I - T ) * ( I - T );
            }
        }
        tm_result = tm_result * 1000 /sqrt((float)(I2*T2));

        atomic_min(var, tm_result);
        barrier(CLK_GLOBAL_MEM_FENCE);
        if ( (*var) == tm_result )
        {
            (*res).tm_result = tm_result;
            (*res).xpos = work_item_X;
            (*res).ypos = work_item_Y;
        }
    }

    if (method == TM_CCOEFF)
    {
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                I = imData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                T = tmData[ Y * TEMPLATE_WIDTH + X ];
                tm_result += I * T;
            }
        }
        atomic_max(var, tm_result);
        barrier(CLK_GLOBAL_MEM_FENCE);
        if ( (*var) == tm_result )
        {
            (*res).tm_result = tm_result;
            (*res).xpos = work_item_X;
            (*res).ypos = work_item_Y;
        }
    }



}


