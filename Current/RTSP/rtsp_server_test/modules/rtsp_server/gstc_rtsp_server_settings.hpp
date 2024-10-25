#ifndef GSTC_RTSP_SERVER_SETTINGS_HPP
#define GSTC_RTSP_SERVER_SETTINGS_HPP

#include <string>
#include <iostream>

namespace rtsp::server
{

struct NetSettings
{
  std::string ip = "127.0.0.1";
  int port = 8081;
  std::string name = "main";
}; // END NetSettings

struct VideoSettings
{
    std::string format = "RGB16";
    int width = 1920;
    int height = 1080;
    int fps = 30;
}; // END struct NetSettings

struct EncoderSettings
{
    int frame_I_time = 5; // sec
    std::string latency = "zerolatency";
    std::string speed_preset = "superfast";
    int bitrate = 8192;
    int clock_rate = 90000;
}; // END EncSettings

struct PaySettings
{
    int config_interval = 1; // sec
}; // END PaySettings

struct SettingsRtspSrv
{
    NetSettings net;
    VideoSettings vid;
    EncoderSettings enc;
    PaySettings pay;
}; // END SettingsRtspSrv

}; // END namespace rtsp
#endif //!GSTC_RTSP_SERVER_SETTINGS_HPP
