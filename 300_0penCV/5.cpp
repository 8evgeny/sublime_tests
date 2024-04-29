#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat src1 = imread("../1.jpeg", IMREAD_GRAYSCALE);
    uchar pixel1=src1.at<uchar>(0,0);
    cout << "Значение пикселя (0,0): " << (unsigned int)pixel1 << endl;
    Mat src2 = imread("../1.jpeg", IMREAD_COLOR);
    Vec3b pixel2 = src2.at<Vec3b>(0,0);
    cout << "Компонента B пикселя (0,0):" << (unsigned int)pixel2[0] << endl;
    cout << "Компонента G пикселя (0,0):" << (unsigned int)pixel2[1] << endl;
    cout << "Компонента R пикселя (0,0):" << (unsigned int)pixel2[2] << endl;
}
