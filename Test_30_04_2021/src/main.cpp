#include "main.h"
//#include "RadarDataConnector.h"
#include "CoastalRadar.h"
#include "Radar.h"
#include "SystemClock.h"
#include "object.cpp"
#include "object.h"
using namespace cv;
using namespace std;
const int numObj = 7;
object::ToRadar obj[numObj]; //Результаты из потоков объектов
Point p[numObj];
Point p_old[numObj];
const int iteration_period = 100;
void CreateObjects();
void MoveObjects(Mat image, char* window_name);
void DisplayObjects();

int main()
{
    CreateObjects(); //Создаем объекты

    CoastalRadar r1;
    r1.set_radar_id(1);

    r1.run(iteration_period);

    DisplayObjects(); //Тестовое отображение
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

void CreateObjects()
{
    for (int i = 0; i < numObj; ++i) {
        object o;
        std::thread t(&object::calculatePosition, o, std::ref(obj[i]));
        t.detach();
    }
}

void MoveObjects(Mat image, char* window_name)
{
    while (1) {
        for (int i = 0; i < numObj; ++i) {
            circle(image, p[i], obj[i].size, Scalar(0, 255, 0), 8, 7);
            p_old[i] = p[i];
            p[i].x = obj[i].x;
            p[i].y = obj[i].y;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        for (int i = 0; i < numObj; ++i) {
            circle(image, p_old[i], obj[i].size, Scalar(0, 0, 0), 8, 7);
            circle(image, p[i], obj[i].size, Scalar(0, 255, 0), 8, 7);
        }
        imshow(window_name, image);
        waitKey(1);
    }
}

void DisplayObjects()
{
    char window_name[] = "MovingObjects";
    Mat image = Mat::zeros(1000, 1000, CV_8UC3);
    imshow(window_name, image);
    moveWindow(window_name, 100, 0);

    MoveObjects(image, window_name);
}