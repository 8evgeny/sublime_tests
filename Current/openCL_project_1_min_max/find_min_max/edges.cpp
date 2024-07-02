#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
extern QElapsedTimer eTimer;
extern quint64 timeSerial, timeParallel;

int testEdges()
{
    QImage imageIn("image");
    imageIn = imageIn.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageIn);
    QImage imageOut(imageIn.size(), imageIn.format());

    workSerialEdges(imageIn, imageOut);


//    QImage imageIn2("image");
//    imageIn2 = imageIn2.convertToFormat(QImage::Format_ARGB32);
//    convertToGrey(imageIn2);

//    imageIn2.save("in.png");
//    QImage imageOut2(imageIn2.size(), imageIn2.format());
//    imageOut2 = imageIn2;

    if(workParallelEdges(imageIn, imageOut) != CL_SUCCESS)
        return -1;
    qDebug() << "serialEdges   " << (float)timeSerial/1000000 << " ms";
    qDebug() << "parallelEdges " << (float)timeParallel/1000000 << " ms";
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
