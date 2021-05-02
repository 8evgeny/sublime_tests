#include "Radar.h"
/*
Жизненный цикл объекта:
СThread thread;
thread.set_iteration_period_milliseconds(50);
thread.set_iteration_callback(callback);
thread.run();
*/
void Radar::run() {
  //    thread.set_iteration_callback(callback);
  thread.set_iteration_period_milliseconds(100);
  thread.run();
}

void Radar::stop() {
  thread.stop();
}

void Radar::wait_shutdown() {
  thread.join();
}

void Radar::set_radar_id(const int64_t id) {
  radar_id = id;
}

void Radar::set_data_connector(const RadarDataConnector& data_connector) {
  //Метод set_data_connector(const RadarDataConnector & data_connector) задает
  //приeмник сообщений радара.
}

RadarDataConnector Radar::get_data_connector() const {}

// virtual void internal_thread_iteration() = 0;

int64_t Radar::get_radar_id() const {
  return radar_id;
}
