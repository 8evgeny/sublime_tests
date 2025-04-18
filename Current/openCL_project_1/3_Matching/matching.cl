typedef struct tag_result
{
    int xpos, ypos;
    uint SAD;
}result;

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
                     __global uint* aux
                     )
{
    // get index into global data array
    int x = get_global_id(0);
    int y = get_global_id(1);
    int iGID = (y * w + h);
    uint SAD=0;

//    local uchar imadeResult[(w-t_cols+1)*(h-t_rows+1)]

    // bound check (equivalent to the limit on a 'for' loop for standard/serial C code
    if ( iGID >= w*h)
    {
        return;
    }


    // loop through the template image
        for ( int y1 = 0; y1 < t_rows; y1++ )
        {
            for ( int x1 = 0; x1 < t_cols; x1++ )
            {
                uchar p_SearchIMG = imageData[(y+y1) * w + (x+x1)];
                uchar p_TemplateIMG = templateData[y1 *  t_cols + x1];
                SAD += abs( p_SearchIMG - p_TemplateIMG );
            }
        }
        // save the best found position
//        if (SAD < 100)
//        {
//            (*res).SAD = SAD;
//            (*res).xpos = x;
//            (*res).ypos = y;
//        }

        atomic_min(aux, SAD);
        barrier(CLK_GLOBAL_MEM_FENCE);

        if ( (*aux) == SAD )
        {
            (*res).SAD = SAD;
            (*res).xpos = x;
            (*res).ypos = y;
        }
    }

//     kernel void test2(global uchar* imageData,global uchar* templateData, int x, int y, int w, int h,int t_cols, int t_rows, global int* aux){
//        // get index into global data array
//        int x1 = get_global_id(0);
//		int y1 = get_global_id(1);
//		int iGID = (y1 * t_cols + x1);


//        // bound check (equivalent to the limit on a 'for' loop for standard/serial C code


//        int p_SearchIMG = imageData[(y+y1) * w + (x+x1)];
//        int p_TemplateIMG = templateData[y1 *  t_cols + x1];
//        (*aux) += abs( p_SearchIMG - p_TemplateIMG );



//     }



    // OpenCL Kernel Function for element by element
// kernel void pattern(global uchar* imageData,global uchar* templateData, global float*aux, int t_cols, int t_rows, int w, int h, global result* res)
//{

//        // get index into global data array
//        int iGIDX = get_global_id(0);
//		int iGIDY = get_global_id(1);
//		int iGID = (iGIDY * w + iGIDX);

//		int x = iGIDX;
//		int y = iGIDY;

//        res->xpos=0;
//        res->ypos=0;

//        float SAD = 0;

//	// loop through the template image

//		for ( int y1 = 0; y1 < t_rows; y1++ )
//            for ( int x1 = 0; x1 < t_cols; x1++ )
//			{

//				int p_SearchIMG = imageData[(y+y1) * w + (x+x1)];
//                int p_TemplateIMG = templateData[y1 *  t_cols + x1];

//                SAD += abs( p_SearchIMG - p_TemplateIMG );
//            }

//        // save the best found position
//        if ( (*res).SAD > SAD )
//		{
//            (*res).SAD = SAD;
//            // give me min SAD
//			(*res).xpos = x;
//            (*res).ypos = y;

//        }

//        (*res).SAD= 3450;
//        *aux=(float)4;

//    }
