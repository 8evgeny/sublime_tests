#include <chrono>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>

#define w 1000
using namespace cv;

void MyFilledCircle(Mat img, Point center);
void MyLine(Mat img, Point start, Point end);

int main(void)
{

    char atom_window[] = "Drawing 1: Atom";
    Mat atom_image = Mat::zeros(w, w, CV_8UC3);
    MyFilledCircle(atom_image, Point(100, 100));
    imshow(atom_window, atom_image);
    moveWindow(atom_window, 100, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    waitKey(0);
    return (0);
}

void MyFilledCircle(Mat img, Point center)
{
    circle(img,
        center,
        10,
        Scalar(0, 255, 0),
        FILLED,
        LINE_8);
}

void MyLine(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = LINE_8;
    line(img,
        start,
        end,
        Scalar(0, 0, 0),
        thickness,
        lineType);
}
