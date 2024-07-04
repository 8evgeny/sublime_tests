#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
extern QElapsedTimer eTimer;
extern quint64 timeSerial, timeParallel;


int Matches()
{
//    serialMatches(); //Не реализовано
//    serialMatchesOpenCV();

    QImage imageIn("image");
    imageIn = imageIn.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageIn);

    QImage imageTempl("template");
    imageIn = imageTempl.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageTempl);

     QImage imageOut(imageIn.size(), imageIn.format());


    if(parallelMatches(imageIn, imageTempl, imageOut) != CL_SUCCESS)
        return -1;

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
