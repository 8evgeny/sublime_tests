#pragma once
#include <CL/cl.hpp>
#include "openCL.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cl;

const int SOURCE_WIDTH = EXT_VAL * TEMPLATE_WIDTH;
const int SOURCE_HEIGHT = EXT_VAL * TEMPLATE_HEIGHT;
const int WORK_WIDTH = SOURCE_WIDTH - 1;
const int WORK_HEIGHT = SOURCE_HEIGHT - 1;
const int RESULT_WIDTH = WORK_WIDTH - TEMPLATE_WIDTH + 1; // 192
const int RESULT_HEIGHT = WORK_HEIGHT - TEMPLATE_HEIGHT + 1; // 192
const int RESULT_AREA = RESULT_WIDTH * RESULT_HEIGHT;
const int TEMPLATE_AREA = TEMPLATE_WIDTH * TEMPLATE_HEIGHT;
const float RESULT_AREA_1 = 1.f / RESULT_AREA;
const float TEMPLATE_WIDTH_1 = 1.f / TEMPLATE_WIDTH;

#define KERNEL_FILE "matching.cl"
#define KERNEL_NAME "matchingCL"

class tmml_cl
{
  public:
    tmml_cl(int temp_leftOK, int temp_topOK);
    ~tmml_cl();

    struct result
    {
        int xpos, ypos;
        cl_uint tm_result;
    };

    enum matchMetod
    {
        TM_SQDIFF = 0,
        TM_SQDIFF_NORMED,
        TM_CCORR,
        TM_CCORR_NORMED,
        TM_CCOEFF,
        TM_CCOEFF_NORMED,
        TM_COMBINED
    };

    int initDevice();
    int loadAndBuildProgram(std::string programFile);
    void loadDataMatToUchar(uchar *data, const cv::Mat &image, int nchannels);
    void uintToMat(uint *data,cv::Mat &image);
    string loadKernelFile(string program);
    int initOpenCL(const cv::Mat& img_work, const cv::Mat& img_temp, int match_method );
    int matchingCL(const cv::Mat& img_work, const cv::Mat& img_temp );
    result res;
    unique_ptr<cl_uint[]> mData;
    int temp_leftOK;
    int temp_topOK;

  private:
    string kernel_source;
    Kernel clkProcess;
    Buffer clInputImg, clInputTemp, clInputRes, clInputMinVal, clInputMaxVal, clResults, clMatchMethod, clmData;
    CommandQueue queue;
    Context context;
    Program program;
    Device default_device;
    vector<Device> all_devices;
    Platform default_platform;
    vector<Platform> all_platforms;
    unique_ptr<cl_uchar[]> imageData;
    unique_ptr<cl_uchar[]> templateData;

    int minVal = 0;
    int maxVal = 0;

}; // END tmml_cl




