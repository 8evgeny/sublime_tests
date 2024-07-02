#pragma once
#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>

#define WORKGROUPSIZE 16
int workParallelEdges(QImage &imageIn, QImage &imageOut);
void workSerialEdges(QImage &imageIn, QImage &imageOut);
inline void calculateNDRange(int size, int groupSize, int *bSize, int *bGroupSize, int *oSize);
void convertToGrey(QImage &imageIn);
int testEdges();

int testMatches();
void workSerialMatches();
