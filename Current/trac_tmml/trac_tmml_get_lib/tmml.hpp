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

#ifdef GPU_AMPERE
    const int threads_match_temp = 128; // 256
    const int threads_maxloc = 128;
    // Число элементов массива внутри нити CUDA:
    const int K1 = 16;
    const int K2 = 12;
#endif // END ifdef GPU3090

#ifdef GPU_VOLTA
    const int threads_match_temp = 128;
    const int threads_maxloc = 64;
    // Число элементов массива внутри нити CUDA:
    const int K1 = 12;
    const int K2 = 12;
#endif  // END ifdef GPU_XAVIER_NX

#ifndef NO_GPU
    const float threads_match_temp_1 = 1.f / threads_match_temp;

    // Число нитей CUDA в итерации:
    const int N1 = RESULT_WIDTH * RESULT_WIDTH / K1; // 6144;
    const int N2 = N1 / K2; // 1024;
    const int blocks_match_temp = RESULT_AREA * threads_match_temp_1;
    const int batch_size = TEMPLATE_AREA;
    const int blocks_maxloc = N1 / threads_maxloc;
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
    void cuda_Malloc();
    void fill_result_array();
    void fill1level();

    const Pix max_pix0;
    void work_tmml(const cv::Mat& img_work, const cv::Mat& img_temp, Pix& max_pix);
    Pix max_pix = max_pix0;
    double maxVal = 0;
    cv::Mat img_result = cv::Mat(cv::Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, cv::Scalar(0));
    cv::Mat img_result2 = cv::Mat(cv::Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, cv::Scalar(0));
    cv::Mat img_result6 = cv::Mat(cv::Size(RESULT_WIDTH, RESULT_WIDTH), CV_32FC1, cv::Scalar(0));
    float * dev_result_array_bright;
    float result_array_bright[RESULT_AREA];

    unsigned char *dev_result_array_x, *dev_result_array_y;
    unsigned char *dev_template_array_x, *dev_template_array_y;
    unsigned char result_array_x[RESULT_AREA], result_array_y[RESULT_AREA];
    unsigned char template_array_x[TEMPLATE_AREA], template_array_y[TEMPLATE_AREA];
    double min_max_Val = 0;
    float min_max_Val2 = 0.f;

  private:
    double minVal;
    cv::Point minLoc, maxLoc;

#ifndef NO_GPU
    void init_matchers();
    void fill_template_array();

    cv::cuda::GpuMat img_work_gpu, img_temp_gpu;
    unsigned char first_level_x[N1], first_level_y[N1];
    Pix *dev_max_K1, *dev_max_K2;
    Pix max_K1[N1], max_K2[N2];

    unsigned char  img_temp_arr[TEMPLATE_AREA];
    float error_Val = 0.f;
#endif // END ifndef NO_GPU
}; // END class tmml
