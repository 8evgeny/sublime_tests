#include "SystemClock.h"
#include "main.h"
class object {
public:
    object();
    ~object();

    void refreshData();
    struct ToRadar {
        double x = 0;
        double y = 0;
        double z = 0;
        double sx = 0;
        double sy = 0;
        double sz = 0;
        double size = 0;
        int64_t timestamp = 0;
    };
    ToRadar toRadar;
    //    void startMove();
    void calculatePosition();
    int periodCalculate = 200;

private:
    struct Data {
        double x = 0;
        double y = 0;
        double z = 0;
        int v = 0;
        double kx = 0; // -1 - 1
        double ky = 0;
        double kz = 0;
        double size = 0;
        int64_t timestamp = 0;
    };
    Data _d;
};

//object::object()
//{
//    std::mt19937 gen(time(0));
//    std::uniform_int_distribution<int> uid(1, 100);
//    std::uniform_int_distribution<int> kuid(-100, 100);
//    std::uniform_int_distribution<int> suid(100, 500);
//    //начальное положение
//    _d.x = uid(gen);
//    _d.y = uid(gen);
//    _d.z = uid(gen);
//    //скорость от 0.01 до 1
//    _d.v = uid(gen) / 100;
//    _d.kx = kuid(gen) / 100;
//    _d.ky = kuid(gen) / 100;
//    _d.kz = kuid(gen) / 100;
//    //Размер 1 - 5
//    _d.size = suid(gen) / 100;
//    _d.timestamp = SystemClock::get_time_milliseconds();

//    //    std::thread calculate(&object::calculatePosition, _d.periodCalculate);
//    //    calculate.join();
//}

//object::~object()
//{
//}
