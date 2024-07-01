#include <QtCore>
#include <QImage>
#include "main.hpp"

extern QElapsedTimer eTimer;
extern quint64 timeSerial;


void workSerialMatches(QImage &imageIn, QImage &imageTempl, QImage &imageOut)
{
    imageIn.save("matches-in.png");
    imageTempl.save("matches-templ.png");
    eTimer.restart();







    timeSerial = eTimer.nsecsElapsed();
    imageOut.save("matches-serial.png");
}
