#pragma once
#include "main.h"

class CThread {
public:
    CThread(const CThread&) = delete;
    CThread(CThread&&) = delete;
    CThread& operator=(const CThread&) = delete;
    CThread& operator=(CThread&&) = delete;

public:
    explicit CThread();
    virtual ~CThread();

public:
    virtual void run();
    virtual void stop();
    virtual void join();
    virtual void set_iteration_period_milliseconds(const int64_t period);
    virtual void set_iteration_callback(const std::function<void()>& on_iteration_callback);
    void run_without_iteration();

private:
    void shutdown();

private:
    std::atomic_bool stop_flag { false };
    std::atomic_bool exit_flag { false };
    int64_t period_ms = 20;
    std::shared_ptr<std::thread> thread = nullptr;
    std::function<void()> on_iteration_callback = nullptr;
};
