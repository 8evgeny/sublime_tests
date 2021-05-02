#include "main.h"
#include "SystemClock.h"

using namespace cv;
const int allTime = 1000;
const int DELAY = 1000;

int objectsMove(Mat image, char* window_name)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> uid(1, 1000);
    std::uniform_int_distribution<int> kuid(-20, 20);
    srand(time(0));

    Point p;
    p.x = uid(gen);
    p.y = uid(gen);
    int a = kuid(gen);
    int b = kuid(gen);
    for (int t = 0; t < allTime; t++) {
        circle(image, p, 3, Scalar(0, 0, 0), 8, 7);
        p.x += a * t / 100;
        p.y += b * t / 100;
        if ((p.x > 1000) || (p.x < 0))
            a = (-1) * a;

        if ((p.y > 1000) || (p.y < 0))
            b *= (-1) * b;

        circle(image, p, 3, Scalar(0, 255, 0), 8, 7);
        imshow(window_name, image);
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        waitKey(1);
    }
    return 0;
}

int main(void)
{
    char window_name[] = "MovingObjects";
    Mat image = Mat::zeros(1000, 1000, CV_8UC3);
    imshow(window_name, image);
    moveWindow(window_name, 100, 0);
    objectsMove(image, window_name);
    return 0;
}

/*
9. Собрать из классов демонстрационное приложение, в котором использовать 2-3 радара и
один дисплей, отображающий перемещение объектов, данные о которых передаются радарами.

    Оцениваются:
– Способность к интерпретации задачи;
– Способность разбираться в новой тематике;
– Способность ориентироваться в сложной архитектуре;
– Чистота и читаемость кода, стиль именования переменных и методов;
– Внимание к исключительным ситуациям, в которых могут возникать ошибки;
контроль за использованием ресурсов.
*/
