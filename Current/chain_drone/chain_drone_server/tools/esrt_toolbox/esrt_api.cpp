#include "esrt_api.hpp"

using namespace esrt_tools;

bool writeESRT(
    const ESRTdata &esrt, 
    const std::string &path2file, 
    bool force_replace)
{
    if(!force_replace)
    {
        if(isRegularFileExist(path2file))
        {
            std::cout << "ERROR (writeESRT): file is exist, but not enable force_replace" << std::endl;
            return false;
        }
    };
    
    std::ofstream file(path2file, std::ios::trunc);
    if(!file.is_open())
    {
        std::cout << "ERROR (writeESRT): file path=\"" 
            << path2file << "\" not open" << std::endl;
        return false;
    }
    
    file << "frame_n = " << esrt.frameNumber << "\n";
    file << "start_frame_time = " << esrt.startFrameTime.to_string() << "\n";
    file << "end_frame_time = " << esrt.endFrameTime.to_string() << "\n";
    file << "date = " << esrt.date.to_string() << "\n";
    file << "time_global = " << esrt.time.to_string() << "\n";
    file << "navigation = " << esrt.navigation.to_string() << "\n";
    file << "reference_altitude_m = " << esrt.ref_altitude_m.to_string() << "\n";
    file << "current_altitude_m = " << std::fixed << std::setprecision(3) << esrt.current_altitude_m << "\n";
    file << "shift_altitude_m = " << std::fixed << std::setprecision(3) << esrt.shift_altitude_m << "\n";
    file << "orientation_deg = " << esrt.orientation_deg.to_string() << "\n";
    file << "shift_xy_m = " <<  esrt.shift_xy_m.to_string();
    
    file.close();
    return true;
} // -- END writeESRT

bool parseESRT(const std::string &path2file, ESRTdata &esrt_dst)
{
    if(!isRegularFileExist(path2file))
    {
        std::cout << "ERROR (parseESRT): path2file=\"" << path2file << "\" not exist!" << std::endl;
        return false;
    }
    std::ifstream file(path2file, std::ios::in);
    if(!file.is_open())
    {
        std::cout << "ERROR (parseESRT): file path=\"" 
            << path2file << "\" not open" << std::endl;
        return false;        
    }

    ESRTdata esrt_tmp;
    std::string line;
    
    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseLabeledLongInteger(line, "frame_n", esrt_tmp.frameNumber))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseTimeESRT(line, "start_frame_time", esrt_tmp.startFrameTime))
    {
        return false;
    }
    
    if(!std::getline(file, line))
    {
        return false;
    }        
    if(!parseTimeESRT(line, "end_frame_time", esrt_tmp.endFrameTime))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseDateESRT(line, "date", esrt_tmp.date))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseTimeESRT(line, "time_global", esrt_tmp.time))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseNavigationESRT(line, "navigation", esrt_tmp.navigation))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseAltitudeESRT(line, "reference_altitude_m", esrt_tmp.ref_altitude_m))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseLabeledDouble(line, "current_altitude_m", esrt_tmp.current_altitude_m))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseLabeledDouble(line, "shift_altitude_m", esrt_tmp.shift_altitude_m))
    {
        return false;
    }

    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseOrientationESRT(line, "orientation_deg", esrt_tmp.orientation_deg))
    {
        return false;
    }
    
    if(!std::getline(file, line))
    {
        return false;
    }
    if(!parseShiftXY_ESRT(line, "shift_xy_m", esrt_tmp.shift_xy_m))
    {
        return false;
    }
    esrt_dst = esrt_tmp; //TODO: fix slow solution
    file.close();
    return true;
} // -- END parseESRT
