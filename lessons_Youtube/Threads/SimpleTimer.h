#pragma once
#include <chrono>
#include <iostream>

class SimpleTimer {
public:
    SimpleTimer();
    ~SimpleTimer();

private:
    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<float> duration;
};
