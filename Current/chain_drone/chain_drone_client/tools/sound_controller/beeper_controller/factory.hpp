#ifndef BEEPER_CONTROLLER_FACTORY_HPP
#define BEEPER_CONTROLLER_FACTORY_HPP

#include "beeper_controller.hpp"

namespace sound::beeper
{
    BeeperController &create(const std::string &pathToSettings);
}

#endif // BEEPER_CONTROLLER_FACTORY_HPP
