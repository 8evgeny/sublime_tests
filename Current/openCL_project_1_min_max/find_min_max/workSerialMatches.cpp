#include <QtCore>
#include <QImage>
#include "main.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

extern QElapsedTimer eTimer;
extern quint64 timeSerial;


void workSerialMatches(QImage &imageIn, QImage &imageTempl, QImage &imageOut)
{
    imageIn.save("matches-in.png");
    imageTempl.save("matches-templ.png");
    eTimer.restart();
    Mat matIn(imageIn.height(), imageIn.width(), CV_8UC3, (cv::Scalar*)imageIn.scanLine(0));
    Mat matTempl(imageTempl.height(), imageTempl.width(), CV_8UC3, (cv::Scalar*)imageTempl.scanLine(0));
    Mat matOut(imageOut.height(), imageOut.width(), CV_8UC3, (cv::Scalar*)imageOut.scanLine(0));
    matchTemplate( matIn, matTempl, matOut, TM_SQDIFF);
    imageOut = QImage((uchar*) matOut.data, /*matOut.cols*/640, /*matOut.rows*/480, matOut.step, QImage::Format_Grayscale8/*Format_RGB888*/);
    timeSerial = eTimer.nsecsElapsed();
    imageOut.save("matches-serial.png");
}
