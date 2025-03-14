#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#define w 400
using namespace cv;
void MyEllipse(Mat img, double angle);
void MyFilledCircle(Mat img, Point center);
void MyPolygon(Mat img);
void MyLine(Mat img, Point start, Point end);
int main(void)
{
    char atom_window[] = "Drawing 1: Atom";
    char rook_window[] = "Drawing 2: Rook";
    Mat atom_image = Mat::zeros(w, w, CV_8UC3);
    Mat rook_image = Mat::zeros(w, w, CV_8UC3);
    MyEllipse(atom_image, 90);
    MyEllipse(atom_image, 0);
    MyEllipse(atom_image, 45);
    MyEllipse(atom_image, -45);
    MyFilledCircle(atom_image, Point(w / 2, w / 2));
    MyPolygon(rook_image);
    rectangle(rook_image,
        Point(0, 7 * w / 8),
        Point(w, w),
        Scalar(0, 255, 255)/*,*/
/*        FILLED,
        LINE_8*/);
    MyLine(rook_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
    MyLine(rook_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
    MyLine(rook_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
    MyLine(rook_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));
    imshow(atom_window, atom_image);
    moveWindow(atom_window, 0, 200);
    imshow(rook_window, rook_image);
    moveWindow(rook_window, w, 200);
    waitKey(0);
    return (0);
}
void MyEllipse(Mat img, double angle)
{
    int thickness = 2;
    int lineType = 8;
    ellipse(img,
        Point(w / 2, w / 2),
        Size(w / 4, w / 16),
        angle,
        0,
        360,
        Scalar(255, 0, 0),
        thickness,
        lineType);
}
void MyFilledCircle(Mat img, Point center)
{
    circle(img,
        center,
        w / 32,
        Scalar(0, 0, 255)/*,
        FILLED,
        LINE_8*/);
}
void MyPolygon(Mat img)
{
    int lineType = 8/*LINE_8*/;
    Point rook_points[1][4];
    rook_points[0][0] = Point(0, 0);
    rook_points[0][1] = Point(300, 0);
    rook_points[0][2] = Point(300, 200);
    rook_points[0][3] = Point(0, 200);

    const Point* ppt[1] = { rook_points[0] };
    int npt[] = { 4 };
    fillPoly(img,
        ppt,
        npt,
        1,
        Scalar(255, 255, 255),
        lineType);
}
void MyLine(Mat img, Point start, Point end)
{
    int thickness = 2;
    int lineType = 8/*LINE_8*/;
    line(img,
        start,
        end,
        Scalar(0, 0, 0),
        thickness,
        lineType);
}
