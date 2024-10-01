#ifndef RTP_SERVER_H264_SETTINGS_HPP
#define RTP_SERVER_H264_SETTINGS_HPP

#include <string>
#include <memory>
#include <iostream>

#include "INIReader.h"
#include "eth_cnt_common_utils/eth_cnt_common_utils.hpp"
#include "toolbox_common_utils/toolbox_common_utils.hpp"

namespace rtp::server::h264
{
struct VideoSettings
{
    std::string format = "BGR";
    int width = 1024;
    int height = 600;
    int framerate = 40;
};

struct EncoderSettings
{
    int bitrate = 2048;
    int quantizer = 21;
    int ref = 3;
};

struct PaySettings
{
    int configInterval = 1;
    int pt = 26;
    int mtu = 1400;
};

struct UdpSettings
{
    std::string host = "127.0.0.1";
    int port = 8080;
};

struct Settings
{
    VideoSettings video;
    EncoderSettings encoder;
    PaySettings pay;
    UdpSettings udp;
};

bool getIniSettings(const std::string &path2ini,
                    const std::string &ini_section_name,
                    Settings &settings);

using SettingsPtr = std::shared_ptr<Settings>;

} // END namespace rtp::server

#endif // RTP_SETTINGS
