#pragma once
#ifndef NO_GPU
    #include <opencv2/core/cuda.hpp>
#endif // END ifndef NO_GPU

#define _USE_MATH_DEFINES
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>

const int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
const int WORK_WIDTH = SOURCE_WIDTH - 1;
const int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1; // 192
const int RESULT_AREA = RESULT_WIDTH * RESULT_WIDTH;
const int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_WIDTH;
const float RESULT_AREA_1 = 1.f / RESULT_AREA;
const float TEMPLATE_WIDTH_1 = 1.f / TEMPLATE_WIDTH;
const float TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;
const float KOEFF2LIB_float = KOEFF2LIB;

#ifdef GPU_AMPERE
    const int threads_match_temp = 128; // 256

#endif // END ifdef GPU3090

#ifdef GPU_VOLTA
    const int threads_match_temp = 128;
#endif  // END ifdef GPU_XAVIER_NX

#ifndef NO_GPU
    const float threads_match_temp_1 = 1.f / threads_match_temp;
    // Число нитей CUDA в итерации:
    const int blocks_match_temp = RESULT_AREA * threads_match_temp_1;
#endif // END ifndef NO_GPU

    struct Pix
    {
        unsigned char x = 0;
        unsigned char y = 0;
        float bright = 0;
    };

class tmml
{
  public:
    tmml(bool& ok, float& min_max_Val0);
    ~tmml();
    void cuda_Free();

    const Pix max_pix0;
    void work_tmml(const cv::Mat& img_work, const cv::Mat& img_temp, Pix& max_pix);
    Pix * maxValue(Pix *, Pix *, Pix *, Pix *);
    Pix max_pix = max_pix0;
    double maxVal = 0;
    cv::Mat img_result = cv::Mat(cv::Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, cv::Scalar(0));
    cv::Mat img_result2 = cv::Mat(cv::Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, cv::Scalar(0));
    cv::Mat img_result6 = cv::Mat(cv::Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, cv::Scalar(0));

  private:
    double minVal, min_max_Val;
    cv::Point minLoc, maxLoc;

#ifndef NO_GPU
    void cuda_Malloc();
    void init_matchers();
//    cv::cuda::GpuMat img_work_gpu;
    cv::cuda::GpuMat img_work_gpu_1;
    cv::cuda::GpuMat img_work_gpu_2;
    cv::cuda::GpuMat img_work_gpu_3;
    cv::cuda::GpuMat img_work_gpu_4;
    int blocks = 18;
    int threads = 288;
    const int numCudaTread = 4;
    cv::cuda::Stream st1;
    cv::cuda::Stream st2;
    cv::cuda::Stream st3;
    cv::cuda::Stream st4;

    cv::cuda::GpuMat img_temp_gpu;
    unsigned char  img_temp_arr[TEMPLATE_AREA];
    float error_Val = 0.f, min_max_Val2 = 0.f;
    int * dev_max_val0 = 0;
    int * dev_max_val_1 = dev_max_val0;
    int * dev_max_val_2 = dev_max_val0;
    int * dev_max_val_3 = dev_max_val0;
    int * dev_max_val_4 = dev_max_val0;

    Pix * dev_mp_1;
    Pix * dev_mp_2;
    Pix * dev_mp_3;
    Pix * dev_mp_4;
//    float * dev_result_array_bright;
#endif // END ifndef NO_GPU
}; // END class tmml
