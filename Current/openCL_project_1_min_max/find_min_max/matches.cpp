#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
extern QElapsedTimer eTimer;
extern quint64 timeSerial, timeParallel;


int testMatches()
{
    workSerialMatchesOpenCV();

    QImage imageIn("image");
    imageIn = imageIn.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageIn);
    QImage imageOut(imageIn.size(), imageIn.format());

    if(workParallelMatches(imageIn, imageOut) != CL_SUCCESS)
        return -1;

    return 0;

}
