#pragma once
#include <CL/cl.hpp>
#include "openCL.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>

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


  private:



}; // END tmml_cl


int matchingOpenCL(std::unique_ptr<tmml_cl> & tm_cl, const cv::Mat& img_work, const cv::Mat& img_temp, cv::Mat& img_result_CL, int match_method, int iter_num, PixCL & pixOK, result & res );
inline void calculateNDRange(int size, int groupSize, int *bSize, int *bGroupSize, int *oSize);
void loadDataMatToUchar(uchar *data, const cv::Mat &image, int nchannels);
void ucharToMat(uchar *data,cv::Mat &image);
void uintToMat(uint *data,cv::Mat &image);

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
