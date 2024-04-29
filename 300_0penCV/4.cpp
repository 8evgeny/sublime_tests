#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    string name1 = "original";
    string name2 = "result";
    namedWindow(name1, WINDOW_AUTOSIZE);
    namedWindow(name2, WINDOW_AUTOSIZE);
    Mat m1 = Mat(300, 300, CV_32FC1);
    randu(m1, 0, 1e6); // случайное значение от 0 до 1e6
    imshow(name1, m1);
    double minRange,MaxRange;
    Point mLoc,MLoc;
    minMaxLoc(m1,&minRange,&MaxRange,&mLoc,&MLoc);
    Mat img1;
    m1.convertTo(img1,CV_8U,255.0/(MaxRange-minRange),-255.0/minRange);

    imshow(name2, img1);
    cout << "Для выхода нажмите 0..." << endl;
    moveWindow(name1, 300, 200);
    moveWindow(name2, 800, 200);
    waitKey(0); // Бесконечный цикл обработки событий
    return 0;
}
