#include "main.h"
#include "SystemClock.h"
#include "object.cpp"
#include "object.h"
using namespace cv;
using namespace std;
const int allTime = 1000000;
const int DELAY = 1000;
object::ToRadar object1; // результат из потока1
object::ToRadar object2; // результат из потока2
object::ToRadar object3; // результат из потока3
object::ToRadar object4; // результат из потока4
object::ToRadar object5; // результат из потока5

int objectsMove(Mat image, char* window_name)
{
    Point p1, p2, p3, p4, p5, p1_old, p2_old, p3_old, p4_old, p5_old;
    for (int t = 0; t < allTime; t++) {
        circle(image, p1, object1.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p2, object2.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p3, object3.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p4, object4.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p5, object5.size, Scalar(0, 255, 0), 8, 7);
        p1_old = p1;
        p2_old = p2;
        p3_old = p3;
        p4_old = p4;
        p5_old = p5;
        p1.x = object1.x;
        p2.x = object2.x;
        p3.x = object3.x;
        p4.x = object4.x;
        p5.x = object5.x;

        p1.y = object1.y;
        p2.y = object2.y;
        p3.y = object3.y;
        p4.y = object4.y;
        p5.y = object5.y;

        //        printf("x1: %lf\t y1: %lf\t z1: %lf \n", object1.x, object1.y, object1.z);
        //        printf("x2: %lf\t y2: %lf\t z2: %lf \n", object2.x, object2.y, object2.z);
        //        printf("x3: %lf\t y3: %lf\t z3: %lf \n", object3.x, object3.y, object3.z);
        //        printf("1: %lf\t 2: %lf\t 3: %lf \n", object1.size, object2.size, object3.size);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        circle(image, p1_old, object1.size, Scalar(0, 0, 0), 8, 7);
        circle(image, p2_old, object2.size, Scalar(0, 0, 0), 8, 7);
        circle(image, p3_old, object3.size, Scalar(0, 0, 0), 8, 7);
        circle(image, p4_old, object4.size, Scalar(0, 0, 0), 8, 7);
        circle(image, p5_old, object5.size, Scalar(0, 0, 0), 8, 7);
        circle(image, p1, object1.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p2, object2.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p3, object3.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p4, object4.size, Scalar(0, 255, 0), 8, 7);
        circle(image, p5, object5.size, Scalar(0, 255, 0), 8, 7);
        imshow(window_name, image);

        waitKey(1);
    }
    return 0;
}

int main()
{

    object o1, o2, o3, o4, o5;
    std::thread t1(&object::calculatePosition, o1, std::ref(object1));
    std::thread t2(&object::calculatePosition, o2, std::ref(object2));
    std::thread t3(&object::calculatePosition, o3, std::ref(object3));
    std::thread t4(&object::calculatePosition, o4, std::ref(object4));
    std::thread t5(&object::calculatePosition, o5, std::ref(object5));
    t1.detach();
    t2.detach();
    t3.detach();
    t4.detach();
    t5.detach();

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
