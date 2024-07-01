#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "find_min_max.hpp"


QElapsedTimer eTimer;
quint64 timeSerial, timeParallel;


void workSerialEdge(QImage &imageIn, QImage &imageOut)
{
    eTimer.start();

    // Serial edge detector
    for (int y = 0; y < imageIn.height(); y++) {
        QRgb *iLine = (QRgb *) imageIn.scanLine(y);

        QRgb *iLine_m1 = (y < 1)?
                             iLine:
                             (QRgb *) imageIn.scanLine(y - 1);

        QRgb *iLine_p1 = (y >= imageIn.height())?
                             iLine:
                             (QRgb *) imageIn.scanLine(y + 1);

        QRgb *oLine = (QRgb *) imageOut.scanLine(y);

        for (int x = 0; x < imageIn.width(); x++)
        {
            int x_m = (x < 1)? x: x - 1;
            int x_p = (x >= imageIn.width())? x: x + 1;

            // Sobel operator
            int grayX = qRed(iLine_p1[x_m])
                      + 2 * qRed(iLine_p1[x])
                      + qRed(iLine_p1[x_p])
                      - qRed(iLine_m1[x_m])
                      - 2 * qRed(iLine_m1[x])
                      - qRed(iLine_m1[x_p]);

            int grayY = qRed(iLine_m1[x_p])
                      + 2 * qRed(iLine[x_p])
                      + qRed(iLine_p1[x_p])
                      - qRed(iLine_m1[x_m])
                      - 2 * qRed(iLine[x_m])
                      - qRed(iLine_p1[x_m]);

            int gray = sqrt(grayX * grayX + grayY * grayY);
            gray = qBound(0, gray, 255);

            oLine[x] = qRgb(gray, gray, gray);
        }
    }
    timeSerial = eTimer.nsecsElapsed();

    imageOut.save("edges-serial.jpg");
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    QImage imageIn("image.jpg");
    imageIn = imageIn.convertToFormat(QImage::Format_ARGB32);
    convertToGrey(imageIn);
    QImage imageOut(imageIn.size(), imageIn.format());

    workSerialEdge(imageIn, imageOut);
    if(workParallelEdge(imageIn, imageOut) != CL_SUCCESS)
        return -1;





    qDebug() << "serial   " << (float)timeSerial/1000000 << " ms";
    qDebug() << "parallel " << (float)timeParallel/1000000 << " ms";
    qDebug() << "serial/parallel=" << (float)timeSerial/timeParallel;



    return 0;
}
