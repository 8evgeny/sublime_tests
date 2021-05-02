#include <chrono>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
using namespace cv;
const int NUMBER = 1000;
const int DELAY = 10;

int Track(Mat image, char* window_name)
{
    Point center, center2;
    for (int i = 0; i < NUMBER; i++) {
        circle(image, center, 3, Scalar(0, 0, 0), 8, 7);
        center.x = 100 + i;
        center.y = 200 + i;
        circle(image, center, 3, Scalar(0, 255, 0), 8, 7);
        imshow(window_name, image);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (waitKey(DELAY) >= 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    char window_name[] = "RadarTest";
    Mat image = Mat::zeros(1000, 1000, CV_8UC3);
    imshow(window_name, image);
    moveWindow(window_name, 200, 0);

    Track(image, window_name);
    return 0;
}
