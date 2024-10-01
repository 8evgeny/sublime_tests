#ifndef TELETXT_API_HPP
#define TELETXT_API_HPP

#include <string>
#include <vector>

struct Teletxt
{
    float roll_deg      = 0;
    float pitch_deg     = 0;
    float yaw_deg       = 0;
    float longitude     = 0;
    float latitude      = 0;
    float alt_gps       = 0;
    float alt_bar       = 0;
    float alt_radio     = 0;
    float alt_work      = 0;
    float exposure_ms   = 0;
    float cpu_temp_deg  = 0;
}; // -- Teletxt

bool readTeletxt(
    const std::string &path2file,
    Teletxt &tele_dst);

bool writeTeletxt(
    const Teletxt &teletxt,
    const std::string path2file,
    bool force_replace = true);

#endif // TELETXT_API_HPP