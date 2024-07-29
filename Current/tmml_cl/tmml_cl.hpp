#pragma once
#include "CL/cl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
const int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
const int SOURCE_HEIGHT = EXT_VAL * TEMPLATE_HEIGHT;
const int WORK_WIDTH = SOURCE_WIDTH - 1;
const int WORK_HEIGHT = SOURCE_HEIGHT - 1;
const int WORK_AREA = WORK_WIDTH * WORK_HEIGHT;
const int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;
const int RESULT_HEIGHT = WORK_HEIGHT - TEMPLATE_HEIGHT + 1;
const int RESULT_AREA = RESULT_WIDTH * RESULT_HEIGHT;
const int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;
const float RESULT_AREA_1 = 1.f / RESULT_AREA;
const float TEMPLATE_WIDTH_1 = 1.f / TEMPLATE_WIDTH;

#define KERNEL_FILE "tmml.cl"
#ifndef testCL
    #ifdef find_diff_result
        #ifdef CCOEFF_NORMED
            #define KERNEL_NAME "work_cl_6"
        #endif
        #ifdef COMBINED
            #define KERNEL_NAME "work_cl_8"
        #endif
    #endif
    #ifndef find_diff_result
        #ifdef CCOEFF_NORMED
            #define KERNEL_NAME "work_cl_6_no_img"
        #endif
        #ifdef COMBINED
            #define KERNEL_NAME "work_cl_8_no_img"
        #endif
    #endif
#endif
#ifdef testCL
    #define KERNEL_NAME "work_cl_test"
#endif

struct Pix
{
    unsigned char x = 0;
    unsigned char y = 0;
    float bright = 0;
}; // END Pix

class tmml_cl
{
  public:
    tmml_cl(bool& ok, float& min_max_Val0);
    ~tmml_cl();

    struct result
    {
        int xpos = 0;
        int ypos = 0;
        cl_uint tm_result = 0;
    }; // END result

    const Pix max_pix0;
    Pix max_pix = max_pix0;

    void initDevice(bool & init_OK);
    void loadAndBuildProgram(bool & init_OK, const std::string & programFile);
    void loadDataMatToUchar(unsigned char *data, const cv::Mat &image);
    void uintToMat(const unsigned int *data, cv::Mat &image);
    std::string loadKernelFile(const std::string program);
    int work_tmml(const cv::Mat& img_work, const cv::Mat& img_temp, Pix& max_pix);
    result res;
    std::unique_ptr<cl_uint[]> mData_ptr = nullptr;

  private:
    std::string kernel_source{""};
    cl::Kernel clkProcess;
    cl::Buffer clInputImg, clInputTemp, clInputRes, clInputMaxVal;
#ifdef find_diff_result
    cl::Buffer clmData;
#endif
    cl::CommandQueue queue;
    cl::Context context;
    cl::Program program;
    cl::Device default_device;
    std::vector<cl::Device> all_devices;
    cl::Platform default_platform;
    std::vector<cl::Platform> all_platforms;
    std::unique_ptr<cl_uchar[]> imageData_ptr = nullptr;
    std::unique_ptr<cl_uchar[]> templateData_ptr = nullptr;

    int minVal = 0;
    int maxVal = 0;

}; // END tmml_cl



