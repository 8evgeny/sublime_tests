#pragma once
#include <CL/cl.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

const int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
const int SOURCE_HEIGHT = EXT_VAL * TEMPLATE_HEIGHT;
const int WORK_WIDTH = SOURCE_WIDTH - 1;
const int WORK_HEIGHT = SOURCE_HEIGHT - 1;
const int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;
const int RESULT_HEIGHT = WORK_HEIGHT - TEMPLATE_HEIGHT + 1;
const int RESULT_AREA = RESULT_WIDTH * RESULT_HEIGHT;
const int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;
const float RESULT_AREA_1 = 1.f / RESULT_AREA;
const float TEMPLATE_WIDTH_1 = 1.f / TEMPLATE_WIDTH;

constexpr int temp_center_x = 150;
constexpr int temp_center_y = 165;
constexpr int temp_left = temp_center_x - 0.5 * TEMPLATE_WIDTH;
constexpr int temp_top = temp_center_y - 0.5 * TEMPLATE_HEIGHT;

#define KERNEL_FILE "tmml.cl"
#define KERNEL_NAME "tmml_cl"

class tmml_cl
{
  public:
    tmml_cl(bool & init_OK, const int temp_left, const int temp_top, const cv::Mat & img_work, const cv::Mat & img_temp );
    ~tmml_cl();

    struct result
    {
        int xpos = 0, ypos = 0;
        cl_uint tm_result = 0;
    };

    const int k_float_to_int = K_FLOAT_TO_INT;
    void initDevice(bool & init_OK);
    void loadAndBuildProgram(bool & init_OK, const std::string & programFile);
    void loadDataMatToUchar(unsigned char *data, const cv::Mat &image, const int nchannels);
    void uintToMat(const unsigned int *data, cv::Mat &image);
    std::string loadKernelFile(const std::string program);
    int matchingCL(const cv::Mat& img_work, const cv::Mat& img_temp );
    result res;
    std::unique_ptr<cl_uint[]> mData_ptr = nullptr;
    int temp_leftOK = 0;
    int temp_topOK = 0;

  private:
    std::string kernel_source{""};
    cl::Kernel clkProcess;
    cl::Buffer clInputImg, clInputTemp, clInputRes, clInputK_FLOAT_TO_INT, clInputMaxVal, clResults, clMatchMethod, clmData;
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




