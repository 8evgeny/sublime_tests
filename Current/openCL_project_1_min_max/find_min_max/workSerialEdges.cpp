#include <QtCore>
#include <QImage>
#include "main.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

extern QElapsedTimer eTimer;
extern quint64 timeSerial;

using namespace std;
using namespace cv;

void workSerialEdges(QImage &imageIn, QImage &imageOut)
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

    imageOut.save("edges-serial.png");

    Mat edges = imread("edges-serial.png", IMREAD_GRAYSCALE);
    imshow("result edges serial", edges );
    waitKey(0);
}

void workSerialEdgesOpenCV()
{
  Mat img = imread("image.jpg", IMREAD_COLOR );
  // Convert to graycsale
  Mat img_gray;
  cvtColor(img, img_gray, COLOR_BGR2GRAY);

  // Blur the image for better edge detection
  Mat img_blur;
  GaussianBlur(img_gray, img_blur, Size(3,3), 0);

    eTimer.restart();

  // Sobel edge detection

//  Mat sobelx, sobely, sobelxy;
//  Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
//  Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
//  Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);
//  imshow("Sobel X", sobelx);
//  waitKey(0);
//  imshow("Sobel Y", sobely);
//  waitKey(0);
//  imshow("Sobel XY using Sobel() function", sobelxy);
//  waitKey(0);


    // Canny edge detection
    Mat edges;
    Canny(img_gray, edges, 100, 200, 3, false);
//    Canny(img_blur, edges, 100, 200, 3, false);

    timeSerial = eTimer.nsecsElapsed();

    imshow("result edges OpenCV", edges);
    waitKey(0);

    destroyAllWindows();







}
