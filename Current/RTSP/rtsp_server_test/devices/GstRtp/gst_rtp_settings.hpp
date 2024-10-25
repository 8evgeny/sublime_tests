#ifndef GST_RTP_SETTINGS_HPP
#define GST_RTP_SETTINGS_HPP

#include <string>
#include <memory>

namespace devices::gst_rtp
{
    enum CameraModes
    {
        CAM_MODE_1920_1080_60FPS,
        CAM_MODE_3840_2160_30FPS,
        CAM_MODE_4032_3040_20FPS
    };

    struct SrcSettings
    {
      std::string ip = "127.0.0.1";
      std::string port = "8081";
    };

    struct UserSettings
    {
        int sensor_id = 0;
        int camera_mode =  0;
        int square_crop_sz = 1000;
        int fps_denominator = 1;
        int square_out_sz = 1080;
        int max_buffers = 3;
    };

    struct CameraSettings
    {
        int sensor_id = 0; // идентификатор сенсора в сис
    };

    struct VideoSettings // Запрашиваемые параметры видеопотока в gstreamer
    {
        VideoSettings(
            int _width,
            int _height,
            int _fps) :
        width(_width),
        height(_height),
        fps(_fps)
        {

        }

        VideoSettings()
        {

        }

        int width = 0;
        int height = 0;
        int fps = 0;
    };

    struct OutputSettings
    {
        int fps = 1; // fps denominator
        int max_buffers = 3;// объем буффера gstreamer для складирования ожидающих выгрузки изображений
    };

    struct Settings
    {
        SrcSettings src;
        UserSettings usr;
        CameraSettings camera;
        VideoSettings video;
        OutputSettings output;
    };
} // END -- devices::gst_rtp

#endif //GST_RTP_SETTINGS_HPP
