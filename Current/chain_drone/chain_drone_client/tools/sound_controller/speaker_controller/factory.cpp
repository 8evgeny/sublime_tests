#include "factory.hpp"
#include "tools/INIReader.h"

#include <iostream>

using namespace sound;

static speaker::SettingsPtr readSettings(const std::string & pathToSettings)
{
    speaker::SettingsPtr settings = std::make_shared<speaker::Settings>();
    const std::string deviceName = "speaker";
    INIReader reader(pathToSettings);
    if(reader.ParseError() < 0)
    {
        std::cout << "ini reader parse error!\n";
        return settings;
    }
    std::cout << "Begin SpeakerController::readSettings\n";

    std::string temp_device = reader.Get(deviceName, "device", "oops");
    if(temp_device == "oops")
    {
        std::cout << "\t device not declared!\n";
    }
    else
    {
        settings->device = temp_device;
        std::cout << "\t device = " << settings->device << ";\n";
    }

    int temp_volume = reader.GetInteger(deviceName, "volume", -1);
    if(temp_volume == -1)
    {
        std::cout << "\t volume not declared!!" << std::endl;
    }
    else
    {
        settings->defaultVolume = temp_volume;
        std::cout << "\t volume = " << settings->defaultVolume << ";\n";
    }

    std::string temp_sound = reader.Get(deviceName, "sound", "oops");
    if(temp_sound == "oops")
    {
        std::cout << "\t sound not declared!\n";
    }
    else
    {
//        settings->sounds.error = temp_sound.c_str();
//        settings->sounds.warning = temp_sound.c_str();
        settings->sounds.error = temp_sound;
        settings->sounds.warning = temp_sound;
        std::cout << "\t warning sound = " << settings->sounds.warning << ";\n";
        std::cout << "\t error sound = " << settings->sounds.error << ";\n";
    } // -- END readSettings

    std::cout << "End SpeakerController::readSettings\n";
    return settings;
}

SpeakerController &sound::speaker::create(const std::string &pathToSettings)
{
    auto settings = readSettings(pathToSettings);
    SpeakerController::inst().setSettings(settings);
    return SpeakerController::inst();
}
