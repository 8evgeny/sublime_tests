#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
// Объявления функций обратного вызова
void cbMouse(int event, int x, int y, int flags, void*);
void tb1_Callback(int value, void *);
void tb2_Callback(int value, void *);
void checkboxCallBack(int state, void *);
void radioboxCallBack(int state, void *id);
void pushbuttonCallBack(int, void *font);
// Глобальные определения и переменные
Mat orig_img, tmp_img;
const char main_win[]="main_win";
char msg[50];
int main(int, char* argv[]) {
const char track1[]="TrackBar 1";
const char track2[]="TrackBar 2";
const char checkbox[]="Check Box";
const char radiobox1[]="Radio Box1";
const char radiobox2[]="Radio Box2";
const char pushbutton[]="Push Button";
int tb1_value = 50; // Начальное значение полосы прокрутки 1
int tb2_value = 25; // Начальное значение полосы прокрутки 2
orig_img = imread(argv[1]); // Открываем и читаем изображение
if (orig_img.empty()) {
                cout << "Ошибка!!! Не удалось загрузить изображение..." << endl;
                return -1;
}

namedWindow(main_win); // Создаем главное окно
// Создаем шрифт для добавления текста поверх изображения
         CvFont font = fontQt("Arial", 20, Scalar(255,0,0,0),
                CV_FONT_BLACK, CV_STYLE_NORMAL);
// Задаем функции обратного вызова
setMouseCallback(main_win, cbMouse, NULL);
createTrackbar(track1, main_win, &tb1_value, 100, tb1_Callback);
createButton(checkbox, checkboxCallBack, 0,  CV_CHECKBOX);
// Передаем значение (шрифт) функции обратного вызова
createButton(pushbutton, pushbuttonCallBack,
(void *)&font, CV_PUSH_BUTTON);
createTrackbar(track2, NULL, &tb2_value,
50, tb2_Callback);
// Передаем значения функциям обратного вызова
createButton(radiobox1, radioboxCallBack,
(void *)radiobox1, CV_RADIOBOX);
createButton(radiobox2, radioboxCallBack,
(void *)radiobox2, CV_RADIOBOX);
imshow(main_win, orig_img); // показываем исходное изображение
         cout << "Для выхода нажмите любую клавишу..." << endl;
waitKey(); // Бесконечный цикл обработки событий
return 0;
}
