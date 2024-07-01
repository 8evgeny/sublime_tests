#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "find_min_max.hpp"
extern QElapsedTimer eTimer;
extern quint64 timeSerial, timeParallel;

int testEdge()
{
    QImage imageIn("image");
    imageIn = imageIn.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageIn);
    QImage imageOut(imageIn.size(), imageIn.format());

    workSerialEdge(imageIn, imageOut);
    if(workParallelEdge(imageIn, imageOut) != CL_SUCCESS)
        return -1;
    qDebug() << "serialEdge   " << (float)timeSerial/1000000 << " ms";
    qDebug() << "parallelEdge " << (float)timeParallel/1000000 << " ms";
    qDebug() << "serial/parallel=" << (float)timeSerial/timeParallel;
    return 0;
}

void convertToGrey(QImage &imageIn)
{
    // Convert to gray scale
    for (int y = 0; y < imageIn.height(); y++)
    {
        QRgb *line = (QRgb *) imageIn.scanLine(y);

        for (int x = 0; x < imageIn.width(); x++)
        {
            int r = qGray(line[x]);
            int g = r;
            int b = r;
            line[x] = qRgb(r, g, b);
        }
    }
}
