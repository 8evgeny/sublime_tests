#ifndef BEEPER_CONTROLLER_HPP
#define BEEPER_CONTROLLER_HPP

#include "settings.hpp"

#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace sound
{
class BeeperController
{
public:
    static BeeperController& inst();
    void setSettings(sound::beeper::SettingsPtr &settings);
    void system();
    void alarm();

    void quit();
private:
    void high();
    void low();
    enum class Commands
    {
        SYSTEM,
        ALARM
    };
    struct CmdData
    {
        Commands id;
        decltype(std::chrono::system_clock::now()) time;
        int length = 0;
    };

    BeeperController();
    BeeperController(const BeeperController & root) = delete;
    BeeperController(BeeperController &&root) = delete;
    BeeperController& operator=(BeeperController &&) = delete;
    ~BeeperController();

    void workflow();

    sound::beeper::Settings settings;

    struct Sync
    {
           std::mutex queueMtx;
           std::atomic<bool> exec;
           std::atomic<bool> workflow_done;
           std::condition_variable queueCV;
    } sync;

    std::queue<CmdData> cmdQueue;
    bool quit_was_apply = false;
};
}

#endif // BEEPER_CONTROLLER_HPP
