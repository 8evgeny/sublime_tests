#include "main.h"
#include "CoastalRadar.h"
#include "CoastalRadarMessage.h"
#include "Radar.h"
#include "SystemClock.h"
#include "object.h"

std::mutex m;
using namespace cv;
using namespace std;

const int numObj = 10; //Колл. объектов
object::ToRadar obj[numObj]; //Результаты из потоков объектов
CoastalRadarMessage::Data msg[numObj]; //Результаты из потоков радаров
Point p[numObj];
Point p_old[numObj];
const int iteration_period = 100;

void CreateObjects();
void MoveObjects(Mat image, char* window_name);
void DisplayObjects();
void RadarMsg(); //Радар забирает данные объектов и отдает для показа

int main()
{

    CreateObjects(); //Создаем объекты

    CoastalRadar r1, r2, r3;
    r1.set_radar_id(1);
    r2.set_radar_id(2);
    r3.set_radar_id(3);
    //    r1.run(iteration_period);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //    r1.stop();
    //    r1.wait_shutdown();
    r1.set_callback(RadarMsg);
    r2.set_callback(RadarMsg);
    r3.set_callback(RadarMsg);
    //    r1.run(iteration_period);
    //    r2.run(50);

    r3.run(1000); //Демонстрация валидности-невалидности отображения

    DisplayObjects(); //Тестовое отображение
        //Размерность 1м = 10 условных единиц на экране
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

bool checkValid(CoastalRadarMessage::Data msg, object::ToRadar obj)
{
    double delta = 2;
    if ((msg.x > obj.x + delta) || (msg.y > obj.y + delta) || (msg.z > obj.z + delta))
        return false;
    return true;
}

void MoveObjects(Mat image, char* window_name)
{
#define green Scalar(0, 255, 0)
#define axisX Scalar(255, 255, 100)
#define axisY Scalar(255, 255, 100)
#define erase Scalar(0, 0, 0)
    auto gr = Scalar(0, 255, 0);
    auto re = Scalar(0, 0, 255);
    auto color = Scalar(0, 0, 255);
    Point q[numObj];
    Point r[numObj];
    while (1) {
        for (int i = 0; i < numObj; ++i) {
            if (checkValid(msg[i], obj[i]))
                color = gr;
            else
                color = re;
            circle(image, p[i], msg[i].size, color, 3, 0);
            q[i].x = p[i].x + 20;
            q[i].y = p[i].y;
            r[i].x = p[i].x;
            r[i].y = p[i].y + 25;

            line(image, p[i], q[i], axisX, 1, 0);
            line(image, p[i], r[i], axisY, 1, 0);
            putText(image, "x", q[i], FONT_HERSHEY_SIMPLEX, 0.6, axisX, 0);
            putText(image, "y", r[i], FONT_HERSHEY_SIMPLEX, 0.6, axisY, 0);
            p_old[i] = p[i];
            p[i].x = msg[i].x;
            p[i].y = msg[i].y;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        for (int i = 0; i < numObj; ++i) {
            circle(image, p_old[i], msg[i].size, erase, 3, 0);
            line(image, p_old[i], q[i], erase, 1, 0);
            line(image, p_old[i], r[i], erase, 1, 0);
            putText(image, "x", q[i], FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);
            putText(image, "y", r[i], FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);

            if (checkValid(msg[i], obj[i]))
                color = gr;
            else
                color = re;

            circle(image, p[i], msg[i].size, color, 3, 0);
            q[i].x = p[i].x + 20;
            q[i].y = p[i].y;
            r[i].x = p[i].x;
            r[i].y = p[i].y + 25;
            line(image, p[i], q[i], axisX, 1, 0);
            line(image, p[i], r[i], axisY, 1, 0);
            putText(image, "x", q[i], FONT_HERSHEY_SIMPLEX, 0.6, axisX, 0);
            putText(image, "y", r[i], FONT_HERSHEY_SIMPLEX, 0.6, axisY, 0);
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
    moveWindow(window_name, 900, 0);

    MoveObjects(image, window_name);
}

void RadarMsg()
{
    lock_guard<mutex> lg(m);
    for (int i = 0; i < numObj; ++i) {
        msg[i].size = obj[i].size;
        msg[i].x = obj[i].x;
        msg[i].y = obj[i].y;
        msg[i].z = obj[i].z;
        msg[i].sx = obj[i].sx;
        msg[i].sy = obj[i].sy;
        msg[i].sz = obj[i].sz;
        msg[i].timestamp = obj[i].timestamp;
    }
    //    printf("x: %lf\t y: %lf\t z :%lf \n", msg[0].x, msg[0].y, msg[0].z);
}
