#pragma once
#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>


#define WORKGROUPSIZE 16

int testEdges();
void workSerialEdges(QImage &imageIn, QImage &imageOut);
int workParallelEdges(QImage &imageIn, QImage &imageOut);
inline void calculateNDRange(int size, int groupSize, int *bSize, int *bGroupSize, int *oSize);
void convertToGrey(QImage &imageIn);

int testMatches();
void workSerialMatchesOpenCV();
int workParallelMatches(QImage &imageIn, QImage &imageOut);
