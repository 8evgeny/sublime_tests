#include "teletxt_api.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#include "tools/string_toolbox/string_processing.hpp"
#include "tools/path_processing/path_processing.hpp"

const std::vector<std::string> teletxtAliases
{
    "kren_deg",
    "tangazh_deg",
    "azimut_deg",
    "gps_long",
    "gps_lat",
    "alt_gps",
    "alt_bar",
    "alt_radio",
    "alt_work",
    "exposure_ms",
    "cpu_temp_deg"
};

std::vector<float const *> getLinkVecTeleTxt(const Teletxt& tele_txt_src)
{
    return std::vector<float const *>
    {
        &tele_txt_src.roll_deg,
        &tele_txt_src.pitch_deg,
        &tele_txt_src.yaw_deg,
        &tele_txt_src.longitude,
        &tele_txt_src.latitude,
        &tele_txt_src.alt_gps,
        &tele_txt_src.alt_bar,
        &tele_txt_src.alt_radio,
        &tele_txt_src.alt_work,
        &tele_txt_src.exposure_ms,
        &tele_txt_src.cpu_temp_deg
    };
} // -- END getLinkVecTeleTxt

std::vector<float*> getLinkVecTeleTxt(Teletxt& tele_txt_src)
{
    const Teletxt& const_tele_txt = tele_txt_src;
    std::vector<float const *> const_vec = getLinkVecTeleTxt(const_tele_txt);
    std::vector<float*> result_vec;
    result_vec.reserve(const_vec.size());
    for(int i = 0; i < const_vec.size(); ++i)
    {
        result_vec.push_back(const_cast<float*>(const_vec[i]));
    }
    return result_vec;
} // -- END getLinkVecTeleTxt

bool readTeletxt(
    const std::string &path2file,
    Teletxt &tele_dst)
{
    std::ifstream file(path2file);
    if(!file.is_open())
    {
        return false;
    }

    std::vector<float *> link_vec = getLinkVecTeleTxt(tele_dst);

    std::string line;
    std::vector <std::string> sub_lines;
    bool success_read = true;
    for(int i = 0; i < link_vec.size(); ++i)
    {
        if(!std::getline(file, line))
        {
            std::cout << "ERROR: read teletxt failed" << std::endl;
            success_read = false;
            break;
        }
        strip(line, ' ');
        split(line, sub_lines, ' ');
        const std::string &cur_valid_alias = teletxtAliases[i];
        if(sub_lines.size() != 2 || sub_lines[0] != cur_valid_alias)
        {
            success_read = false;
            break;
        }
        *(link_vec[i]) = std::stof(sub_lines[1]); 
    } // -- END for(int i = 0; i < link_vec.size(); ++i)
    
    file.close();

    return success_read;
} // -- END readTeleTxt

bool writeTeletxt(
    const Teletxt &tele_txt,
    const std::string path2file,
    bool force_replace)
{
    if(path_processing::isRegularFileExist(path2file) && !force_replace)
    {
        return false;
    }
    std::ofstream file(path2file, std::ios::trunc);
    if(!file.is_open())
    {
        return false;
    }   

    static std::vector<float const *> link_vec = getLinkVecTeleTxt(tele_txt);

    for(size_t i = 0; i < link_vec.size(); ++i)
    {
        file << teletxtAliases[i] << " " << *(link_vec[i]) << "\n";
    }

    file.close();
    return true;
} // -- END writeTeletxt
