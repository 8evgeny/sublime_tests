#include "Radar.h"
#include "RadarDataConnector.h"

Radar::Radar()
{
}

Radar::~Radar()
{
}

void Radar::run(int64_t period)
{
    printf("Radar starting \n");
    thread.set_iteration_period_milliseconds(period);
    printf("iteration_period_milliseconds = %ld \n", period);
    thread.run();
}

void Radar::stop()
{
    printf("Thread stop \n");
    thread.stop();
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

/*
Жизненный цикл объекта:
СThread thread;
thread.set_iteration_period_milliseconds(50);
thread.set_iteration_callback(callback);
thread.run();
*/
