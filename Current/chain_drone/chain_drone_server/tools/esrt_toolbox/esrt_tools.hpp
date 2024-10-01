#ifndef ESRT_PROCESSING_H
#define ESRT_PROCESSING_H

#include <iostream>
#include <sys/stat.h> // for isRegularFileExist
#include <iomanip>
#include <math.h>
#include <regex>
#include <string>

namespace esrt_tools
{
    struct Time
    {
        int hour = 0;
        int min = 0;
        double sec = 0.0;
        std::string to_string() const;
    };
    struct Date
    {
        int day = 0;
        int month = 0;
        int year = 0;
        std::string to_string() const;
    };
    struct Navigation
    {
        double latitude = 0.0;
        double longitude = 0.0;
        std::string to_string() const;
    };
    struct Orientation
    {
        double roll = 0.0;
        double pitch = 0.0;
        double yaw = 0.0;
        std::string to_string() const;
    };
    struct Altitude
    {
        double rel_alt = 0.0;
        double abs_alt = 0.0;
        std::string to_string() const;
    };
    struct ShiftXY
    {
        double dx; // сдвиг в параллельной земле плоскости в рамках кадра
        double dy; // - || - || -
        std::string to_string() const;
    };

    bool parseTimeESRT(
        const std::string &raw_str,
        const std::string &alias,
        Time &time_dst);
    bool parseDateESRT(
        const std::string &raw_str,
        const std::string &alias,
        Date &date_dst);
    bool parseNavigationESRT(
        const std::string &raw_str,
        const std::string &alias,
        Navigation &navigation_dst);
    bool parseOrientationESRT(
        const std::string &raw_str,
        const std::string &alias,
        Orientation &orientation_dst);
    bool parseAltitudeESRT(
        const std::string &raw_str,
        const std::string &alias,
        Altitude &altitude_dst);
    bool parseShiftXY_ESRT(
        const std::string &raw_str,
        const std::string &alias,
        ShiftXY &shift_dst);

    //parse lines like $alias$ = $value$
    bool parseLabeledDouble(
        const std::string &raw_str,
        const std::string &alias,
        double &value_dst);
    bool parseLabeledLongInteger(
        const std::string &raw_str,
        const std::string &alias,
        long &value_dst);
    bool isRegularFileExist(const std::string &path);
} // -- namespace esrt_tools

#endif //ESRT_PROCESSING