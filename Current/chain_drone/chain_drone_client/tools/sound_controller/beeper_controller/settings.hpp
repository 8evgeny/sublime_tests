#ifndef BEEPER_CONTROLLER_SETTINGS_HPP
#define BEEPER_CONTROLLER_SETTINGS_HPP

#include <string>
#include <vector>
#include <memory>

namespace sound::beeper
{
enum class LAVEL : uint8_t
{
    LOW = 0,
    HIGH = 1
};

struct Settings
{
    LAVEL defaultLavel = LAVEL::LOW;
    std::vector<int> pins;
    struct Sounds
    {
        int system = 100;
        int alarm = 500;
    } sounds;
};

using SettingsPtr = std::shared_ptr<Settings>;
}

#endif // BEEPER_CONTROLLER_SETTINGS_HPP
