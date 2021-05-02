#pragma once
#include "main.h"

class SystemClock {
public:
    static int64_t get_time_milliseconds();
};

class Timer {
public:
    Timer();
    ~Timer();

private:
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<float> duration;
};

//2. Создать класс, инкапсулирующий источник времени для приложения.
