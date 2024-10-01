#ifndef SPEAKER_CONTROLLER_SETTINGS_HPP
#define SPEAKER_CONTROLLER_SETTINGS_HPP

#include <string>
#include <memory>

namespace sound::speaker
{
struct Settings
{
    std::string device;
    int defaultVolume = 35; // %
    struct Sounds
    {
        std::string warning = "echo -en '\007'";
        std::string error = "echo -en '\007'";
    } sounds;
};

using SettingsPtr = std::shared_ptr<Settings>;
}

#endif // SPEAKER_CONTROLLER_SETTINGS_HPP
