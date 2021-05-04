#include "main.h"
#include "SystemClock.h"
#include "object.cpp"
#include "object.h"
using namespace cv;
using namespace std;
const int NUMBER_OBJECTS = 3;
mutex m;
vector<object::ToRadar> vToRadar;

int objectsMove(Mat image, char* window_name)
{
    while (1) {
        for (int i = 0; i < NUMBER_OBJECTS; i++) {
            Point p, p_old;
            m.lock();
            circle(image, p, vToRadar[i].size, Scalar(0, 255, 0), 8, 7);
            p_old = p;
            p.x = vToRadar[i].x;
            p.y = vToRadar[i].y;
            m.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            m.lock();
            circle(image, p_old, vToRadar[i].size, Scalar(0, 0, 0), 8, 7);
            circle(image, p, vToRadar[i].size, Scalar(0, 255, 0), 8, 7);
            m.unlock();
        }
        imshow(window_name, image);
        waitKey(1);
    }
    return 0;
}

int main()
{
    vector<object> vObj;
    vector<std::thread*> vTh;
    for (int i = 0; i < NUMBER_OBJECTS; i++) {
        object Obj;
        vObj.push_back(Obj);
        object::ToRadar Result;
        vToRadar.push_back(Result);
        thread t(&object::calculatePosition, Obj, std::ref(vToRadar[i]));
        //        vTh.push_back(t);
        t.detach();
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
