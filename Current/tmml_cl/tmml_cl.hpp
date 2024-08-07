#pragma once
#include "CL/cl.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
const int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
const int WORK_WIDTH = SOURCE_WIDTH - 1;
const int WORK_AREA = WORK_WIDTH * WORK_WIDTH;
const int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;
const int RESULT_AREA = RESULT_WIDTH * RESULT_WIDTH;
const int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_WIDTH;
//const float RESULT_AREA_1 = 1.f / RESULT_AREA;
//const float TEMPLATE_WIDTH_1 = 1.f / TEMPLATE_WIDTH;

#define KERNEL_FILE "tmml.cl"

#ifdef SQDIFF_NORMED
    #define KERNEL_tmml_cl_NAME1 "work_cl_2"
#endif
#ifdef CCOEFF_NORMED
    #define KERNEL_tmml_cl_NAME1 "work_cl_6"
#endif
#ifdef COMBINED
    #define KERNEL_tmml_cl_NAME1 "work_cl_8"
#endif

#define KERNEL_tmml_cl_NAME2 "work_cl_max"

struct Pix
{
    unsigned char x = 0;
    unsigned char y = 0;
    float bright = 0;
}; // END Pix

struct Templ
{
    unsigned char templ_arr[18][128]; //2304
}; // END Templ

//struct Work
//{
//    unsigned char result_arr[288][128]; //36864
//}; // END Templ


class tmml_cl
{
  public:
    tmml_cl(bool& ok, float& min_max_Val0);
    ~tmml_cl();

    cv::Mat img_result;
    void work_tmml(const cv::Mat & img_work, const cv::Mat & img_temp, Pix & max_pix);
    const Pix max_pix0;
    Pix max_pix = max_pix0;

  private:
    cv::UMat img_work_umat, img_temp_umat;
    unsigned char img_temp_arr[TEMPLATE_AREA];
    unsigned char img_work_arr[WORK_AREA];
    unsigned char img_result_x[RESULT_WIDTH];
    float img_result_bright[RESULT_WIDTH];
    std::string kernel_source{""};
    cl::Kernel tmml_cl_kernel1, tmml_cl_kernel2;
    cl::Buffer img_work_buff, img_temp_buff, img_result_buff, img_result_x_buff, img_result_bright_buff;
    cl::Buffer maxVal_int_buff, max_pix_buff;
    cl::CommandQueue qu;
    cl::Context context;
    cl::Program program;
    cl::Device default_device;
    std::vector<cl::Device> all_devices;
    cl::Platform default_platform;
    std::vector<cl::Platform> all_platforms;

    double min_max_Val = 0, min_max_Val2 = 0;
    double minVal = 0, maxVal = 0;
    cv::Point minLoc, maxLoc;
    int maxVal_int = 0;

    void initDevice(bool & init_OK);
    void loadAndBuildProgram(bool & init_OK, const std::string & programFile);
    std::string loadKernelFile(const std::string & program);
}; // END tmml_cl



