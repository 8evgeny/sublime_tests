#ifndef RECORDER_SRST_HPP
#define RECORDER_SRST_HPP

#include "recorder_base.hpp"
#include "tools/path_processing/path_processing.hpp"
#include <atomic>
// SRST - Single Request Single Thread

namespace recorder
{

struct WatchDogEvent
{
    int wait_total_time     = 1'000;    // общее время ожидания
    int check_delay_time    = 30;       // интервал проверки
    WatchDogEvent(int _wait_total_time, int _check_delay_time)
        : wait_total_time(_wait_total_time), check_delay_time(_check_delay_time)
    {
    };
};

struct WatchDog // настройки временных интервалов для внутриклассовых процессов 
{
    WatchDogEvent complete_all_threads = {3'000, 1};
};

struct RecorderSRSTSettings
{
    RecorderBaseSettings base;
    WatchDog watchdog;
};

class RecorderSRST : public RecorderBase
{
public:
    RecorderSRST(const RecorderSRSTSettings &_settings);
    ~RecorderSRST() override;
    bool setup() override;
    bool save(const cv::Mat &frame, const std::string &path) override;
    bool save(const cv::Mat &frame, long frame_num) override;
    void log() override;
    long getDiff() override;
    bool quit() override;
private:
    RecorderSRST() = delete;
    long save_started_counter = 0;
    std::atomic<long> save_complete_counter = 0;
    std::function<void(
        cv::Mat                 frame, 
        std::string             path, 
        std::vector<int>        params
        )> save_lambda;
    ; // счетчик завершенных процессов сохранения 

    RecorderSRSTSettings settings;
}; // -- class RecorderSRST 

} // -- namespace recorder

#endif // RECORDER_SRST_HPP
