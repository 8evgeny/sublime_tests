#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int, char *argv[])
{
Mat in_image, out_image;
// Порядок запуска: <cmd> <file_in> <file_out>
// Читаем исходное изображение
         in_image = imread(argv[1], IMREAD_UNCHANGED);
         if (in_image.empty()) {
// Проверяем, успешно ли прочитано изображение
                cout << "Ошибка! Не удалось прочитать исходное изображение...\n";
                return -1;
}
// Создаем два окна с именами изображений в заголовке
         namedWindow(argv[1], WINDOW_AUTOSIZE);
         namedWindow(argv[2], WINDOW_AUTOSIZE);
// Показываем изображения в окнах
         imshow(argv[1], in_image);
                  cvtColor(in_image, out_image, COLOR_BGR2GRAY);
         imshow(argv[2], out_image);
//                  cout << "Для выхода нажмите любую клавишу...\n";
//                  waitKey(); // Ждем нажатия клавиши
         // Записываем изображение
                  imwrite(argv[2], out_image);
         return 0;
         }
