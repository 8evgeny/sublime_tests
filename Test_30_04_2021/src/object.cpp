#include "object.h"
#include "SystemClock.h"

object::object()
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> uid(1, 100);
    std::uniform_int_distribution<int> kuid(-100, 100);
    std::uniform_int_distribution<int> suid(100, 500);
    //начальное положение
    _d.x = uid(gen);
    _d.y = uid(gen);
    _d.z = uid(gen);
    //скорость от 0.01 до 1
    _d.v = uid(gen);
    _d.kx = kuid(gen) / 10;
    _d.ky = kuid(gen) / 10;
    _d.kz = kuid(gen) / 10;
    //Размер 1 - 5
    _d.size = suid(gen) / 100;
    _d.timestamp = SystemClock::get_time_milliseconds();

    refreshData();
}

object::~object()
{
}

//void object::startMove()
//{
//    std::thread move(&object::calculatePosition, std::ref(_d.periodCalculate));
//    move.join();
//}

void object::refreshData()
{
    toRadar.x = _d.x;
    toRadar.y = _d.y;
    toRadar.z = _d.z;
    toRadar.sx = _d.kx * _d.v;
    toRadar.sy = _d.ky * _d.v;
    toRadar.sz = _d.kz * _d.v;
    toRadar.size = _d.size;
    toRadar.timestamp = SystemClock::get_time_milliseconds();
}

void object::calculatePosition()
{
    while (1) {
        printf("_d.x: %lf \n", _d.x);
        printf("_d.кx: %lf \n", _d.kx);

        _d.x += _d.kx * _d.v * periodCalculate;
        _d.y += _d.ky * _d.v * periodCalculate;
        _d.z += _d.kz * _d.v * periodCalculate;

        if ((_d.x > 100) || (_d.x < 0))
            _d.kx *= -1.0;
        if ((_d.y > 100) || (_d.y < 0))
            _d.ky *= -1.0;
        if ((_d.z > 100) || (_d.z < 0))
            _d.kz *= -1.0;
        refreshData();
        std::this_thread::sleep_for(std::chrono::milliseconds(periodCalculate));
    }
}
