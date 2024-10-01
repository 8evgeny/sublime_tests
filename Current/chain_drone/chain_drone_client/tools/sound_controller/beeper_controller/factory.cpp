#include "factory.hpp"
#include "tools/INIReader.h"

#include <iostream>

using namespace sound;

static std::vector<int> split(std::string &str, char d)
{
    std::vector<int> r;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        if (stop != 0)
        {
            r.push_back(std::stoi(str.substr(0, stop)));
        }
        str.erase(0, stop + 1);
        stop = str.find_first_of(d, 0);
    }
    if(!str.empty())
    {
        r.push_back(std::stoi(str));
    }
    return r;
}

static beeper::SettingsPtr readSettings(const std::string &pathToSettings)
{
    beeper::SettingsPtr settings = std::make_shared<beeper::Settings>();
    const std::string deviceName = "beeper";
    INIReader reader(pathToSettings);
    if(reader.ParseError() < 0)
    {
        std::cout << "ini reader parse error!\n";
        return settings;
    }
    std::cout << "Begin BeeperController::readSettings\n";

    std::string pins = reader.Get(deviceName, "pins", "oops");
    if(pins == "oops")
    {
        std::cout << "\t pins not declared!\n";
    }
    else
    {
        settings->pins = split(pins, ',');
        std::cout << "\t pins = ";
        for(auto const &pin : settings->pins)
        {
            std::cout << pin << ", ";
        }
        std::cout << std::endl;
    }

    int lavel = reader.GetInteger("Jetson", "GPIO_lavel", -1);
    if(lavel == -1)
    {
        std::cout << "\t Jetson GPIO_lavel not declared!\n";
    }
    else
    {
        settings->defaultLavel = static_cast<beeper::LAVEL>(lavel);
        std::cout << "\t Jetson GPIO_lavel = " << lavel << std::endl;
    }

    std::cout << "End BeeperController::readSettings\n";
    return settings;
}

BeeperController &sound::beeper::create(const std::string &pathToSettings)
{
    auto settings = readSettings(pathToSettings);
    BeeperController::inst().setSettings(settings);
    return BeeperController::inst();
}
