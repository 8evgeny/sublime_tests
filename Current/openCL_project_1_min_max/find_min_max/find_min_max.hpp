#pragma once
#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>

#define WORKGROUPSIZE 16
int workParallelEdge(QImage &imageIn, QImage &imageOut);
inline void calculateNDRange(int size, int groupSize,
                             int *bSize, int *bGroupSize, int *oSize);
