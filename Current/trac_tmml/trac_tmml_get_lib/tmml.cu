#include "tmml.hpp"

using namespace std;
using namespace cv;

__constant__ unsigned char const_img_temp_array[TEMPLATE_AREA];
__constant__ unsigned char const_first_level_x[N1];
__constant__ unsigned char const_first_level_y[N1];

void tmml::cuda_Malloc()
{
    cudaMalloc((void**)&dev_result_array_x, sizeof(unsigned char) * RESULT_AREA);
    cudaMalloc((void**)&dev_result_array_y, sizeof(unsigned char) * RESULT_AREA);
    cudaMalloc((void**)&dev_result_array_bright, sizeof(float) * RESULT_AREA);
    Mat img_work(Size(WORK_WIDTH, WORK_HEIGHT), CV_8UC1, Scalar(0));
    img_work_gpu.upload(img_work);
    Mat img_temp(Size(TEMPLATE_WIDTH, TEMPLATE_HEIGHT), CV_8UC1, Scalar(0));
    img_temp_gpu.upload(img_temp);
    cudaMalloc((void**)&dev_max_K1, sizeof(Pix) * N1);
    cudaMalloc((void**)&dev_max_K2, sizeof(Pix) * N2);
} // -- END cuda_Malloc()

void tmml::cuda_Free()
{
    cudaFree(&img_work_gpu);
    cudaFree(&img_temp_gpu);
    cudaFree(dev_result_array_x);
    cudaFree(dev_result_array_y);
    cudaFree(dev_result_array_bright);
    cudaFree(dev_max_K1);
    cudaFree(dev_max_K2);
    cudaFree(const_img_temp_array);
    cudaFree(const_first_level_x);
    cudaFree(const_first_level_y);
} // -- END cudaFree()

void tmml::fill_result_array()
{
    int id = 0;
    for(int y = 0; y < RESULT_HEIGHT; ++y)
    {
        for(int x = 0; x < RESULT_WIDTH; ++x)
        {
            result_array_x[id] = (unsigned char)x;
            result_array_y[id] = (unsigned char)y;
            id++;
        } // END for(int x = 0; x < RESULT_WIDTH; ++x)
    } // END for(int y = 0; y < RESULT_HEIGHT; ++y)
    cudaMemcpy(dev_result_array_x, result_array_x, sizeof(unsigned char) * RESULT_AREA, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_result_array_y, result_array_y, sizeof(unsigned char) * RESULT_AREA, cudaMemcpyHostToDevice);
} // END fill_result_array

void tmml::fill_template_array()
{
    int id = 0;
    for(int y = 0; y < TEMPLATE_HEIGHT; ++y)
    {
        for(int x = 0; x < TEMPLATE_WIDTH; ++x)
        {
            template_array_x[id] = (unsigned char)x;
            template_array_y[id] = (unsigned char)y;
            id++;
        }  // END for(int x = 0; x < TEMPLATE_WIDTH; ++x)
    }  // END for(int y = 0; y < TEMPLATE_HEIGHT; ++y)
    cudaMemcpy(dev_template_array_x, template_array_x, sizeof(unsigned char) * TEMPLATE_AREA, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_template_array_y, template_array_y, sizeof(unsigned char) * TEMPLATE_AREA, cudaMemcpyHostToDevice);
} // END fill_template_array

void tmml::fill1level()
{       
    int id = 0;
    for(int y = 0; y < RESULT_HEIGHT; ++y)
    {
        for(int x = 0; x < RESULT_WIDTH; x += K1)
        {
            first_level_x[id] = (unsigned char)x;
            first_level_y[id] = (unsigned char)y;
            id++;
        } // END for(int x = 0; x < RESULT_WIDTH; x += K1)
    } // END for(int x = 0; x < RESULT_WIDTH; x += K1)
    cudaMemcpyToSymbol(const_first_level_x, first_level_x, sizeof(unsigned char) * N1);
    cudaMemcpyToSymbol(const_first_level_y, first_level_y, sizeof(unsigned char) * N1);
} // END fill1level

#ifdef SQDIFF_NORMED
__global__ void match_temp(const cuda::PtrStepSz<unsigned char> img_work_gpu, float * dev_result_array_bright)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int sum_roi_temp = 0;
    int diff_roi_temp = 0;
    int y = id / RESULT_WIDTH;
    int x = id % RESULT_WIDTH;
    for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
    {
        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
        {
            int i = tmp_y * TEMPLATE_WIDTH + tmp_x;
            unsigned char temp = const_img_temp_array[i];
            unsigned char roi = img_work_gpu(tmp_y + y, tmp_x + x);
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp += (roi + temp);
        } // for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
    } // for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
    dev_result_array_bright[id] = 1.f - (float)diff_roi_temp / ((float)sum_roi_temp);
}  // END void match_temp
#endif // END #ifdef SQDIFF_NORMED

#ifdef CCOEFF_NORMED
__global__ void match_temp(const cuda::PtrStepSz<unsigned char> img_work_gpu, float * dev_result_array_bright)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int y = id / RESULT_WIDTH;
    int x = id % RESULT_WIDTH;
    for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
    {
        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
        {
            int i = tmp_y * TEMPLATE_WIDTH + tmp_x;
            unsigned char temp = const_img_temp_array[i];
            unsigned char roi = img_work_gpu(tmp_y + y, tmp_x + x);
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
        } // for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
    } // for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    dev_result_array_bright[id] = ch / sqrt(zn1 * zn2);
}  // END void match_temp
#endif // END #ifdef CCOEFF_NORMED

