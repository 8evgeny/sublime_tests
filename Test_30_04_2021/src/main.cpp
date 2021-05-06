#include "main.h"
#include "CoastalRadar.h"
#include "CoastalRadarMessage.h"
#include "Radar.h"
#include "RadarDisplay.h"

std::mutex m;
using namespace cv;
using namespace std;

object::ToRadar obj[object::numObj]; //Результаты из потоков объектов

CoastalRadarMessage::Data msg[object::numObj]; //Результаты из потоков радаров

int main(int argc, char** argv)
{
    object::CreateObjects(); //Создаем объекты

    RadarDisplay d;
    d.set_callback([&]() { RadarDisplay::display_objects(d.transformToPerspective); });
    d.run();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    CoastalRadar r1, r2, r3; //Создаем 3 радара
    r3.iteration_period = 1000;

    r1.set_radar_id(1);
    r2.set_radar_id(2);
    r3.set_radar_id(3);

    r1.set_callback([]() { Radar::receive_data(); });
    r2.set_callback([]() { Radar::receive_data(); });
    r3.set_callback([]() { Radar::receive_data(); });

    //    r3.run(); //Демонстрация валидности-невалидности отображения
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //    r3.stop();
    //    r3.wait_shutdown();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    d.transformToPerspective = true;

    r1.run();

    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //    r1.stop();
    //    r1.wait_shutdown();
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    //    r2.run(2000);
    //    destroyWindow("DisplayRadar");

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

void object::CreateObjects()
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

Point3d RadarDisplay::transform(double x, double y, double z)
{
    glm::vec3 POZITION_CAMERA = glm::vec3(0, 0, 0);

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    //    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
    // Or, for an ortho camera :
    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1000.0f); // In world coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        POZITION_CAMERA, // Camera is at (x,y,z), in World Space
        glm::vec3(500, 0, 500), // and looks at the origin
        glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

    glm::vec4 tmp = MVP * glm::vec4(x, y, z, 1);

    return Point3d { tmp.x, tmp.y, tmp.z };
}

void RadarDisplay::display_objects(bool transf)
{
    int axis = 50;
    auto green = Scalar(0, 255, 0);
    auto red = Scalar(0, 0, 255);
    auto erase = Scalar(0, 0, 0);
    auto axisX = Scalar(255, 255, 100);
    auto axisY = Scalar(255, 255, 100);
    auto axisZ = Scalar(255, 255, 100);
    auto color = Scalar(255, 255, 100);

    char* window = const_cast<char*>("DisplayRadar");
    Mat image = Mat::zeros(1000, 1000, CV_8UC3);

    imshow(window, image);
    moveWindow(window, 900, 0);

    Point3d p3[object::numObj];
    Point3d p3_old[object::numObj];

    Point3d x3[object::numObj];
    Point3d y3[object::numObj];
    Point3d z3[object::numObj];

    for (int i = 0; i < 50; ++i) {
        for (int i = 0; i < object::numObj; ++i) {

            if (checkValid(msg[i], obj[i]))
                color = green;
            else
                color = red;

            circle(image, Point(p3[i].x, p3[i].y), msg[i].size, color, 3, 0);

            if (!transf) {
                x3[i].x = p3[i].x + axis;
                x3[i].y = p3[i].y;
                x3[i].z = p3[i].z;

                y3[i].x = p3[i].x;
                y3[i].y = p3[i].y + axis;
                y3[i].z = p3[i].z;

                z3[i].x = p3[i].x;
                z3[i].y = p3[i].y;
                z3[i].z = p3[i].z + axis;
            } else {
                x3[i] = transform(p3[i].x + axis, p3[i].y, p3[i].z);
                y3[i] = transform(p3[i].x, p3[i].y + axis, p3[i].z);
                z3[i] = transform(p3[i].x, p3[i].y, p3[i].z + axis);
            }

            line(image, Point(p3[i].x, p3[i].y), Point(x3[i].x, x3[i].y), axisX, 1, 0);
            line(image, Point(p3[i].x, p3[i].y), Point(y3[i].x, y3[i].y), axisY, 1, 0);
            line(image, Point(p3[i].x, p3[i].y), Point(z3[i].x, z3[i].y), axisZ, 1, 0);

            putText(image, "x", Point(x3[i].x, x3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisX, 0);
            putText(image, "y", Point(y3[i].x, y3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisY, 0);

            p3_old[i] = p3[i];

            //Тут забираем координаты объектов

            if (!transf) {
                p3[i].x = msg[i].x;
                p3[i].y = msg[i].y;
                p3[i].z = msg[i].z;

            } else {
                p3[i] = transform(msg[i].x, msg[i].y, msg[i].z);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        for (int i = 0; i < object::numObj; ++i) {
            circle(image, Point(p3_old[i].x, p3_old[i].y), msg[i].size, erase, 3, 0);
            line(image, Point(p3_old[i].x, p3_old[i].y), Point(x3[i].x, x3[i].y), erase, 1, 0);
            line(image, Point(p3_old[i].x, p3_old[i].y), Point(y3[i].x, y3[i].y), erase, 1, 0);
            line(image, Point(p3_old[i].x, p3_old[i].y), Point(z3[i].x, z3[i].y), erase, 1, 0);

            putText(image, "x", Point(x3[i].x, x3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);
            putText(image, "y", Point(y3[i].x, y3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);

            if (checkValid(msg[i], obj[i]))
                color = green;
            else
                color = red;

            circle(image, Point(p3[i].x, p3[i].y), msg[i].size, color, 3, 0);

            if (!transf) {
                x3[i].x = p3[i].x + axis;
                x3[i].y = p3[i].y;
                x3[i].z = p3[i].z;

                y3[i].x = p3[i].x;
                y3[i].y = p3[i].y + axis;
                y3[i].z = p3[i].z;

                z3[i].x = p3[i].x;
                z3[i].y = p3[i].y;
                z3[i].z = p3[i].z + axis;
            } else {
                x3[i] = transform(p3[i].x + axis, p3[i].y, p3[i].z);
                y3[i] = transform(p3[i].x, p3[i].y + axis, p3[i].z);
                z3[i] = transform(p3[i].x, p3[i].y, p3[i].z + axis);
            }

            line(image, Point(p3[i].x, p3[i].y), Point(x3[i].x, x3[i].y), axisX, 1, 0);
            line(image, Point(p3[i].x, p3[i].y), Point(y3[i].x, y3[i].y), axisY, 1, 0);
            line(image, Point(p3[i].x, p3[i].y), Point(z3[i].x, z3[i].y), axisZ, 1, 0);

            putText(image, "x", Point(x3[i].x, x3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisX, 0);
            putText(image, "y", Point(y3[i].x, y3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisY, 0);
        }
        imshow(window, image);
        waitKey(1);
    }
}

void Radar::receive_data()
{
    lock_guard<mutex> lg(m);
    for (int i = 0; i < object::numObj; ++i) {
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
