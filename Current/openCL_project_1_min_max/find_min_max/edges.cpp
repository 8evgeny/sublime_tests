#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
extern QElapsedTimer eTimer;
extern quint64 timeSerial, timeParallel;

int testEdges()
{
//    workSerialEdges();
//    qDebug() << "serialEdges   " << (float)timeSerial/1000000 << " ms";

//    workSerialEdgesOpenCV();
//    qDebug() << "serialEdgesOpenCV   " << (float)timeSerial/1000000 << " ms";

    if(workParallelEdges() != CL_SUCCESS)
        return -1;

//    qDebug() << "parallelEdges " << (float)timeParallel/1000000 << " ms";
//    qDebug() << "serial/parallel=" << (float)timeSerial/timeParallel;
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
