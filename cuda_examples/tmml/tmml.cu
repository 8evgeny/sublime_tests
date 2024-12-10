#include "tmml.hpp"

using namespace std;
using namespace cv;

__constant__ unsigned char const_img_temp_array[TEMPLATE_AREA];
cudaStream_t streamsKernel[numCudaTread];

void tmml::cuda_Malloc()
{
    Mat img_temp(Size(TEMPLATE_WIDTH, TEMPLATE_WIDTH), CV_8UC1, Scalar(0));
    img_temp_gpu.upload(img_temp);

    for(int i = 0; i < numCudaTread; ++i)
    {
        cudaMalloc((void**)& dev_mp[i], sizeof(Pix));
    }// END for(int i = 0; i < numCudaTread; ++i)
} // -- END cuda_Malloc()

void tmml::cuda_Free()
{
    cudaFree(&img_temp_gpu);
    for(int i = 0; i < numCudaTread; ++i)
    {
        cudaFree(&dev_img_work[i]);
        cudaFree(dev_mp[i]);
    }// END for(int i = 0; i < numCudaTread; ++i)

} // -- END cudaFree()

__global__ void match_temp(const cuda::PtrStepSz<unsigned char> img_work_gpu,
                           Pix * dev_v_res_pix
//                           ,float * dev_result_array_bright
                           )
{
    const int result_id = blockIdx.x * blockDim.x + threadIdx.x;
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int sum_roi_roi = 0;
#ifdef COMBINED
    int sum_roi = 0;
    int sum_temp = 0;
#endif // END ifdef COMBINED
    const int result_y = result_id / RESULT_WIDTH_1;
    const int result_x = result_id % RESULT_WIDTH;

    for(int temp_y = 0; temp_y < TEMPLATE_WIDTH; ++temp_y)
    {
        int work_y = temp_y + result_y;
        int temp_id0 = temp_y * TEMPLATE_WIDTH;
        for(int temp_x = 0; temp_x < TEMPLATE_WIDTH; ++temp_x)
        {
            int temp = const_img_temp_array[temp_id0 + temp_x];
            int roi = img_work_gpu(work_y, temp_x + result_x);
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
#ifdef COMBINED
            sum_roi += roi;
            sum_temp += temp;
#endif // END ifdef COMBINED
        } // for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
    } // for(int tmp_y = 0; tmp_y < TEMPLATE_WIDTH; ++tmp_y)

    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float diff_roi_temp2 = sum_roi_roi1 + sum_temp_temp1 - 2.f * sum_roi_temp1;
#ifdef COMBINED
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    const float result_float = ch / sqrt(zn1 * zn2) -
            KOEFF2LIB_float * diff_roi_temp2 / sqrt(sum_roi_roi1 * sum_temp_temp1);
#endif // END ifdef COMBINED
#ifdef SQDIFF_NORMED
    const float result_float = 1.f - KOEFF2LIB_float * diff_roi_temp2 / sqrt(sum_roi_roi1 * sum_temp_temp1);
#endif // END ifdef SQDIFF_NORMED

    int val = 1000000 * result_float;
    atomicMax(&dev_v_res_pix->bright, val);
    __syncthreads();
    if(dev_v_res_pix->bright == val)
    {
        dev_v_res_pix->x = result_x;
        dev_v_res_pix->y = result_y;
    }  // END if(*dev_max_val == val)
}  // END match_temp

void tmml::work_tmml(const Mat& img_work, const Mat& img_temp, Pix& max_pix)
{
    cudaMemcpyToSymbol(const_img_temp_array, img_temp.data, sizeof(unsigned char) * TEMPLATE_AREA);

    for(int i = 0; i < numCudaTread; ++i)
    {
        dev_img_work[i].upload(img_work(Ri[i]), st[i]);
        cudaStreamCreate(&streamsKernel[i]);
        match_temp<<<blocks, threads, 0, streamsKernel[i]>>>(dev_img_work[i], dev_mp[i] );
    }// END for(int i = 0; i < numCudaTread; ++i)

    for(int i = 0; i < numCudaTread; ++i)
    {
        cudaMemcpy(&host_mp[i], dev_mp[i], sizeof(Pix), cudaMemcpyDeviceToHost);
    }// END for(int i = 0; i < numCudaTread; ++i)

    max_pix = maxValue(host_mp);

} // END work_tmml

Pix tmml::maxValue(Pix host_mp[numCudaTread])
{
    Pix max;
    max.bright = 0;
    for(int i = 0; i < numCudaTread; ++i)
    {
        if(host_mp[i].bright > max.bright) max = host_mp[i];
    }
    return  max;
} // END maxValue


