#ifndef GST_RTP_FACTORY_HPP
#define GST_RTP_FACTORY_HPP

#include <memory>
#include <string>
#include <iostream>
#include "gst_rtp.hpp"
#include "tools/ExtendINIReader.hpp"
#include "toolbox_common_utils/toolbox_common_utils.hpp"
#include "tools/INIReader.h"
#include "tools/ExtendINIReader.hpp"
#include "toolbox_common_utils.hpp"

namespace devices::gst_rtp
{
    Settings readSettings(const std::string &pathToSettings, const std::string & ini_section_name, bool &success);
    bool checkValidAndAdaptationSettings(UserSettings &settings);
    std::shared_ptr<GstRtp> create(const std::string &config_path, const std::string & ini_section_name);

} // -- END namespace devices::gst_rtp

#endif // GST_RTP_FACTORY_HPP
