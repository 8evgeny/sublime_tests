#include "main.h"
#include "CoastalRadar.h"
#include "CoastalRadarMessage.h"
#include "Radar.h"
#include "RadarDisplay.h"

std::mutex m;
using namespace cv;
using namespace std;
namespace po = boost::program_options;
boost::program_options::variables_map vmd;
int view_x; //точка куда смотрит камера
int view_y;
int view_z;
glm::vec3 POZITION_CAMERA; //точка где камера расположена

object::ToRadar obj[object::numObj]; //Результаты из потоков объектов

CoastalRadarMessage::Data msg[object::numObj]; //Результаты из потоков радаров

int main(int argc, char** argv)
{
    readConfig("../config.ini");
    int cameraX = vmd["position_camera_X"].as<int>();
    int cameraY = vmd["position_camera_Y"].as<int>();
    int cameraZ = vmd["position_camera_Z"].as<int>();
    view_x = vmd["view_X"].as<int>();
    view_y = vmd["view_Y"].as<int>();
    view_z = vmd["view_Z"].as<int>();
    POZITION_CAMERA = glm::vec3(cameraX, cameraY, cameraZ);

    printf("Position camera: %d, %d, %d \n", cameraX, cameraY, cameraZ);

    object::CreateObjects(); //Создаем объекты

    RadarDisplay d; //Размерность 1м = 10 условных единиц на экране

    d.set_callback([&]() { RadarDisplay::display_objects(d.transformToPerspective); });
    d.run();

    //    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    CoastalRadar r1, r2; //Создаем 2 радара
    r2.iteration_period = 1000;

    r1.set_radar_id(1);
    r2.set_radar_id(2);

    r1.set_callback([]() { Radar::receive_data(); });
    r2.set_callback([]() { Radar::receive_data(); });

    //    r2.run(); //Демонстрация валидности-невалидности отображения
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //    d.transformToPerspective = true;
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    //    d.transformToPerspective = false;
    //    r2.stop();
    //    r2.wait_shutdown();
    d.transformToPerspective = true;
    r2.run(100);

    r1.run();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    test_rotate_camera();

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

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 4.0f, 10.1f, 1500.0f);
    // Or, for an ortho camera :
    //    glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(
        POZITION_CAMERA, // Camera is at (x,y,z), in World Space
        glm::vec3(view_x, view_y, view_z), // and looks at the origin
        glm::vec3(0, 0, -1) // Head is up (set to 0,-1,0 to look upside-down)
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

    Point3d p3[object::numObj]; //0,0,0 объекта
    Point3d p3_old[object::numObj];

    Point3d x3[object::numObj]; //Концы векторов объекта
    Point3d y3[object::numObj];
    Point3d z3[object::numObj];

    Point3d poli0[object::numObj]; //Полигон объекта
    Point3d poli1[object::numObj];
    Point3d poli2[object::numObj];
    Point3d poli3[object::numObj];
    Point3d poli4[object::numObj];

    for (int i = 0; i < 50; ++i) { //частота вызова функции

        for (int i = 0; i < object::numObj; ++i) {

            //            circle(image, Point(p3[i].x, p3[i].y), msg[i].size, color, FILLED, 0);

            if (transf) {
                Polygon(image, poli0[i], k3(poli0[i], poli1[i]), k3(poli0[i], poli2[i]), k3(poli0[i], poli3[i]), k3(poli0[i], poli4[i]), color);
                line(image, Point(p3[i].x, p3[i].y), k(p3[i], x3[i]), axisX, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), k(p3[i], y3[i]), axisY, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), k(p3[i], z3[i]), axisZ, 1, 0);
            } else {
                Polygon(image, poli0[i], poli1[i], poli2[i], poli3[i], poli4[i], color);
                line(image, Point(p3[i].x, p3[i].y), Point(x3[i].x, x3[i].y), axisX, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), Point(y3[i].x, y3[i].y), axisY, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), Point(z3[i].x, z3[i].y), axisZ, 1, 0);
            }

            //            putText(image, "x", Point(x3[i].x, x3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisX, 0);
            //            putText(image, "y", Point(y3[i].x, y3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisY, 0);
            if (transf)
                putText(image, "z", k(p3[i], z3[i]), FONT_HERSHEY_SIMPLEX, 0.6, axisZ, 0);
            p3_old[i] = p3[i];
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        for (int i = 0; i < object::numObj; ++i) {

            //            circle(image, Point(p3_old[i].x, p3_old[i].y), msg[i].size, erase, FILLED, 0);

            if (transf) {
                Polygon(image, poli0[i], k3(poli0[i], poli1[i]), k3(poli0[i], poli2[i]), k3(poli0[i], poli3[i]), k3(poli0[i], poli4[i]), erase);
                line(image, Point(p3_old[i].x, p3_old[i].y), k(p3_old[i], x3[i]), erase, 1, 0);
                line(image, Point(p3_old[i].x, p3_old[i].y), k(p3_old[i], y3[i]), erase, 1, 0);
                line(image, Point(p3_old[i].x, p3_old[i].y), k(p3_old[i], z3[i]), erase, 1, 0);
            } else {
                Polygon(image, poli0[i], poli1[i], poli2[i], poli3[i], poli4[i], erase);
                line(image, Point(p3_old[i].x, p3_old[i].y), Point(x3[i].x, x3[i].y), erase, 1, 0);
                line(image, Point(p3_old[i].x, p3_old[i].y), Point(y3[i].x, y3[i].y), erase, 1, 0);
                line(image, Point(p3_old[i].x, p3_old[i].y), Point(z3[i].x, z3[i].y), erase, 1, 0);
            }
            //            putText(image, "x", Point(x3[i].x, x3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);
            //            putText(image, "y", Point(y3[i].x, y3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);
            if (transf)
                putText(image, "z", k(p3_old[i], z3[i]), FONT_HERSHEY_SIMPLEX, 0.6, erase, 0);
            //Тут забираем координаты объектов
            if (!transf) {
                p3[i].x = msg[i].x;
                p3[i].y = msg[i].y;
                p3[i].z = msg[i].z;

                x3[i].x = p3[i].x + axis;
                x3[i].y = p3[i].y;
                x3[i].z = p3[i].z;

                y3[i].x = p3[i].x;
                y3[i].y = p3[i].y + axis;
                y3[i].z = p3[i].z;

                z3[i].x = p3[i].x;
                z3[i].y = p3[i].y;
                z3[i].z = p3[i].z + axis;

                poli0[i] = p3[i];

                poli1[i].x = p3[i].x + msg[i].size * 5;
                poli1[i].y = p3[i].y;
                poli1[i].z = p3[i].z;

                poli2[i].x = p3[i].x + msg[i].size * 5;
                poli2[i].y = p3[i].y + msg[i].size * 3;
                poli2[i].z = p3[i].z;

                poli3[i].x = p3[i].x;
                poli3[i].y = p3[i].y + msg[i].size * 3;
                poli3[i].z = p3[i].z;

                poli4[i].x = p3[i].x - msg[i].size * 1.5;
                poli4[i].y = p3[i].y + msg[i].size * 1.5;
                poli4[i].z = p3[i].z;

            } else {
                p3[i] = transform(msg[i].x, msg[i].y, msg[i].z);

                x3[i] = transform(msg[i].x + axis, msg[i].y, msg[i].z);
                y3[i] = transform(msg[i].x, msg[i].y + axis, msg[i].z);
                z3[i] = transform(msg[i].x, msg[i].y, msg[i].z + axis);

                poli0[i] = transform(msg[i].x, msg[i].y, msg[i].z);
                poli1[i] = transform(msg[i].x + msg[i].size * 5, msg[i].y, msg[i].z);
                poli2[i] = transform(msg[i].x + msg[i].size * 5, msg[i].y + msg[i].size * 3, msg[i].z);
                poli3[i] = transform(msg[i].x, msg[i].y + msg[i].size * 3, msg[i].z);
                poli4[i] = transform(msg[i].x - msg[i].size * 1.5, msg[i].y + msg[i].size * 1.5, msg[i].z);
            }

            if (checkValid(msg[i], obj[i]))
                color = green;
            else
                color = red;

            //            circle(image, Point(p3[i].x, p3[i].y), msg[i].size, color, FILLED, 0);

            if (transf) {
                Polygon(image, poli0[i], k3(poli0[i], poli1[i]), k3(poli0[i], poli2[i]), k3(poli0[i], poli3[i]), k3(poli0[i], poli4[i]), color);
                line(image, Point(p3[i].x, p3[i].y), k(p3[i], x3[i]), axisX, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), k(p3[i], y3[i]), axisY, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), k(p3[i], z3[i]), axisZ, 1, 0);
            } else {
                Polygon(image, poli0[i], poli1[i], poli2[i], poli3[i], poli4[i], color);
                line(image, Point(p3[i].x, p3[i].y), Point(x3[i].x, x3[i].y), axisX, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), Point(y3[i].x, y3[i].y), axisY, 1, 0);
                line(image, Point(p3[i].x, p3[i].y), Point(z3[i].x, z3[i].y), axisZ, 1, 0);
            }
            //            putText(image, "x", Point(x3[i].x, x3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisX, 0);
            //            putText(image, "y", Point(y3[i].x, y3[i].y), FONT_HERSHEY_SIMPLEX, 0.6, axisY, 0);
            if (transf)
                putText(image, "z", k(p3[i], z3[i]), FONT_HERSHEY_SIMPLEX, 0.6, axisZ, 0);
        }
        imshow(window, image);
        waitKey(1);
    }
}

