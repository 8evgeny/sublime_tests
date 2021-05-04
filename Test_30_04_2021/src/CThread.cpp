#include "CThread.h"
#include "SystemClock.h"

CThread::CThread()
{
    on_iteration_callback = []() { std::cout << "iteration_callback()" << std::endl; };
}

CThread::~CThread()
{
}

void CThread::set_iteration_period_milliseconds(const int64_t period)
{
    period_ms = period;
}

void CThread::set_iteration_callback(
    const std::function<void()>& on_iteration_callback)
{
    CThread::on_iteration_callback = on_iteration_callback;
}

void CThread::run()
{
    stop_flag = false;

    auto fo = [&]() {
        while (!stop_flag) {
            auto start = SystemClock::get_time_milliseconds();
            on_iteration_callback();

            []() { std::cout << "iteration_callback()" << std::endl; };
            while (SystemClock::get_time_milliseconds() < start + period_ms) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    };
    std::thread t(fo);
    CThread::thread = std::make_shared<std::thread>(std::move(t));
}

void CThread::stop()
{
    stop_flag = true;
}

void CThread::join()
{
    if (thread->joinable()) {
        thread->join();
    }
}

void CThread::shutdown()
{
}
