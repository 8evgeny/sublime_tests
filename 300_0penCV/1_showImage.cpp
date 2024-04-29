#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv) //Аргументы запуска  ../2 ../4.jpg
{
    string name1;
    string name2;
    if (argc == 1){
        name1 = "../2";
        name2 = "../4.jpg";
    }
    if (argc == 3) {
        name1 = argv[1];
        name2 = argv[2];
    }
    if ((argc != 3) && (argc != 1)){
        cout << "Ошибка аргументов\n";
        return -1;
    }
Mat in_image, out_image;
// Порядок запуска: <cmd> <file_in> <file_out>
// Читаем исходное изображение
         in_image = imread(name1, IMREAD_UNCHANGED);
         if (in_image.empty()) {
// Проверяем, успешно ли прочитано изображение
                cout << "Ошибка! Не удалось прочитать исходное изображение...\n";
                return -1;
}
// Создаем два окна с именами изображений в заголовке
         namedWindow(name1, WINDOW_AUTOSIZE);
         namedWindow(name2, WINDOW_AUTOSIZE);
// Показываем изображения в окнах
         imshow(name1, in_image);
         cvtColor(in_image, out_image, COLOR_BGR2GRAY /*COLOR_RGBA2BGRA*/);
         imshow(name2, out_image);
         cout << "Для выхода нажмите 0...\n";
         moveWindow(name1, 300, 200);
         moveWindow(name2, 1000, 200);
         waitKey(0);
         // Записываем изображение
                  imwrite(name2, out_image);
         return 0;
         }
