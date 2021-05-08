#pragma once
#include "main.h"

class Radar {
public:
    Radar(const Radar&) = delete;
    Radar(Radar&&) = delete;
    Radar& operator=(const Radar&) = delete;
    Radar& operator=(Radar&&) = delete;

    explicit Radar();
    virtual ~Radar();

    virtual void run(int);
    virtual void run();
    virtual void stop();
    virtual void wait_shutdown();
    virtual void set_radar_id(const int64_t id);
    virtual void set_data_connector(const RadarDataConnector&);
    static void receive_data();
    virtual void set_callback(const std::function<void()>&);
    int iteration_period = 100;

protected:
    virtual RadarDataConnector get_data_connector() const;
    virtual void internal_thread_iteration() = 0;
    virtual int64_t get_radar_id() const;

private:
    CThread thread;
    bool is_runned_flag = false;
    std::shared_ptr<RadarDataConnector> data_connector = nullptr;
    int64_t radar_id = 0;
    std::function<void()> iteration_callback = nullptr;
};
