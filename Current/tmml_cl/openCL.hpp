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

struct result
{
    int xpos, ypos;
    cl_uint tm_result;
};
struct PixCL
{
    int x = 0;
    int y = 0;
    PixCL(int left, int top)
    {
        x = left;
        y = top;
    }
};

class tmml_cl
{
  public:
    tmml_cl();
    ~tmml_cl();

    int initDevice();
    int loadAndBuildProgram(std::string programFile);
    void loadDataMatToUchar(uchar *data, const cv::Mat &image, int nchannels);
    void uintToMat(uint *data,cv::Mat &image);
    string loadKernelFile(string program);
    int matchingOpenCL(std::unique_ptr<tmml_cl> & tm_cl, const cv::Mat& img_work, const cv::Mat& img_temp, cv::Mat& img_result_CL, int match_method, int iter_num, PixCL & pixOK, result & res );

  private:



}; // END tmml_cl






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
