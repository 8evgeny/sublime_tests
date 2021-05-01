//#include <opencv2/cv.h>
//#include <opencv2/highgui.h>

#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/ximgproc.hpp"
using namespace std;
using namespace cv;
using namespace cv::ximgproc;

int main(int argc, char** argv) {
  cout << "OpenCV version : " << CV_VERSION << endl;
  cout << "Major version : " << CV_MAJOR_VERSION << endl;
  cout << "Minor version : " << CV_MINOR_VERSION << endl;
  cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

  //  Mat img, gray, edges;      // Объявление матриц
  //  img = imread(argv[1], 1);  // Читаем изображение
  //  imshow("original", img);   // Отрисовываем изображение
  //  cvtColor(img, gray, COLOR_BGR2GRAY);
  //  // Конвертируем в монохромный формат
  //  GaussianBlur(gray, gray, Size(7, 7), 1.5);
  //  // Устраняем размытие
  //  Canny(gray, edges, 0, 50);
  //  // Запускаем детектор ребер
  //  imshow("edges", edges);
  //  // Отрисовываем изображение
  //  waitKey();
  //  //Ожидаем нажатия клавиши

  // create a new image which consists of
  // 3 channels
  // image depth of 8 bits
  // 800 x 600 of resolution (800 wide and 600 high)
  // each pixels initialized to the value of (100, 250, 30) for Blue, Green and
  // Red planes respectively.

  Mat image(800, 1400, CV_8UC3, Scalar(0, 0, 30));
  String windowName = "Window with Blank Image";  // Name of the window
  namedWindow(windowName);                        // Create a window
  imshow(windowName, image);  // Show our image inside the created window.
  waitKey(0);                 // Wait for any keystroke in the window
  destroyWindow(windowName);  // destroy the created window

  return 0;
}
