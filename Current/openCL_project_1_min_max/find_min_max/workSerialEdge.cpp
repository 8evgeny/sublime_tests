#include <QtCore>
#include <QImage>
#include "find_min_max.hpp"

extern QElapsedTimer eTimer;
extern quint64 timeSerial;


void workSerialEdge(QImage &imageIn, QImage &imageOut)
{
    eTimer.restart();

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
