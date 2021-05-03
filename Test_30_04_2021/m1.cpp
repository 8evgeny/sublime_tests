#include "SystemClock.h"
#include "main.h"
#include "object.cpp"
#include "object.h"
using namespace cv;
using namespace std;
const int NUMBER_OBJECTS = 5;
vector<object::ToRadar*> vToRadar;

int objectsMove(Mat image, char* window_name)
{
    while (1) {
        for (int i = 0; i < NUMBER_OBJECTS; i++) {
            Point p, p_old;
            circle(image, p, vToRadar[i]->size, Scalar(0, 255, 0), 8, 7);
            p_old = p;
            p.x = vToRadar[i]->x;
            p.y = vToRadar[i]->y;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            circle(image, p_old, vToRadar[i]->size, Scalar(0, 0, 0), 8, 7);
            circle(image, p, vToRadar[i]->size, Scalar(0, 255, 0), 8, 7);
        }
        imshow(window_name, image);
        waitKey(1);
    }
    return 0;
}

int main()
{
    vector<object*> vObj;
    vector<std::thread*> vTh;
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        object* Obj = new object();
        vObj.push_back(Obj);

        object::ToRadar* Result = new object::ToRadar;
        vToRadar.push_back(Result);
        auto fo = std::move(&object::calculatePosition);
        std::thread* t = new std::thread(&fo, std::move(Obj), std::ref(Result));
        vTh.push_back(t);
        t->detach();
    }

    char window_name[]
        = "MovingObjects";
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
