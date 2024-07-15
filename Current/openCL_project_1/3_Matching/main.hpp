#pragma once
#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define WORKGROUPSIZE 1024
//#define NUM_ITERATIONS_GPU  100

enum matchMetod
{
    TM_SQDIFF = 0,
    TM_SQDIFF_NORMED,
    TM_CCORR,
    TM_CCORR_NORMED,
    TM_CCOEFF,
    TM_CCOEFF_NORMED
};

struct result
{
    int xpos, ypos;
    uint SAD;
};

void matchesOpenCV();
void MatchingMethod( int, void* );

int matchesGPU();

inline void calculateNDRange(int size, int groupSize, int *bSize, int *bGroupSize, int *oSize);
void convertToGrey(QImage &imageIn);

void qimage_to_mat(const QImage& image, cv::OutputArray out);
void mat_to_qimage(cv::InputArray image, QImage& out);
void loadDataMatToUchar(uchar *data, cv::Mat &image, int nchannels);
void ucharToMat(uchar *data,cv::Mat &image);


