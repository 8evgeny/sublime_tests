#ifndef ESRT_API_H
#define ESRT_API_H

#include "esrt_tools.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

// Extend SubRip Subtitle files (modern relative SRT DJI definition)
/*
В связной системе координат:
    - ось X направлена вдоль БПЛА
    - ось Y направлена поперек БПЛА
    - ось Z направлена по нормали вниз БПЛА
*/
struct ESRTdata
{
    long frameNumber = 0;                       // порядковый номер кадра
    esrt_tools::Time startFrameTime;            // локальное время начала кадра (в рамках одного видео)
    esrt_tools::Time endFrameTime;              // локальное время конца кадра
    esrt_tools::Date date;                      // год, месяц, день
    esrt_tools::Time time;                      // глобально (время по внутренним часам)
    esrt_tools::Navigation navigation;          // долгота, широта (не пересчитанные с учетом shift_xy_m)
    esrt_tools::Altitude ref_altitude_m;        // считанная напрямую из DJI SRT (не пересчитанные с учетом shift_xy_m)
    double current_altitude_m = 0;              // пересчитанная высота по радиовысотомеру (используем ее) - метры
    double shift_altitude_m = 0;                // синтетический сдвиг по высоте в метрах
    esrt_tools::Orientation orientation_deg;    // крен, тангаж, рысканье
    esrt_tools::ShiftXY shift_xy_m;             // синтетический сдвиг UAV по осям X,Y связной системы координат             
};

bool parseESRT(
    const std::string &path2file, 
    ESRTdata &esrt_dst); // чтение ESRT из txt файла

bool writeESRT(
    const ESRTdata &esrt, 
    const std::string &path2file,
    bool force_replace = true); // запись ESRT в txt файл

#endif // ESRT_API_H
