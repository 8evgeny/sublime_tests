#pragma once
#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define WORKGROUPSIZE 16

int Matches();
void matchesOpenCV();
int matches();
void MatchingMethod( int, void* );
int parallelMatches();

inline void calculateNDRange(int size, int groupSize, int *bSize, int *bGroupSize, int *oSize);
void convertToGrey(QImage &imageIn);

void qimage_to_mat(const QImage& image, cv::OutputArray out);
void mat_to_qimage(cv::InputArray image, QImage& out);
