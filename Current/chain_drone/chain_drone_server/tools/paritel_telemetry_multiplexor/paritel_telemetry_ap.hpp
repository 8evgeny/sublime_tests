#ifndef PARITEL_TELEMETRY_AP_HPP
#define PARITEL_TELEMETRY_AP_HPP

#include <cstdint>

/*
    Данные в пакетах телеметрии, поступающие от автопилота (AP) парителя
*/

struct ParitelTelemetryAP
{
    uint32_t uid;               // FrameID - порядковый номер поступившего пакета
    float roll_deg;             // Крен
    float pitch_deg;            // Тангаж
    float yaw_deg;              // Курс (рысканье)
    float heading_deg;          // Курс по GNSS
    float latitude_deg;         // Широта
    float longitude_deg;        // Долгота
    float altitude_m;           // Высота по радиовысотомеру
    float altitude_bar_m;       // Высота по барометру
    float speed_mps;            // Скорость (GNSS) mps - metres per second
    float airspeed_mps;         // Скорость ветра (TODO: уточнить источник сигнала)
    float gx;                   // Перегрузка по X (нормированная)
    float gy;                   // Перегрузка по Y (нормированная)
    float gz;                   // Перегрузка по Z (нормированная)
    float ang_rate_x_dps;       // Угловая скорость вокруг оси X; dps - degrees per second
    float ang_rate_y_dps;       // Угловая скорость вокруг оси Y
    float ang_rate_z_dps;       // Угловая скорость вокруг оси Z
    float pos_error_longit;     /*
                                    Смещение относительно заданной 
                                    точки вдоль продольной оси в 
                                    связанной системе координат
                                */
    float pos_error_transv;     /*
                                    Смещение относительно заданной 
                                    точки вдоль поперечной оси в 
                                    связанной системе координат
                                */
    float vel_longit_mps;       /*
                                    Проекция скорости перемещения относительно 
                                    земли на продольную ось 
                                    связанной системы координат
                                */
    float vel_transv_mps;       /*
                                    Проекция скорости перемещения относительно 
                                    земли на продольную ось 
                                    связанной системы координат
                                */
    float vel_vertical_mps;     /*
                                    Проекция скорости перемещения относительно
                                    земли на вертикальную ось
                                    связанной системы координат 
                                    TODO:(уточнить, что подразумевается под
                                    вертикальной осью связанной системы координат.
                                    Вертикальная ось нормальна земли или нормальна
                                    брюшной поверхности БПЛА?).
                                */
}; // -- ParitelTelemetryAP

#endif //PARITEL_TELEMETRY_AP_HPP