#include "SystemClock.h"

int64_t SystemClock::get_time_milliseconds()
{
    auto currTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(
        currTime.time_since_epoch())
        .count();
}

Timer::Timer()
{
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float result = duration.count();
    std::cout << "Прошло времени: " << result << " секунд" << std::endl;
}
