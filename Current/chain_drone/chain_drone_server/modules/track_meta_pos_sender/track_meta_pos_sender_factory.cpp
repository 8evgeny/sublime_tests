#include "track_meta_pos_sender_factory.hpp"
#include "ExtendINIReader.hpp"

using namespace track_meta_sender;

bool readIniSettings(const std::string &path2ini, const std::string section, Settings &settings_dst)
{
    // std::string deviceName = "HVGS_Gray_USB_CameraNL";
    std::cout << "BEGIN " << section << "::readIniSettings\n";
    INIReader reader(path2ini);
    if(reader.ParseError() < 0)
    {
        std::cout << "ini reader parse error!\n";
        return false;
    }

    settings_dst.section = section;
    settings_dst.path2ini = path2ini;

    bool ini_report = true;

    ini_report &= ext_ini::GetInteger(reader, section, "fps_stream",    settings_dst.fps_stream);

    int use_cmd_net_id_tmp;
    ini_report &= ext_ini::GetInteger(reader, section, "use_cmd_net_id", use_cmd_net_id_tmp);
    settings_dst.use_cmd_net_id = static_cast<bool>(use_cmd_net_id_tmp);
    ini_report &= ext_ini::GetInteger(reader, section, "tracker_metadata_cmd_net_id", settings_dst.cmd_net_id);

    std::cout << "END " << section << "::readIniSettings" << std::endl;
    return ini_report;
} // -- END readIniSettings

std::shared_ptr<TrackMetaPosSender> track_meta_sender::create(const std::string &path2ini, const std::string &section)
{
    Settings settings;
    if(!readIniSettings(path2ini, section, settings))
    {
        std::cout << "ERROR: call readIniSettings return false" << std::endl;
        return nullptr;
    }

    std::shared_ptr<TrackMetaPosSender> cam_ptr = std::make_shared<TrackMetaPosSender>(settings);
    return cam_ptr;
} // -- END create