Point3d RadarDisplay::k3(Point3d one, Point3d two)
{
    Point p;
    double k = 1 / (two.z / 300 + 1);

    return Point3d(one.x + (two.x - one.x) * k, one.y + (two.y - one.y) * k, two.z);
}

Point RadarDisplay::k(Point3d one, Point3d two)
{
    Point p;
    double k = 1 / (two.z / 300 + 1);

    return Point(one.x + (two.x - one.x) * k, one.y + (two.y - one.y) * k);
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

void Polygon(Mat img, Point3d p0, Point3d p1, Point3d p2, Point3d p3, Point3d p4, Scalar color)
{
    int lineType = LINE_8;
    Point object[1][5];

    object[0][0] = Point(p0.x, p0.y);
    object[0][1] = Point(p1.x, p1.y);
    object[0][2] = Point(p2.x, p2.y);
    object[0][3] = Point(p3.x, p3.y);
    object[0][4] = Point(p4.x, p4.y);

    const Point* ppt[1] = { object[0] };
    int npt[] = { 5 };
    fillPoly(img,
        ppt,
        npt,
        1,
        color,
        lineType);
}

void test_rotate_camera()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    printf("Rotate camera\n");
    for (int i = 0; i < 1000; ++i) {
        POZITION_CAMERA = glm::vec3(i, 0, 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    printf("Rotate camera\n");
    for (int i = 0; i < 1000; ++i) {
        POZITION_CAMERA = glm::vec3(i, i, i);
        std::this_thread::sleep_for(std::chrono::microseconds(5000));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    printf("Rotate camera\n");
    for (int i = 0; i < 1000; ++i) {
        POZITION_CAMERA = glm::vec3(0, i, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    printf("Rotate camera\n");
    for (int i = 0; i < 1000; ++i) {
        POZITION_CAMERA = glm::vec3(0, 0, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}

void readConfig(const char* conf_file)
{
    po::options_description disp("display");
    disp.add_options()("position_camera_X", po::value<int>())("position_camera_Y", po::value<int>())("position_camera_Z", po::value<int>())("view_X", po::value<int>())("view_Y", po::value<int>())("view_Z", po::value<int>());

    po::options_description desc("Allowed options");
    desc.add(disp);

    try {
        po::parsed_options parsed = po::parse_config_file<char>(conf_file, desc, true); //флаг true разрешает незарегистрированные опции !
        po::store(parsed, vmd);
    } catch (const po::reading_file& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    po::notify(vmd);
}
