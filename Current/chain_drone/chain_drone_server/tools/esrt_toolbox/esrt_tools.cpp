#include "esrt_tools.hpp"

namespace esrt_tools
{
    bool isRegularFileExist(const std::string &path)
    {
        struct stat sb;
        return (stat(path.c_str(), &sb) == 0 && S_ISREG(sb.st_mode));
    } // -- END isRegularFileExist

    std::string Time::to_string() const
    {
        std::ostringstream os;
        os.str("");
        if(hour < 10)
        {
            os << "0";
        }
        os << std::to_string(hour) << ":";
        
        if(min < 10)
        {
            os << "0";
        }
        os << std::to_string(min) << ":";

        if(sec < 10)
        {
            os << "0";
        }
        os << std::fixed << std::setprecision(3) << sec;
        return os.str();
    } // -- END Time::to_string

    std::string Date::to_string() const
    {
        std::ostringstream os;
        os.str("");
        std::string year_str = std::to_string(year);
        int cnt_zeros_year = 4 - year_str.size();
        for(int i = 0; i < cnt_zeros_year; ++i)
        {
            os << "0";
        }
        os << year_str << "-";
        
        if(month < 10)
        {
            os << "0";
        }
        os << std::to_string(month) << "-";

        if(day < 10)
        {
            os << "0";
        }
        os << std::to_string(day);
        return os.str();   
    } // -- END Date::to_string

    std::string Navigation::to_string() const
    {
        std::ostringstream os;
        os.str("");
        os << "[latitude: " << std::fixed << std::setprecision(5) << latitude << "] "
            << "[longitude: " << std::fixed << std::setprecision(5) << longitude << "]";
        // example: [latitude: 54.66886] [longitude: 40.00593]
        return os.str();
    } // -- END Navigation::to_string()

    std::string Altitude::to_string() const
    {
        std::ostringstream os;
        os.str("");
        os << "[rel_alt: " << std::fixed << std::setprecision(3) << rel_alt << " "
            << "abs_alt: " << std::fixed << std::setprecision(3) << abs_alt << "]";
        // example [rel_alt: 105.100 abs_alt: 173.017]
        return os.str();
    } // -- END Altitude::to_string()

    std::string Orientation::to_string() const
    {
        std::ostringstream os;
        os.str("");
        std::string unit_str;

        os << "[roll: " << std::fixed << std::setprecision(5) << roll << "] ";
        os << "[pitch: "<< std::fixed << std::setprecision(5) << pitch << "] ";
        os << "[yaw: " << std::fixed << std::setprecision(5) << yaw << "]";
        // example [roll_deg: 15.12345] [pitch_deg: 24.67890] [yaw_deg: 98.54321]
        return os.str();
    } // -- END Orientation::to_string()

    std::string ShiftXY::to_string() const
    {
        std::ostringstream os;
        os.str("");
        os << "[dx: " << std::fixed << std::setprecision(3) << dx << "] ";
        os << "[dy: " << std::fixed << std::setprecision(3) << dy << "]";
        // example [dx: 12.345] [dy: 98.876]
        return os.str();
    } // -- END ShiftXY::to_string()

    bool parseTimeESRT(
        const std::string &raw_str,
        const std::string &alias,
        Time &time_dst)
    {
        // parse raw string like: $alias$ = hour(d{2}):min(d{2}):seconds(d{2}.3f)
        std::string regex_str = alias + " = (\\d{2}):(\\d{2}):(\\d{2}.\\d{3})";
        std::regex time_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, time_regex))
        {
            time_dst.hour = std::stoi(match[1].str());
            time_dst.min = std::stoi(match[2].str());
            time_dst.sec += std::stod(match[3].str());
            return true;
        }
        return false;
    } // -- END parseTimeESRT

    bool parseDateESRT(
        const std::string &raw_str,
        const std::string &alias,
        Date &date_dst)
    {
        std::string regex_str = alias + " = (\\d{4})-(\\d{2})-(\\d{2})";
        std::regex date_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, date_regex))
        {
            date_dst.year = std::stoi(match[1].str());
            date_dst.month = std::stoi(match[2].str());
            date_dst.day = std::stoi(match[3].str());
            return true;
        }
        return false;
    } // -- END parseDateESRT

    bool parseNavigationESRT(
        const std::string &raw_str,
        const std::string &alias,
        Navigation &navigation_dst)
    {
        std::string regex_str = alias + " = \\[latitude: ([+-]?\\d*.\\d*)\\] \\[longitude: ([+-]?\\d*.\\d*)\\]";
        std::regex navigation_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, navigation_regex))
        {
            navigation_dst.latitude = std::stod(match[1].str());
            navigation_dst.longitude = std::stod(match[2].str());
            return true;
        }
        return false;
    } // -- END parseNavigationESRT

    bool parseOrientationESRT(
        const std::string &raw_str,
        const std::string &alias,
        Orientation &orientation_dst)
    {
        std::string regex_str = alias + " = \\[roll: ([+-]?\\d*.\\d{5})\\] \\[pitch: ([+-]?\\d*.\\d{5})\\] \\[yaw: ([+-]?\\d*.\\d{5})\\]";
        std::regex orientation_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, orientation_regex))
        {
            orientation_dst.roll = std::stod(match[1].str());
            orientation_dst.pitch = std::stod(match[2].str());
            orientation_dst.yaw = std::stod(match[3].str());
            return true;
        }
        return false;
    } // -- END parseOrientationESRT

    bool parseAltitudeESRT(
        const std::string &raw_str,
        const std::string &alias,
        Altitude &altitude_dst)
    {
        std::string regex_str = alias + " = \\[rel_alt: ([+-]?\\d*.\\d*) abs_alt: ([+-]?\\d*.\\d*)\\]";
        std::regex altitude_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, altitude_regex))
        {
            altitude_dst.rel_alt = std::stod(match[1].str());
            altitude_dst.abs_alt = std::stod(match[2].str());
            return true;
        }
        return false;
    } // -- END parseAltitudeESRT

    bool parseShiftXY_ESRT(
        const std::string &raw_str,
        const std::string &alias,
        ShiftXY &shift_dst)
    {
        std::string regex_str = alias + " = \\[dx: ([+-]?\\d*.\\d*)\\] \\[dy: ([+-]?\\d*.\\d*)\\]";
        std::regex shift_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, shift_regex))
        {
            shift_dst.dx = std::stod(match[1].str());
            shift_dst.dy = std::stod(match[2].str());
            return true;
        }
        return false;   
    } // -- END parseShiftXY_ESRT

    bool parseLabeledDouble(
        const std::string &raw_str,
        const std::string &alias,
        double &value_dst)
    {
        std::string regex_str = alias + " = ([+-]?\\d*.\\d*)";
        std::regex value_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, value_regex))
        {
            value_dst = std::stod(match[1].str());
            return true;
        }
        return false;
    } // -- END parseLabeledDouble

    bool parseLabeledLongInteger(
        const std::string &raw_str,
        const std::string &alias,
        long &value_dst)
    {
        std::string regex_str = alias + " = ([+-]?\\d*)";
        std::regex value_regex(regex_str);
        std::smatch match;
        if(std::regex_search(raw_str, match, value_regex))
        {
            value_dst = std::stol(match[1].str());
            return true;
        }
        return false;
    } // -- END parseLabeledLongInteger
} // -- namespace esrt_tools
