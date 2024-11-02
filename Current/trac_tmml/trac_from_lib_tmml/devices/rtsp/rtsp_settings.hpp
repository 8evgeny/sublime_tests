#ifndef RTSP_SETTINGS_HPP
#define RTSP_SETTINGS_HPP

#include <string>
#include <memory>

namespace devices::rtsp
{
//    enum CameraModes
//    {
//        CAM_MODE_0 = 0,
//        CAM_MODE_3840_2160_6FPS = 1, // max birate = 16384
//        CAM_MODE_1280_720_20FPS = 2, // max birate = 8192
//        CAM_MODE_LAST = 3
//    }; // END CameraModes

    struct RtspsrcSettings
    {
        std::string ip = "127.0.0.1";
        std::string codec = "h265";
        int port = 8888;
        int channel = 1;
        int latency = 0;
    }; // END RtspsrcSettings

    struct AppsinkSettings
    {
        std::string name = "sink";
        std::string emit_signals = "true";
        std::string sync = "false";
        int max_buffers = 3;
        std::string drop = "true";
    }; // END AppsinkSettings

    struct VideoSettings // Запрашиваемые параметры видеопотока в gstreamer 
    {
        VideoSettings(int _width, int _height,int _fps) : width(_width), height(_height), fps(_fps){}
        VideoSettings(){}
        int width = 1920;
        int height = 1080;
        int fps = 30;
        std::string mountpoint = "imx415video";
    }; // END VideoSettings

    struct OutputSettings
    {
        std::string format_out = "BGR";
        int square_mode = 0;
        int square_size = 2160;
        int fps = 1; // fps denominator
        int max_buffers = 3;// объем буффера gstreamer для складирования ожидающих выгрузки изображений 
    }; // END OutputSettings

    struct Settings
    {
        RtspsrcSettings src;
        AppsinkSettings sink;
        VideoSettings video;
        OutputSettings output;
    }; // END Settings

    using SettingsPtr = std::shared_ptr<Settings>;

} // END -- namespace devices::rtsp

#endif //RTSP_SETTINGS_HPP
