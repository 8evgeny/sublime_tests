typedef struct tag_result
{
    int xpos, ypos;
    uint SAD;
}result;

enum matchMetod
{
    TM_SQDIFF = 0,
    TM_SQDIFF_NORMED,
    TM_CCOEFF_NORMED,
    TM_COMBINED
};


//wokrItem передает сигнал о завершении (если к примеру SAD < 100)
//Передавать image2D
//__Local
//Запускать сразу 4  kernel

__kernel void matching(__global uchar* imageData,
                     __global uchar* templateData,
                     __global result* res,
                     int IMG_WIDTH,
                     int IMG_HEIGHT,
                     int TEMPLATE_WIDTH,
                     int TEMPLATE_HEIGHT,
                     __global uint* aux,
                     int method
                     )
{
    // get index into global data array
    int work_item_X = get_global_id(0);
    int work_item_Y = get_global_id(1);
    int iGID = (work_item_Y * IMG_WIDTH + IMG_HEIGHT);
    uint SAD=0;
    uint step_y = IMG_HEIGHT / 8;
    uint step_x = IMG_WIDTH / 8;
    if ( iGID >= IMG_WIDTH * IMG_HEIGHT)
    {
        return;
    }
    uchar searchIMG;
    uchar templateIMG;

    if (method == TM_SQDIFF)
    {
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                searchIMG = imageData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                templateIMG = templateData[ Y * TEMPLATE_WIDTH + X ];
                SAD += ( searchIMG - templateIMG ) * ( searchIMG - templateIMG );
            }
        }
    }

    if (method == TM_SQDIFF_NORMED)
    {
        for ( int Y = 0; Y < TEMPLATE_HEIGHT; Y +=step_y )
        {
            for ( int X = 0; X < TEMPLATE_WIDTH; X +=step_x )
            {
                searchIMG = imageData[ ( work_item_Y + Y ) * IMG_WIDTH + ( work_item_X + X ) ];
                templateIMG = templateData[ Y * TEMPLATE_WIDTH + X ];
                SAD += ( searchIMG - templateIMG ) * ( searchIMG - templateIMG );
            }
        }
    }


    atomic_min(aux, SAD);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*aux) == SAD )
    {
        (*res).SAD = SAD;
        (*res).xpos = work_item_X;
        (*res).ypos = work_item_Y;
    }
}


