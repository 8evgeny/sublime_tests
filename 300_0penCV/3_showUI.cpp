#include <opencv2/opencv.hpp>
#include <iostream>
//#include <QFont>
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
// Создаем главное окно
    namedWindow(main_win);
// Создаем шрифт для добавления текста поверх изображения
    CvFont font = fontQt("Arial", 20, Scalar(255,0,0,0), CV_FONT_NORMAL, CV_STYLE_NORMAL);
// Задаем функции обратного вызова
    setMouseCallback(main_win, cbMouse, NULL);
    createTrackbar(track1, main_win, &tb1_value, 100, tb1_Callback);
    createButton(checkbox, checkboxCallBack, 0,  CV_CHECKBOX);
// Передаем значение (шрифт) функции обратного вызова
    createButton(pushbutton, pushbuttonCallBack, (void *)&font, CV_PUSH_BUTTON);
//    createTrackbar(track2, NULL, &tb2_value, 50, tb2_Callback);
// Передаем значения функциям обратного вызова
    createButton(radiobox1, radioboxCallBack,
    (void *)radiobox1, CV_RADIOBOX);
    createButton(radiobox2, radioboxCallBack,
    (void *)radiobox2, CV_RADIOBOX);
// показываем исходное изображение
    imshow(main_win, orig_img);
    cout << "Для выхода нажмите 0..." << endl;
    waitKey(0); // Бесконечный цикл обработки событий
    return 0;
}

void cbMouse(int event, int x, int y, int flags, void*) {
    // Static vars hold values between calls
    static Point p1, p2;
    static bool p2set = false;
    // Left mouse button pressed
    if (event == EVENT_LBUTTONDOWN) {
        p1 = Point(x, y); // Set orig. point
        p2set = false;
    } else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON) {
        // Check moving mouse and left button down
        // Check out bounds
        if (x > orig_img.size().width)
        x = orig_img.size().width;
        else if (x < 0)
        x = 0;
        // Check out bounds
        if (y > orig_img.size().height)
        y = orig_img.size().height;
        else if (y < 0)
        y = 0;
        p2 = Point(x, y); // Set final point
        p2set = true;
        // Copy orig. to temp. image
        orig_img.copyTo(tmp_img);
        // Draws rectangle
        rectangle(tmp_img, p1, p2, Scalar(0, 0 ,255));
        // Draw temporal image with rect.
        imshow(main_win, tmp_img);
    } else if (event == EVENT_LBUTTONUP && p2set) {
        // Check if left button is released
        // and selected an area
        // Set subarray on orig. image
        // with selected rectangle
        Mat submat = orig_img(Rect(p1, p2));
        // Here some processing for the submatrix
        //...
        // Mark the boundaries of selected rectangle
        rectangle(orig_img, p1, p2, Scalar(0, 0, 255), 2);
        imshow("main_win", orig_img);
    }
    return;
 }
void tb1_Callback(int value, void *) {
    sprintf(msg, "Trackbar 1 changed. New value=%d", value);
    displayOverlay(main_win, msg);
    return;
}
void tb2_Callback(int value, void *) {
    sprintf(msg, "Trackbar 2 changed. New value=%d", value);
    displayStatusBar(main_win, msg, 1000);
    return;
}
void checkboxCallBack(int state, void *) {
    sprintf(msg, "Check box changed. New state=%d", state);
    displayStatusBar(main_win, msg);
    return;
}
void radioboxCallBack(int state, void *id) {
    // Id of the radio box passed to the callBack
    sprintf(msg, "%s changed. New state=%d",
    (char *)id, state);
    displayStatusBar(main_win, msg);
    return;
}
void pushbuttonCallBack(int, void *font) {
    // Add text to the image
    addText(orig_img, "Push button clicked",
    Point(50,50), *((CvFont *)font));
    imshow(main_win, orig_img); // Shows original image
    return;
}
