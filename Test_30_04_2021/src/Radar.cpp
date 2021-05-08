#include "Radar.h"
#include "RadarDataConnector.h"

Radar::Radar()
{
}

Radar::~Radar()
{
    wait_shutdown();
}

void Radar::run(int period)
{
    try {
        if (!is_runned_flag) {
            is_runned_flag = true;
            printf("Radar starting \n");
            thread.set_iteration_period_milliseconds(period);
            printf("iteration_period_milliseconds = %d \n", period);
            thread.run();
        }
    } catch (std::exception& e) {
        printf("Exception: %s \n", e.what());
        printf("Type: %s \n", typeid(e).name());
    }
}

void Radar::run()
{
    try {
        if (!is_runned_flag) {
            is_runned_flag = true;
            printf("Radar starting \n");
            thread.set_iteration_period_milliseconds(iteration_period);
            printf("iteration_period_milliseconds = %d \n", iteration_period);
            thread.run();
        }
    } catch (std::exception& e) {
        printf("Exception: %s \n", e.what());
        printf("Type: %s \n", typeid(e).name());
    }
}

void Radar::stop()
{
    if (is_runned_flag) {
        is_runned_flag = false;
        printf("Thread stop \n");
        thread.stop();
    }
}

void Radar::wait_shutdown()
{
    printf("Thread joined \n");
    thread.join();
}

void Radar::set_radar_id(const int64_t id)
{
    printf("\nSetting radar id: %ld \n", id);
    radar_id = id;
}

void Radar::set_data_connector(const RadarDataConnector& data_connector)
{
    //Метод set_data_connector(const RadarDataConnector & data_connector) задает
    //приeмник сообщений радара.
}

RadarDataConnector Radar::get_data_connector() const
{
}

int64_t Radar::get_radar_id() const
{
    return radar_id;
}

void Radar::set_callback(const std::function<void()>& set_callback)
{
    printf("Setting new callback  \n");
    iteration_callback = set_callback;
    thread.set_iteration_callback(iteration_callback);
}
