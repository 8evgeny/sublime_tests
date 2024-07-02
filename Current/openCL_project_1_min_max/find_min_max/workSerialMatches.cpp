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


void workSerialMatches()
{
//    imageIn.save("matches-in.png");
//    imageTempl.save("matches-templ.png");
    eTimer.restart();
//    Mat matIn(imageIn.height(), imageIn.width(), CV_8UC1, (cv::Scalar*)imageIn.scanLine(0));
    Mat img_source = imread("image", CV_8UC1);
    imshow("matIn", img_source);
    Mat img_templ = imread("template", CV_8UC1);
    imshow("matTempl", img_templ);
    waitKey(0);
    Mat matOut;

//    Mat matTempl(imageTempl.height(), imageTempl.width(), CV_8UC1, (cv::Scalar*)imageTempl.scanLine(0));
//    Mat matOut(imageOut.height(), imageOut.width(), CV_8UC1, (cv::Scalar*)imageOut.scanLine(0));
    matchTemplate( img_source, img_templ, matOut, TM_SQDIFF);
    imshow("matOut", matOut);
    waitKey(0);
//    imageOut = QImage((uchar*) matOut.data, /*matOut.cols*/640, /*matOut.rows*/480, matOut.step, QImage::Format_Grayscale8/*Format_RGB888*/);
    timeSerial = eTimer.nsecsElapsed();

//    imageOut.save("matches-serial.png");
}
