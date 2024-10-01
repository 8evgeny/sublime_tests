#include "paritel_telemetry_general.hpp"
#include "tools/path_processing/path_processing.hpp"
#include "tools/string_toolbox/string_processing.hpp"
#include <fstream>
#include <iomanip>
#include <vector>

bool ParitelTelemetryGen::save2txt(const std::string &path2file, bool force_replace)
{
    if(path_processing::isRegularFileExist(path2file))
    {
        if(!force_replace)
        {
            std::cout << "ERROR (ParitelTelemetryGen::save2txt): file currently exist, not use force replace!" << std::endl;
            return false;
        }
    }
    std::ofstream file(path2file, std::ios::trunc);
    if(!file.is_open())
    {
        std::cout << "ERROR (ParitelTelemetryGen::save2txt): error ofstream open file" << std::endl;
        return false;
    }
    file << frameNumber << "\n";
    file << telemetryNumberAP << "\n";
    file << std::setw(4) << std::setfill('0') << date_year << "-";
    file << std::setw(2) << std::setfill('0') << date_month << "-";
    file << std::setw(2) << std::setfill('0') << date_day << "\n";
    file << std::setw(2) << std::setfill('0') << time_hour << ":";
    file << std::setw(2) << std::setfill('0') << time_min << ":";
    if(time_sec < 10)
    {
        file << "0";
    }
    file << std::fixed << std::setprecision(3) << time_sec << "\n";
    file << std::setw(10) << std::setfill('0') << time_ms << "\n";
    file << std::fixed << std::setprecision(5) << roll_deg << " " << pitch_deg << " " << yaw_deg << "\n";
    file << std::fixed << std::setprecision(5) << altitude_m << " " << altitude_bar_m << "\n";
    file << std::fixed << std::setprecision(5) << heading_deg << "\n";
    file << std::fixed << std::setprecision(5) << latitude_deg << " " << longitude_deg << "\n";
    file << std::fixed << std::setprecision(5) << speed_mps << " " << airspeed_mps << "\n";
    file << std::fixed << std::setprecision(5) << gx << " " << gy << " " << gz << "\n";
    file << std::fixed << std::setprecision(5) << ang_rate_x_dps << " " << ang_rate_y_dps << " " << ang_rate_z_dps << "\n";
    file << std::fixed << std::setprecision(5) << vel_longit_mps << " " << vel_transv_mps << " " << vel_vertical_mps << "\n";
    file << std::fixed << std::setprecision(3) << exposure_ms << "\n";
    file << std::fixed << std::setprecision(1) << cpu_temp_deg << "\n";
    file.close();
    return true;
}

bool ParitelTelemetryGen::readFromTxt(const std::string &path2file)
{
    const int cnt_rows_in_txt_file = 15;
    if(!path_processing::isRegularFileExist(path2file))
    {
        std::cout << "ERROR: (ParitelTelemetryGen::readFromTxt): path2file not exist" << "\n";
        std::cout << "\tpath2file = "<< path2file << std::endl;
        return false;
    }
    std::ifstream file(path2file, std::ios::in);
    if(!file.is_open())
    {
        std::cout << "ERROR: (ParitelTelemetryGen::readFromTxt): failed ifstream open path2file" << "\n";
        std::cout << "\tpath2file = " << path2file << std::endl;
        return false;
    }
    std::vector<std::string> content;
    std::string line;
    bool valid_read_content = true;
    content.reserve(cnt_rows_in_txt_file);
    for(int i = 0; i < cnt_rows_in_txt_file; ++i)
    {
        if(std::getline(file, line), '\n')
        {
            content.push_back(line);
        }
        else
        {
            valid_read_content = false;
            break;
        }
    }
    if(!valid_read_content)
    {
        file.close();
        return false;
    }

    std::cout << "dbg:: Read ParitelGenData:: ok content!" << std::endl;
    std::cout << "content.size = " << content.size() << std::endl;

    frameNumber = std::stol(content[0]);
    telemetryNumberAP = std::stol(content[1]);

    std::vector<std::string> date_split;
    split(content[2], date_split, '-');
    date_year = std::stoi(date_split[0]);
    date_month = std::stoi(date_split[1]);
    date_day = std::stoi(date_split[2]);

    std::vector<std::string> time_split;
    split(content[3], time_split, ':');
    time_hour = std::stoi(time_split[0]);
    time_min = std::stoi(time_split[1]);
    time_sec = std::stod(time_split[2]);


    time_ms = std::stol(content[4]);

    std::vector<std::string> orientation_split;
    split(content[5], orientation_split, ' ');
    roll_deg = std::stof(orientation_split[0]);
    pitch_deg = std::stof(orientation_split[1]);
    yaw_deg = std::stof(orientation_split[2]);

    std::vector<std::string> altitude_split;
    split(content[6], altitude_split, ' ');
    altitude_m = std::stof(altitude_split[0]);
    altitude_bar_m = std::stof(altitude_split[1]);

    heading_deg = std::stof(content[7]);

    std::vector<std::string> navigation_split;
    split(content[8], navigation_split, ' ');
    latitude_deg = std::stof(navigation_split[0]);
    longitude_deg = std::stof(navigation_split[1]);

    std::vector<std::string> speed_split;
    split(content[9], speed_split, ' ');
    speed_mps = std::stof(speed_split[0]);
    airspeed_mps = std::stof(speed_split[1]);

    std::vector<std::string> override_split;
    split(content[10], override_split, ' ');
    gx = std::stof(override_split[0]);
    gy = std::stof(override_split[1]);
    gz = std::stof(override_split[2]);

    std::vector<std::string> ang_rate_split;
    split(content[11], ang_rate_split, ' ');
    ang_rate_x_dps = std::stof(ang_rate_split[0]);
    ang_rate_y_dps = std::stof(ang_rate_split[1]);
    ang_rate_z_dps = std::stof(ang_rate_split[2]);

    std::vector<std::string> ap_vel_split;
    split(content[12], ap_vel_split, ' ');
    vel_longit_mps = std::stof(ap_vel_split[0]);
    vel_transv_mps = std::stof(ap_vel_split[1]);
    vel_vertical_mps = std::stof(ap_vel_split[2]);

    exposure_ms = std::stof(content[13]);
    cpu_temp_deg = std::stof(content[14]);

    file.close();
    return true;
}
