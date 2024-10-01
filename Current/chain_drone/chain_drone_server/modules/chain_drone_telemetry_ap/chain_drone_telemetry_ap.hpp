#ifndef CHAIN_DRONE_TELEMETRY_AP_HPP
#define CHAIN_DRONE_TELEMETRY_AP_HPP

#include <cstdint>

/*
    Данные в пакетах телеметрии, поступающие от автопилота (AP) парителя
*/
#pragma pack(push, 1)
struct ChainDroneTelemetryAP
{
    float roll_rad = 0;             // Крен
    float pitch_rad = 0;            // Тангаж
    float yaw_rad = 0;              // Курс (рысканье)
    float altitude_m = 100.f;           // Высота по радиовысотомеру
  
}; // -- ParitelTelemetryAP
#pragma pack(pop)

#endif //CHAIN_DRONE_TELEMETRY_AP_HPP
