typedef struct tag_result
{
    int xpos, ypos;
    uint SAD;
}result;

enum matchMetod
{
    TM_SQDIFF = 0,
    TM_SQDIFF_NORMED,
    TM_CCORR,
    TM_CCORR_NORMED,
    TM_CCOEFF,
    TM_CCOEFF_NORMED
};


//wokrItem передает сигнал о завершении (если к примеру SAD < 100)
//Передавать image2D
//__Local
//Запускать сразу 4  kernel

__kernel void matching(__global uchar* imageData,
                     __global uchar* templateData,
                     __global result* res,
                     int w,
                     int h,
                     int t_cols,
                     int t_rows,
                     __global uint* aux,
                     int method
                     )
{
    // get index into global data array
    int x = get_global_id(0);
    int y = get_global_id(1);
    int iGID = (y * w + h);
    uint SAD=0;
    uint step_y = h / 8;
    uint step_x = w / 8;

//    local uchar imadeResult[(w-t_cols+1)*(h-t_rows+1)]

    // bound check (equivalent to the limit on a 'for' loop for standard/serial C code
    if ( iGID >= w*h)
    {
        return;
    }

    uchar searchIMG;
    uchar templateIMG;


    if (method == TM_SQDIFF)
    {
        for ( int y1 = 0; y1 < t_rows; y1 +=step_y )
        {
            for ( int x1 = 0; x1 < t_cols; x1 +=step_x )
            {
                searchIMG = imageData[(y+y1) * w + (x+x1)];
                templateIMG = templateData[y1 *  t_cols + x1];
//                SAD += abs( searchIMG - templateIMG );
                SAD += ( searchIMG - templateIMG ) * ( searchIMG - templateIMG );
            }
        }
    }


    atomic_min(aux, SAD);
    barrier(CLK_GLOBAL_MEM_FENCE);
    if ( (*aux) == SAD )
    {
        (*res).SAD = SAD;
        (*res).xpos = x;
        (*res).ypos = y;
    }
}


//#ifdef SQDIFF_NORMED
//__global__ void match_temp(const cuda::PtrStepSz<unsigned char> img_work_gpu, float * dev_result_array_bright)
//{
//    int id = blockIdx.x * blockDim.x + threadIdx.x;
//    int sum_roi_temp = 0;
//    int diff_roi_temp = 0;
//    int y = id / RESULT_WIDTH;
//    int x = id % RESULT_WIDTH;
//    for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
//    {
//        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
//        {
//            int i = tmp_y * TEMPLATE_WIDTH + tmp_x;
//            unsigned char temp = const_img_temp_array[i];
//            unsigned char roi = img_work_gpu(tmp_y + y, tmp_x + x);
//            diff_roi_temp += abs(roi - temp);
//            sum_roi_temp += (roi + temp);
//        } // for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
//    } // for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
//    dev_result_array_bright[id] = 1.f - (float)diff_roi_temp / ((float)sum_roi_temp);
//}  // END void match_temp
//#endif // END #ifdef SQDIFF_NORMED
