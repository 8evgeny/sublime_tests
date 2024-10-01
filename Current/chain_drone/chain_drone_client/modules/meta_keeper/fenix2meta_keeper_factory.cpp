#include "fenix2meta_keeper.hpp"

#include "ExtendINIReader.hpp"

namespace fenix2meta_keeper
{

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

    settings_dst.section_name = section;
    settings_dst.path2ini = path2ini;

    bool ini_report = true;

    ini_report &= ext_ini::GetInteger(reader, section, "max_delay_btw_packs_ms",    settings_dst.max_delay_btw_packs_ms);

    std::cout << "END " << section << "::readIniSettings" << std::endl;
    return ini_report;
} // -- END readIniSettings

std::shared_ptr<Fenix2MetaKeeper> create(
    const std::string &path2ini, const std::string &section)
{
    Settings settings;
    if(!readIniSettings(path2ini, section, settings))
    {
        std::cout << "ERROR: call readIniSettings return false" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Fenix2MetaKeeper> cam_ptr = std::make_shared<Fenix2MetaKeeper>(settings);
    return cam_ptr;
} // -- END create

} // -- namespace fenix2meta_keeper
