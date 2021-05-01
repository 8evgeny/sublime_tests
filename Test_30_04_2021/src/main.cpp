#include "main.h"

using namespace std;
using namespace cv;
using namespace cv::ximgproc;

// void foo() {
//  glm::vec4 Position = glm::vec4(glm::vec3(0.0f), 1.0f);
//  glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f));
//    Model = glm::rotate(Model, 45, 0, 1, 0);
//  glm::vec4 Transformed = Model * Position;
//}

int main(int argc, char** argv) {
  //  foo();
  cout << "OpenCV version : " << CV_VERSION << endl;
  cout << "Major version : " << CV_MAJOR_VERSION << endl;
  cout << "Minor version : " << CV_MINOR_VERSION << endl;
  cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

  Mat img, gray, edges;      // Объявление матриц
  img = imread(argv[1], 1);  // Читаем изображение
  imshow("original", img);   // Отрисовываем изображение
  cvtColor(img, gray, COLOR_BGR2GRAY);
  // Конвертируем в монохромный формат
  GaussianBlur(gray, gray, Size(7, 7), 1.5);
  // Устраняем размытие
  Canny(gray, edges, 0, 50);
  // Запускаем детектор ребер
  imshow("edges", edges);
  // Отрисовываем изображение
  waitKey();
  //Ожидаем нажатия клавиши

  // create a new image which consists of
  // 3 channels
  // image depth of 8 bits
  // 800 x 600 of resolution (800 wide and 600 high)
  // each pixels initialized to the value of (100, 250, 30) for Blue, Green and
  // Red planes respectively.

  Mat image(800, 1000, CV_8UC3, Scalar(100, 100, 30));
  String windowName = "Window with Blank Image";  // Name of the window
  namedWindow(windowName);                        // Create a window
  imshow(windowName, image);  // Show our image inside the created window.
  waitKey(0);                 // Wait for any keystroke in the window
  destroyWindow(windowName);  // destroy the created window

  return 0;
}
/*
9. Собрать из классов демонстрационное приложение, в котором использовать 2-3
радара и один дисплей, отображающий перемещение объектов, данные о которых
передаются радарами.

    Оцениваются:
– Способность к интерпретации задачи;
– Способность разбираться в новой тематике;
– Способность ориентироваться в сложной архитектуре;
– Чистота и читаемость кода, стиль именования переменных и методов;
– Внимание к исключительным ситуациям, в которых могут возникать ошибки;
контроль за использованием ресурсов.
*/
