#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
extern QElapsedTimer eTimer;
extern quint64 timeSerial, timeParallel;


int testMatches()
{
    QImage imageIn("image");
    QImage imageTempl("template");

    imageIn = imageIn.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageIn);
    imageTempl = imageTempl.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageTempl);
    QImage imageOut(imageIn.size(), imageIn.format());




    workSerialMatches(imageIn, imageTempl, imageOut);

//    if(workParallelMatches(imageIn, imageOut) != CL_SUCCESS)
//        return -1;
//    qDebug() << "\nserialMatches   " << (float)timeSerial/1000000 << " ms";
//    qDebug() << "parallelMatches " << (float)timeParallel/1000000 << " ms";
//    qDebug() << "serial/parallel=" << (float)timeSerial/timeParallel;
    return 0;

}
