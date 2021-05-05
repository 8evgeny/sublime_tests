#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "CoastalRadar.h"
#include "CoastalRadarMessage.h"
#include "Radar.h"
#include "RadarDisplay.h"
#include "SystemClock.h"
#include "main.h"
#include "object.h"

std::mutex m;
using namespace cv;
using namespace std;

#define POZITION_CAMERA 1000, 1000, 1000
bool transformToPerspective = 1;

const int numObj = 50; //Колл. объектов
object::ToRadar obj[numObj]; //Результаты из потоков объектов
CoastalRadarMessage::Data msg[numObj]; //Результаты из потоков радаров
//Point3d p3[numObj];
//Point3d p3_old[numObj];
const int iteration_period = 100;

Point3d transform(double x, double y, double z);
void CreateObjects();
void Display();
void movingObjects(Mat image, char* window_name);
void RadarMsg(); //Радар забирает данные объектов и отдает для показа

int main(int argc, char** argv)
{
    //    Mat img;
    //    img = imread(argv[1], 1); // Читаем изображение
    //    imshow("original", img); // Отрисовываем изображение
    //    waitKey(1);

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
    r1.run(iteration_period);
    //    r2.run(50);
    //    r3.run(1000); //Демонстрация валидности-невалидности отображения

    RadarDisplay d;
    d.set_callback(Display);
    d.run();

    //Размерность 1м = 10 условных единиц на экране
    while (1) { }
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

Point3d transform(double x, double y, double z)
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    // Or, for an ortho camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        glm::vec3(POZITION_CAMERA), // Camera is at (x,y,z), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    glm::vec4 tmp = MVP * glm::vec4(x, y, z, 1);
    return Point3d { tmp.x, tmp.y, tmp.z };
}

void movingObjects(Mat image, char* window_name)
{

#define green Scalar(0, 255, 0)
#define axisX Scalar(255, 255, 100)
#define axisY Scalar(255, 255, 100)
#define erase Scalar(0, 0, 0)
    auto gr
        = Scalar(0, 255, 0);
    auto re = Scalar(0, 0, 255);
    auto color = Scalar(0, 0, 255);

    Point q[numObj];
    Point r[numObj];
    Point p[numObj];
    Point p_old[numObj];

    for (int i = 0; i < 1000; ++i) {
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

            //Тут забираем координаты объектов

            Point3d p3;
            if (!transformToPerspective) {
                p[i].x = msg[i].x;
                p[i].y = msg[i].y;
            } else {
                p3 = transform(msg[i].x, msg[i].y, msg[i].z);
                p[i].x = p3.x;
                p[i].y = p3.y;
            }
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

void Display()
{
    char window_name[] = "DisplayRadar";
    Mat image = Mat::zeros(1000, 1000, CV_8UC3);
    imshow(window_name, image);
    moveWindow(window_name, 900, 0);

    movingObjects(image, window_name);
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
