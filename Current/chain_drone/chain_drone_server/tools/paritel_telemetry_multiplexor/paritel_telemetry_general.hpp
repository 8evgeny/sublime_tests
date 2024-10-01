#ifndef PARITEL_TELEMETRY_GENERAL_HPP
#define PARITEL_TELEMETRY_GENERAL_HPP

#include <string>

/*
    Мультиплексированная телеметрия.
    Может быть получена на основе ESRT или ParitelTelemetryAP
*/

struct ParitelTelemetryGen
{
    long frameNumber = 0;               // порядковый номер кадра
    long telemetryNumberAP = 0;         /*
                                        Номер актуального пакета 
                                        телеметрии от автопилота (АП).
                                        Обновляется реже, чем frjgthtameNumber
                                    */
    
    int date_year = 0;                  // дата-год
    int date_month = 0;                 // дата-месяц
    int date_day = 0;                   // дата-день

    int time_hour = 0;                  // время-час
    int time_min = 0;                   // время-минуты
    double time_sec = 0;                // время-секунды (вещественное)
    
    unsigned long time_ms = 0;          // относительное время с момента начала работы программы

    float roll_deg = 0.f;
    float pitch_deg = 0.f;
    float yaw_deg = 0.f;

    float altitude_m = -1.f;               // высота по радиовысотомеру

    // второстепенные данные 
    float altitude_bar_m = -1.f;           // высота по барометру

    float heading_deg = -1.f;              // направление по GNSS
    float latitude_deg = -1.f;             // широта по GNSS
    float longitude_deg = -1.f;            // долгота по GNSS
    float speed_mps = -1.f;                // скорость по GNSS (mps - metres per second)

    float airspeed_mps = -1.f;             // скорость ветра
    float gx, gy, gz = -1;                 // перегрузка по осям X,Y,Z
    float ang_rate_x_dps = -1.f;           // угловая скорость вокруг оси X (dps - deg per second)
    float ang_rate_y_dps = -1.f;
    float ang_rate_z_dps = -1.f;

    float vel_longit_mps = -1.f;           // продольная скорость вдоль продольной оси связанной системы координат; mps - metres per sec
    float vel_transv_mps = -1.f;
    float vel_vertical_mps = -1.f;         // вертикальная скорость

    // относится к Jetson
    float exposure_ms = -1;                // время экспозиции 
    float cpu_temp_deg = -1;               // температура процессора в градусах

    bool save2txt(const std::string &path2file, bool force_replace = true);
    bool readFromTxt(const std::string &path2file);
}; // -- ParitelTelemetryGen

#endif // PARITEL_TELEMETRY_GENERAL_HPP
