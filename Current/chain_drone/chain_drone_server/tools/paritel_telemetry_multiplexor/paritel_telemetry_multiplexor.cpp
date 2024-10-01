#include "paritel_telemetry_multiplexor.hpp"

#include <ctime>
#include <chrono>
#include "tools/sys_time_toolbox/sys_time_extract.hpp"


namespace telemetry_mux
{
double deg2rad(double angle_deg)
{
    return angle_deg * M_PI / 180.f;
}

double rad2deg(double angle_rad)
{
    return angle_rad * 180.f / M_PI;
}

void conv_ESRT_to_TeleGen(
        const ESRTdata &esrt_src,
        ParitelTelemetryGen &teleGen_dst)
{
    /* ######################## MAJOR ################################## */
    teleGen_dst.frameNumber             = esrt_src.frameNumber;
    teleGen_dst.telemetryNumberAP       = -1;
    teleGen_dst.date_year               = esrt_src.date.year;
    teleGen_dst.date_month              = esrt_src.date.month;
    teleGen_dst.date_day                = esrt_src.date.day;
    teleGen_dst.time_hour               = esrt_src.time.hour;
    teleGen_dst.time_min                = esrt_src.time.min;
    teleGen_dst.time_sec                = esrt_src.time.sec;
    teleGen_dst.time_ms                 = 0;
    teleGen_dst.roll_deg                = esrt_src.orientation_deg.roll;
    teleGen_dst.pitch_deg               = esrt_src.orientation_deg.pitch;
    teleGen_dst.yaw_deg                 = esrt_src.orientation_deg.yaw;
    teleGen_dst.altitude_m              = esrt_src.current_altitude_m;

    /* ######################## MINOR ################################## */
    teleGen_dst.altitude_bar_m          = esrt_src.ref_altitude_m.abs_alt;
    teleGen_dst.heading_deg             = -1;
    teleGen_dst.latitude_deg            = esrt_src.navigation.latitude;
    teleGen_dst.longitude_deg           = esrt_src.navigation.longitude;
    teleGen_dst.speed_mps               = -1;
    teleGen_dst.airspeed_mps            = -1;
    teleGen_dst.gx                      = -1;
    teleGen_dst.gy                      = -1;
    teleGen_dst.gz                      = -1;
    teleGen_dst.ang_rate_x_dps          = -1;
    teleGen_dst.ang_rate_y_dps          = -1;
    teleGen_dst.ang_rate_z_dps          = -1;
    teleGen_dst.vel_longit_mps          = -1;
    teleGen_dst.vel_transv_mps          = -1;
    teleGen_dst.vel_vertical_mps        = -1;
} // -- END conv_ESRT_to_TeleGen

void conv_Teletxt_to_TeleGen(
        const Teletxt &teleTxt_src,
        int _frameNumber,
        ParitelTelemetryGen &teleGen_dst)
{
    float deg2rad = 3.14 / 180.f ;
    teleGen_dst.frameNumber             = _frameNumber;
    teleGen_dst.telemetryNumberAP       = 0;
    teleGen_dst.date_year               = 0;
    teleGen_dst.date_month              = 0;
    teleGen_dst.date_day                = 0;
    teleGen_dst.time_hour               = 0;
    teleGen_dst.time_min                = 0;
    teleGen_dst.time_sec                = 0;
    teleGen_dst.time_ms                 = 0;
    teleGen_dst.roll_deg                = teleTxt_src.roll_deg;
    teleGen_dst.pitch_deg               = teleTxt_src.pitch_deg;
    teleGen_dst.yaw_deg                 = teleTxt_src.yaw_deg;
    teleGen_dst.altitude_m              = teleTxt_src.alt_radio;
    teleGen_dst.altitude_bar_m          = teleTxt_src.alt_bar;
    teleGen_dst.latitude_deg            = teleTxt_src.latitude;
    teleGen_dst.longitude_deg           = teleTxt_src.longitude;
    teleGen_dst.airspeed_mps            = -1;
    teleGen_dst.gx                      = -1;
    teleGen_dst.gy                      = -1;
    teleGen_dst.gz                      = -1;
    teleGen_dst.ang_rate_x_dps          = -1;
    teleGen_dst.ang_rate_y_dps          = -1;
    teleGen_dst.ang_rate_z_dps          = -1;
    teleGen_dst.vel_longit_mps          = -1;
    teleGen_dst.vel_transv_mps          = -1;
    teleGen_dst.vel_vertical_mps        = -1;
} // -- END conv_Teletxt_to_TeleGen

void conv_TeleGen_to_Teletxt(
        const ParitelTelemetryGen &teleGen_src,
        Teletxt &teleTxt_dst)
{
    teleTxt_dst.roll_deg      = teleGen_src.roll_deg;
    teleTxt_dst.pitch_deg     = teleGen_src.pitch_deg;
    teleTxt_dst.yaw_deg       = teleGen_src.yaw_deg;
    teleTxt_dst.longitude     = teleGen_src.longitude_deg;
    teleTxt_dst.latitude      = teleGen_src.latitude_deg;
    teleTxt_dst.alt_gps       = -1;
    teleTxt_dst.alt_bar       = teleGen_src.altitude_bar_m;
    teleTxt_dst.alt_radio     = teleGen_src.altitude_m;
    teleTxt_dst.alt_work      = teleGen_src.altitude_m;
    teleTxt_dst.exposure_ms   = teleGen_src.exposure_ms;
    teleTxt_dst.cpu_temp_deg  = teleGen_src.cpu_temp_deg;
} // -- END conv_TeleGen_to_Teletxt

// ParitelTelemetryAP --> ParitelTelemetryGen
void conv_TeleAP_to_TeleGen(
        const ParitelTelemetryAP &teleAP_src,
        int _frameNumber,
        ulong _time_ms,
        ParitelTelemetryGen &teleGen_dst)
{
    syst_time_extract::DateTime dateTime = syst_time_extract::getCurrentDateTime();

    /* ######################## MAJOR ################################## */
    teleGen_dst.frameNumber             = _frameNumber;
    teleGen_dst.telemetryNumberAP       = teleAP_src.uid;
    teleGen_dst.date_year               = dateTime.year;
    teleGen_dst.date_month              = dateTime.month;
    teleGen_dst.date_day                = dateTime.day;
    teleGen_dst.time_hour               = dateTime.hour;
    teleGen_dst.time_min                = dateTime.min;
    teleGen_dst.time_sec                = dateTime.sec;
    teleGen_dst.time_ms                 = _time_ms;
    teleGen_dst.roll_deg                = teleAP_src.roll_deg;
    teleGen_dst.pitch_deg               = teleAP_src.pitch_deg;
    teleGen_dst.yaw_deg                 = teleAP_src.yaw_deg;
    teleGen_dst.altitude_m              = teleAP_src.altitude_m;

    /* ######################## MINOR ################################## */
    teleGen_dst.altitude_bar_m          = teleAP_src.altitude_bar_m;
    teleGen_dst.heading_deg             = teleAP_src.heading_deg;
    teleGen_dst.latitude_deg            = teleAP_src.latitude_deg;
    teleGen_dst.longitude_deg           = teleAP_src.longitude_deg;
    teleGen_dst.speed_mps               = teleAP_src.speed_mps;
    teleGen_dst.airspeed_mps            = teleAP_src.airspeed_mps;
    teleGen_dst.gx                      = teleAP_src.gx;
    teleGen_dst.gy                      = teleAP_src.gy;
    teleGen_dst.gz                      = teleAP_src.gz;
    teleGen_dst.ang_rate_x_dps          = teleAP_src.ang_rate_x_dps;
    teleGen_dst.ang_rate_y_dps          = teleAP_src.ang_rate_y_dps;
    teleGen_dst.ang_rate_z_dps          = teleAP_src.ang_rate_z_dps;
    teleGen_dst.vel_longit_mps          = teleAP_src.vel_longit_mps;
    teleGen_dst.vel_transv_mps          = teleAP_src.vel_transv_mps;
    teleGen_dst.vel_vertical_mps        = teleAP_src.vel_vertical_mps;
} // -- conv_TeleAP_to_TeleGen

} // -- telemetry_mux
