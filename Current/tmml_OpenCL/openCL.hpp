#pragma once
#include <CL/cl.hpp>
#include "openCL.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <QtCore>

#define KERNEL_FILE "matching.cl"
#define KERNEL_NAME "matching"

struct result
{
    int xpos, ypos;
    cl_uint tm_result;
};

int initDevice();
int loadAndBuildProgram(std::string programFile);
int matchingOpenCL();
inline void calculateNDRange(int size, int groupSize, int *bSize, int *bGroupSize, int *oSize);
void loadDataMatToUchar(uchar *data, cv::Mat &image, int nchannels);
void ucharToMat(uchar *data,cv::Mat &image);

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
