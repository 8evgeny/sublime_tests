#ifndef LIVE_DISK_MONITOR_HPP
#define LIVE_DISK_MONITOR_HPP

#include "disk_monitor.hpp"
#include <chrono>
#include <thread>
#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#include <memory>

namespace chr = std::chrono;

#include <string>


class LvDiskMonitor
{
public:
    LvDiskMonitor(const std::string &disk, int check_step_ms, bool &ok);
    long get_free_space_mb();
    bool quit();
private:
    void exec();
    std::shared_ptr<DiskMonitor> disk_monitor = nullptr;
    chr::milliseconds check_step = chr::milliseconds(5'000);
    long cur_free_space_mb = 0; // обновляется при итерациях запроса
    long default_val = -1;
    struct Sync
    {
        std::atomic<bool> init = {false};
        std::atomic<bool> execute = {false};
        std::atomic<bool> exec_compl = {false};
        std::atomic<bool> quit_was_call = {false};
        std::atomic<bool> success_quit = {false};
        std::mutex fr_sp_mtx; // current free space mutex
    } sync;
    chr::milliseconds watchdog_wait_exec_compl = chr::milliseconds(5'000); // общее допустимое время на завершение потока
    chr::milliseconds delay_exec_compl = chr::milliseconds(5); // шаг проверки закрытия потока
}; // -- END LvDiskMonitor

#endif // LIVE_DISK_MONITOR
