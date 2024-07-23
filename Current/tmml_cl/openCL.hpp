#pragma once
#include <CL/cl.hpp>
#include "openCL.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;

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
    int initOpenCL(std::unique_ptr<tmml_cl> & tm_cl, const cv::Mat& img_work, const cv::Mat& img_temp, cv::Mat& img_result_CL, int match_method, int iter_num );
    int matchingOpenCL(std::unique_ptr<tmml_cl> & tm_cl, const cv::Mat& img_work, const cv::Mat& img_temp, cv::Mat& img_result_CL, int match_method, int iter_num );
    result res;

  private:
    int temp_leftOK;
    int temp_topOK;
    string kernel_source;
    cl::Kernel clkProcess;
    cl::Buffer clInputImg, clInputTemp, clInputRes, clInputMinVal, clInputMaxVal, clResults, clMatchMethod, clmData;
    cl::CommandQueue queue;
    cl::Context context;
    cl::Program program;
    cl::Device default_device;
    std::vector<cl::Device> all_devices;
    cl::Platform default_platform;
    vector<cl::Platform> all_platforms;
    unique_ptr<cl_uchar[]> imageData;
    unique_ptr<cl_uchar[]> templateData;
    unique_ptr<cl_uint[]> mData;

}; // END tmml_cl




