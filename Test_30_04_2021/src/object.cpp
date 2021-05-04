#include "object.h"
#include "SystemClock.h"

object::object()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uid(1, 1000000);
    std::uniform_int_distribution<int> vuid(200, 400);
    std::uniform_int_distribution<int> kuid(-1000000, 1000000);
    std::uniform_int_distribution<int> suid(1, 10);
    //начальное положение
    _d.x = static_cast<double>(uid(gen)) / 1000;
    _d.y = static_cast<double>(uid(gen)) / 1000;
    _d.z = static_cast<double>(uid(gen)) / 1000;
    //скорость
    _d.v = static_cast<double>(vuid(gen)) / 200;
    //коэффициенты
    _d.kx = static_cast<double>(kuid(gen)) / 1000000;
    _d.ky = static_cast<double>(kuid(gen)) / 1000000;
    _d.kz = static_cast<double>(kuid(gen)) / 1000000;
    //Размер
    _d.size = suid(gen);
    _d.timestamp = SystemClock::get_time_milliseconds();

    printf("x: %lf\t y: %lf\t z :%lf \n", _d.x, _d.y, _d.z);
    printf("kx: %lf\t ky: %lf\t kz :%lf \n", _d.kx, _d.ky, _d.kz);
    printf("v: %lf \n", _d.v);
}

object::~object()
{
}

void object::calculatePosition(ToRadar& result)
{
    while (1) {
        printf("x: %lf\t y: %lf\t z :%lf \n", _d.x, _d.y, _d.z);
        _d.x += _d.kx * _d.v / 10;
        _d.y += _d.ky * _d.v / 10;
        _d.z += _d.kz * _d.v / 10;

        if ((_d.x > 1000) || (_d.x < 0))
            _d.kx *= -1.0;
        if ((_d.y > 1000) || (_d.y < 0))
            _d.ky *= -1.0;
        if ((_d.z > 1000) || (_d.z < 0))
            _d.kz *= -1.0;

        toRadar.x = _d.x;
        toRadar.y = _d.y;
        toRadar.z = _d.z;
        toRadar.sx = _d.kx * _d.v;
        toRadar.sy = _d.ky * _d.v;
        toRadar.sz = _d.kz * _d.v;
        toRadar.size = _d.size;
        toRadar.timestamp = SystemClock::get_time_milliseconds();
        result = toRadar;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
