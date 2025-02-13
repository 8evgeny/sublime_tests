#include "CThread.h"
#include "SystemClock.h"

CThread::CThread()
{
    on_iteration_callback = []() { std::cout << "default_callback()" << std::endl; };
}

CThread::~CThread()
{
    shutdown();
    exit_flag = true;
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
    try {
        stop_flag = false;
        auto fo = [&]() {
            if (!exit_flag) {
                while (!stop_flag) {
                    auto start = SystemClock::get_time_milliseconds();
                    on_iteration_callback();
                    //Ожидаем
                    while (SystemClock::get_time_milliseconds() < start + period_ms) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                }
            } else {
                return;
            }
        };
        std::thread t(fo);
        printf("Run Thread\n");
        CThread::thread = std::make_shared<std::thread>(std::move(t));
    } catch (std::exception& e) {
        printf("Exception: %s \n", e.what());
        printf("Type: %s \n", typeid(e).name());
    }
}

void CThread::run_without_iteration()
{
    try {
        stop_flag = false;

        auto fo = [&]() {
            on_iteration_callback();
        };
        std::thread t(fo);
        CThread::thread = std::make_shared<std::thread>(std::move(t));
    } catch (std::exception& e) {
        printf("Exception: %s \n", e.what());
        printf("Type: %s \n", typeid(e).name());
    }
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
    stop();
    join();
}
