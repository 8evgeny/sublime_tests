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

#ifdef SQDIFF_NORMED
    #define KERNEL_NAME "work_cl_2"
#endif
#ifdef CCOEFF_NORMED
    #define KERNEL_NAME "work_cl_6"
#endif
#ifdef COMBINED
    #define KERNEL_NAME "work_cl_8"
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

    cv::Mat img_result;
    void work_tmml(const cv::Mat & img_work, const cv::Mat & img_temp, Pix & max_pix);
    const Pix max_pix0;
    Pix max_pix = max_pix0;

  private:
    unsigned char img_temp_arr[TEMPLATE_AREA];
    unsigned char img_work_arr[WORK_AREA];
    std::string kernel_source{""};
    cl::Kernel tmml_cl_kernel;
    cl::Buffer img_work_buff, img_temp_buff, img_result_buff;
    cl::CommandQueue queue;
    cl::Context context;
    cl::Program program;
    cl::Device default_device;
    std::vector<cl::Device> all_devices;
    cl::Platform default_platform;
    std::vector<cl::Platform> all_platforms;
    std::unique_ptr<cl_uchar[]> imageData_ptr = nullptr;
    std::unique_ptr<cl_uchar[]> templateData_ptr = nullptr;

    double min_max_Val = 0, min_max_Val2 = 0;
    double minVal = 0, maxVal = 0;
    cv::Point minLoc, maxLoc;

    void initDevice(bool & init_OK);
    void loadAndBuildProgram(bool & init_OK, const std::string & programFile);
    std::string loadKernelFile(const std::string & program);

#ifndef KernelFromFile
    const std::string programm_CL //  \n ->  \\n"\n"
    {
        "__constant int TEMPLATE_WIDTH = 48;\n"
        "__constant int TEMPLATE_HEIGHT = 48;\n"
        "__constant int EXT_VAL = 5;\n"
        "__constant int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;\n"
        "__constant int SOURCE_HEIGHT = EXT_VAL * TEMPLATE_HEIGHT;\n"
        "__constant int WORK_WIDTH = SOURCE_WIDTH - 1;\n"
        "__constant int WORK_HEIGHT = SOURCE_HEIGHT - 1;\n"
        "__constant int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1;\n"
        "__constant int RESULT_HEIGHT = WORK_HEIGHT - TEMPLATE_HEIGHT + 1;\n"
        "__constant int RESULT_AREA = RESULT_WIDTH * RESULT_HEIGHT;\n"
        "__constant int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;\n"
        "__constant float RESULT_AREA_1 = 1.f / RESULT_AREA;\n"
        "__constant float TEMPLATE_AREA_1 = 1.f / TEMPLATE_AREA;\n"
        "\n"
        "\n"
        "__kernel void work_cl_6(__global unsigned char * img_work,\n"
        "                        __global unsigned char * img_temp,\n"
        "                        __global float * img_result)\n"
        "{\n"
        "//    int result_x = get_global_id(0);\n"
        "//    int result_y = get_global_id(1);\n"
        "    int result_id = get_global_id(0);\n"
        "    int result_y = result_id / RESULT_WIDTH;\n"
        "    int result_x = result_id % RESULT_WIDTH;\n"
        "    int sum_roi_temp = 0;\n"
        "    int sum_temp_temp = 0;\n"
        "    int sum_roi_roi = 0;\n"
        "    int sum_roi = 0;\n"
        "    int sum_temp = 0;\n"
        "    int temp_id = 0;\n"
        "    for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)\n"
        "    {\n"
        "        int roi_id0 = (result_y + tmp_y) * WORK_WIDTH + result_x;\n"
        "        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)\n"
        "        {\n"
        "            unsigned char temp = img_temp[temp_id];\n"
        "            unsigned char roi = img_work[roi_id0 + tmp_x];\n"
        "            sum_roi_temp += roi * temp;\n"
        "            sum_temp_temp += temp * temp;\n"
        "            sum_roi_roi += roi * roi;\n"
        "            sum_roi += roi;\n"
        "            sum_temp += temp;\n"
        "            temp_id++;\n"
        "        } // END for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)\n"
        "    } // END for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)\n"
        "    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;\n"
        "    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;\n"
        "    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;\n"
        "    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;\n"
        "    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;\n"
        "    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;\n"
        "    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;\n"
        "    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;\n"
        "    img_result[result_id] = ch / sqrt(zn1 * zn2);\n"
        "} // END void work_cl_6\n"
        "\n"
        "\n"
        "__kernel void work_cl_8(__global unsigned char * img_work,\n"
        "                        __global unsigned char * img_temp,\n"
        "                        __global float * img_result)\n"
        "{\n"
        "//    int result_x = get_global_id(0);\n"
        "//    int result_y = get_global_id(1);\n"
        "    int result_id = get_global_id(0);\n"
        "    int result_y = result_id / RESULT_WIDTH;\n"
        "    int result_x = result_id % RESULT_WIDTH;\n"
        "    int sum_roi_temp = 0;\n"
        "    int sum_roi_temp_2 = 0;\n"
        "    int sum_temp_temp = 0;\n"
        "    int diff_roi_temp = 0;\n"
        "    int sum_roi_roi = 0;\n"
        "    int sum_roi = 0;\n"
        "    int sum_temp = 0;\n"
        "    int temp_id = 0;\n"
        "    for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)\n"
        "    {\n"
        "        int roi_id0 = (result_y + tmp_y) * WORK_WIDTH + result_x;\n"
        "        for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)\n"
        "        {\n"
        "            int temp = img_temp[temp_id];\n"
        "            int roi = img_work[roi_id0 + tmp_x];\n"
        "            sum_roi_temp += roi * temp;\n"
        "            sum_temp_temp += temp * temp;\n"
        "            sum_roi_roi += roi * roi;\n"
        "            sum_roi += roi;\n"
        "            sum_temp += temp;\n"
        "            diff_roi_temp += abs(roi - temp);\n"
        "            sum_roi_temp_2 += (roi + temp);\n"
        "            temp_id++;\n"
        "        } // END for(int tmp_x = 0; tmp_x < TEMPLATE_WIDTH; ++tmp_x)\n"
        "    } // END for(int tmp_y = 0; tmp_y < TEMPLATE_HEIGHT; ++tmp_y)\n"
        "    const float sum_roi_temp1 = TEMPLATE_AREA_1 * sum_roi_temp;\n"
        "    const float sum_roi1 = TEMPLATE_AREA_1 * sum_roi;\n"
        "    const float sum_temp1 = TEMPLATE_AREA_1 * sum_temp;\n"
        "    const float sum_roi_roi1 = TEMPLATE_AREA_1 * sum_roi_roi;\n"
        "    const float sum_temp_temp1 = TEMPLATE_AREA_1 * sum_temp_temp;\n"
        "    const float ch  = sum_roi_temp1 - sum_roi1 * sum_temp1;\n"
        "    const float zn1 = sum_temp_temp1 - sum_temp1 * sum_temp1;\n"
        "    const float zn2 = sum_roi_roi1 - sum_roi1 * sum_roi1;\n"
        "    img_result[result_id] = ch / sqrt(zn1 * zn2) - (float)diff_roi_temp / sum_roi_temp_2;\n"
        "} // END tmml_cl_8\n"
    };
#endif

}; // END tmml_cl