#ifdef COMBINED
__global__ void match_temp(const cuda::PtrStepSz<unsigned char> img_work_gpu, float * dev_result_array_bright)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;
    int sum_temp = 0;
    int sum_roi_temp_2 = 0;
    int diff_roi_temp = 0;
    int y = id / RESULT_WIDTH;
    int x = id % RESULT_WIDTH;
    for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
    {
        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
        {
            int i = tmp_y * TEMPLATE_WIDTH + tmp_x;
            unsigned char temp = const_img_temp_array[i];
            unsigned char roi = img_work_gpu(tmp_y + y, tmp_x + x);
            sum_roi_temp += roi * temp;
            sum_temp_temp += temp * temp;
            sum_roi_roi += roi * roi;
            sum_roi += roi;
            sum_temp += temp;
            diff_roi_temp += abs(roi - temp);
            sum_roi_temp_2 += (roi + temp);
        } // for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)
    } // for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)
    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;
    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;
    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;
    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;
    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;
    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;
    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;
    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;
    dev_result_array_bright[id] = ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2;
}  // END void match_temp
#endif // END ifdef COMBINED

__global__ void max_pixel1(const float * dev_result_array_bright, Pix * max_K1)
{
    __shared__ int id, first_level_x_id, first_level_y_id, x, k, i, max_pix_x, max_pix_y;
    __shared__ float bright, max_pix_bright;
    id = blockDim.x * blockIdx.x + threadIdx.x;
    first_level_y_id = const_first_level_y[id];
    first_level_x_id = const_first_level_x[id];

    k = first_level_y_id * RESULT_WIDTH + first_level_x_id;
    bright = dev_result_array_bright[k];

    max_pix_x = first_level_x_id;
    max_pix_y = first_level_y_id;
    max_pix_bright = bright;

    for(i = 1; i < K1; ++i)
    {
        x = first_level_x_id + i;
        k = first_level_y_id * RESULT_WIDTH + x;
        bright = dev_result_array_bright[k];
        if(bright > max_pix_bright)
        {
            max_pix_x = x;
            max_pix_y = first_level_y_id;
            max_pix_bright = bright;
        } // END if(bright > max_pix.bright)
    } // END for(i = 1; i < K1; ++i)
    max_K1[id].x = max_pix_x;
    max_K1[id].y = max_pix_y;
    max_K1[id].bright = max_pix_bright;
} // END __global__ max_pixel1

__global__ void max_pixel2(const Pix * max_K1, Pix * max_K2)
{
    __shared__ int id, i, k, max_pix_x, max_pix_y;
    __shared__ float max_pix_bright;
    id = blockDim.x * blockIdx.x + threadIdx.x;
    k = id * K2;

    const Pix& max_K1_0 = max_K1[k];
    max_pix_x = max_K1_0.x;
    max_pix_y = max_K1_0.y;
    max_pix_bright = max_K1_0.bright;

    for(i = 1; i < K2; ++i)
    {
        const Pix& max_K1_i = max_K1[k + i];
        if(max_K1_i.bright > max_pix_bright)
        {
            max_pix_bright = max_K1_i.bright;
            max_pix_x = max_K1_i.x;
            max_pix_y = max_K1_i.y;
        } // END if(max_K1_i.bright > max_pix_bright)
    } // END for(i = 1; i < K2; ++i)
    max_K2[id].x = max_pix_x;
    max_K2[id].y = max_pix_y;
    max_K2[id].bright = max_pix_bright;
} // END max_pixel2

void tmml::work_tmml(const Mat& img_work, const Mat& img_temp, Pix& max_pix)
{
    img_work_gpu.upload(img_work);
    int id = 0;
    for(int y = 0; y < TEMPLATE_HEIGHT; y++)
    {
        for(int x = 0; x < TEMPLATE_WIDTH; x++)
        {
            img_temp_arr[id] = img_temp.at<unsigned char>(y, x);
            id++;
        } // END for(int x = 0; x < TEMPLATE_WIDTH; x++)
    } // END for(int y = 0; y < TEMPLATE_HEIGHT; y++)

    cudaMemcpyToSymbol(const_img_temp_array, img_temp_arr, sizeof(unsigned char) * TEMPLATE_AREA);


    match_temp<<<blocks_match_temp, threads_match_temp>>>(img_work_gpu, dev_result_array_bright);

// =========================================================
    max_pixel1<<<blocks_maxloc, threads_maxloc>>>(dev_result_array_bright, dev_max_K1);
    max_pixel2<<<blocks_maxloc, threads_maxloc>>>(dev_max_K1, dev_max_K2);
    cudaMemcpy(max_K2, dev_max_K2, sizeof(Pix) * N2, cudaMemcpyDeviceToHost);

    max_pix = max_pix0;
    for(int i = 0; i < N2; ++i)
    {
        Pix& pix_i = max_K2[i];
        if(pix_i.bright > max_pix.bright){max_pix = pix_i;}
    } // END for(int i = 0; i < N3; ++i)

#ifdef find_diff_result
    cudaMemcpy(result_array_bright, dev_result_array_bright, sizeof(float) * RESULT_AREA, cudaMemcpyDeviceToHost);
#endif // END #ifdef find_diff_result
} // END work_tmml
