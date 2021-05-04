#include "main.h"
#include "SystemClock.h"
#include "object.cpp"
#include "object.h"
using namespace cv;
using namespace std;
const int numObj = 5;
object::ToRadar obj[numObj]; //Результаты из потоков объектов
Point p[numObj];
Point p_old[numObj];
int objectsMove(Mat image, char* window_name)
{
    //    for (int i = 0; i < numObj; ++i) {

    Point p1, p2, p3, p4, p5, p1_old, p2_old, p3_old, p4_old, p5_old;
    while (1) {
        for (int i = 0; i < numObj; ++i) {
            circle(image, p1, obj[i].size, Scalar(0, 255, 0), 8, 7);
        }
        p1_old = p1;
        p2_old = p2;
        p3_old = p3;
        p4_old = p4;
        p5_old = p5;

        p1.x = obj[0].x;
        p2.x = obj[1].x;
        p3.x = obj[2].x;
        p4.x = obj[3].x;
        p5.x = obj[4].x;

        p1.y = obj[0].y;
        p2.y = obj[1].y;
        p3.y = obj[2].y;
        p4.y = obj[3].y;
        p5.y = obj[4].y;

        //        printf("x1: %lf\t y1: %lf\t z1: %lf \n", object1.x, object1.y, object1.z);
        //        printf("x2: %lf\t y2: %lf\t z2: %lf \n", object2.x, object2.y, object2.z);
        //        printf("x3: %lf\t y3: %lf\t z3: %lf \n", object3.x, object3.y, object3.z);
        //        printf("1: %lf\t 2: %lf\t 3: %lf \n", object1.size, object2.size, object3.size);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //                for (int i = 0; i < numObj; ++i) {
        circle(image, p1_old, obj[0].size, Scalar(0, 0, 0), 8, 7);
        circle(image, p2_old, obj[1].size, Scalar(0, 0, 0), 8, 7);
        circle(image, p3_old, obj[2].size, Scalar(0, 0, 0), 8, 7);
        circle(image, p4_old, obj[3].size, Scalar(0, 0, 0), 8, 7);
        circle(image, p5_old, obj[4].size, Scalar(0, 0, 0), 8, 7);
        //                }
        circle(image, p1, obj[0].size, Scalar(0, 255, 0), 8, 7);
        circle(image, p2, obj[1].size, Scalar(0, 255, 0), 8, 7);
        circle(image, p3, obj[2].size, Scalar(0, 255, 0), 8, 7);
        circle(image, p4, obj[3].size, Scalar(0, 255, 0), 8, 7);
        circle(image, p5, obj[4].size, Scalar(0, 255, 0), 8, 7);

        imshow(window_name, image);

        waitKey(1);
    }
    return 0;
}

int main()
{
    for (int i = 0; i < numObj; ++i) {
        //    object o1, o2, o3, o4, o5;

        //    std::thread t1(&object::calculatePosition, o1, std::ref(obj[0]));
        //    std::thread t2(&object::calculatePosition, o2, std::ref(obj[1]));
        //    std::thread t3(&object::calculatePosition, o3, std::ref(obj[2]));
        //    std::thread t4(&object::calculatePosition, o4, std::ref(obj[3]));
        //    std::thread t5(&object::calculatePosition, o5, std::ref(obj[4]));

        //    t1.detach();
        //    t2.detach();
        //    t3.detach();
        //    t4.detach();
        //    t5.detach();
        object o;
        std::thread t(&object::calculatePosition, o, std::ref(obj[i]));
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
