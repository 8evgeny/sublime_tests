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
    const long long ch  = (long long)TEMPLATE_AREA * sum_roi_temp - (long long)sum_roi * sum_temp;
    const long long zn1 = (long long)TEMPLATE_AREA * sum_temp_temp - (long long)sum_temp * sum_temp;
    const long long zn2 = (long long)TEMPLATE_AREA * sum_roi_roi - (long long)sum_roi * sum_roi;
    const double sq1 = sqrt((double)zn1);
    const double sq2 = sqrt((double)zn2);
    dev_result_array_bright[id] = (double)ch / (sq1 * sq2);
}  // END void match_temp
#endif // END #ifdef CCOEFF_NORMED

#ifdef COMBINED
__global__ void match_temp(const cuda::PtrStepSz<unsigned char> img_work_gpu, float * dev_result_array_bright)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int sum_roi_temp = 0;
    int sum_temp_temp = 0;
    int sum_roi_roi = 0;
    int sum_roi = 0;u, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    if(maxLoc.x != temp_left || maxLoc.y != temp_top){cout << "CPU iter=" << iter << " !!!" << endl; break;}
}  // END for(int iter = 0; iter < iter_num; ++iter)
time_end = system_clock::now();
duration_matching = time_end - time_start;
cout.precision(2);
std::cout.setf(std::ios::fixed);
cout << "Duration OpenCV =\t" << 1e3 * duration_matching.count()/iter_num << " ms" << endl;

//CUDA
time_start = system_clock::now();

for(int iter = 0; iter < iter_num; ++iter)
{
    tm->work_cuda(img_work, img_temp, tm->max_pix);
    if(tm->max_pix.x != temp_left || tm->max_pix.y != temp_top){cout << "GPU iter=" << iter << " !!!" << endl; break;}
}  // END for(int iter = 0; iter < iter_num; ++iter)
time_end = system_clock::now();
duration_matching = time_end - time_start;
cout << "Duration CUDA =\t\t" << 1e3 * duration_matching.count()/iter_num  << " ms" << endl;
cout << "cuda xy =\t\t[" << (int)tm->max_pix.x << ", " << (int)tm->max_pix.y << "] " /*<<"   bright= " << tm->max_pix.bright*/ << endl;

//OpenCL
matchingOpenCL(img_work, img_temp);

//Results
tm->fill_result_array();
double sum_diff = 0;
for(int id = 0; id < RESULT_AREA; id++)
{
    int x = tm->result_array_x[id];
    int y = tm->result_array_y[id];
    float bright_gpu = tm->result_array_bright[id];
    float bright_cpu = img_result_cpu.at<float>(y, x);
    img_result_cuda.at<float>(y, x) = bright_gpu;
    double diff = abs(bright_cpu - bright_gpu);
    //cout << id << "; x = " << x << "; y = " << y << "; cpu = " << bright_cpu << "; gpu = " << bright_gpu << endl;
    sum_diff += diff;
} // END for(int id = 0; id < RESULT_AREA; id++)
//    cout << "sum_diff = " << sum_diff << "; RESULT_AREA = " << RESULT_AREA << "; raitio = " << sum_diff/RESULT_AREA << endl;


normalize(img_result_cpu, img_result_cpu, 0, 255, NORM_MINMAX);
img_result_cpu.convertTo(img_result_cpu, CV_8UC1);
int k = 2;
resize(img_result_cpu, img_result_cpu, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
const char* OpenCV_window = "OpenCV";
namedWindow( OpenCV_window, WINDOW_AUTOSIZE );
moveWindow(OpenCV_window, 900,100);
imshow(OpenCV_window, img_result_cpu);

normalize(img_result_cuda, img_result_cuda, 0, 255, NORM_MINMAX);

cout<<"CUDA"<<endl;
for (int i = res.xpos  + res.ypos * (img_result_cuda.cols - img_temp.cols + 1);
     i < res.xpos + res.ypos * (img_result_cuda.cols - img_temp.cols + 1) + 10; ++i)
{
    cout<<img_result_cuda.at<uint>(i)<<"  ";
}
cout<<endl;

img_result_cuda.convertTo(img_result_cuda, CV_8UC1);
resize(img_result_cuda, img_result_cuda, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
const char* CUDA_window = "CUDA";
namedWindow( CUDA_window, WINDOW_AUTOSIZE );
moveWindow(CUDA_window, 1300,100);
imshow(CUDA_window, img_result_cuda);

normalize(img_result_CL, img_result_CL, 0, 255, NORM_MINMAX);
img_result_CL.convertTo(img_result_CL, CV_8UC1);
resize(img_result_CL, img_result_CL, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
const char* CL_window = "OpenCL";
namedWindow( CL_window, WINDOW_AUTOSIZE );
moveWindow(CL_window, 900,600);
imshow(CL_window, img_result_CL);

cv::cvtColor(img_work,img_work,cv::COLOR_GRAY2BGR);
cv::rectangle(img_work, cv::Point(res.xpos, res.ypos), cv::Point(res.xpos+img_temp.cols, res.ypos+img_temp.rows),cv::Scalar(0,0,255),3);
const char* OpenCL = "matchingOpenCL";
namedWindow( OpenCL, WINDOW_AUTOSIZE );
moveWindow(OpenCL, 1300,600);
resize(img_work, img_work, Size(k*RESULT_WIDTH, k*RESULT_HEIGHT));
imshow(OpenCL, img_work);

unsigned char key = waitKey(0);
tm.reset();
return 0;
} // END main

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
    const long long ch  = (long long)TEMPLATE_AREA * sum_roi_temp - (long long)sum_roi * sum_temp;
    const long long zn1 = (long long)TEMPLATE_AREA * sum_temp_temp - (long long)sum_temp * sum_temp;
    const long long zn2 = (long long)TEMPLATE_AREA * sum_roi_roi - (long long)sum_roi * sum_roi;
    const double sq1 = sqrt((double)zn1);
    const double sq2 = sqrt((double)zn2);
    dev_result_array_bright[id] = (double)ch/ (sq1 * sq2) - (double)diff_roi_temp / ((double)sum_roi_temp);
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

void tmml::work_cuda(const Mat& img_work, const Mat& img_temp, Pix& max_pix)
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

    cudaMemcpy(result_array_bright, dev_result_array_bright, sizeof(float) * RESULT_AREA, cudaMemcpyDeviceToHost);

} // END work_cuda
