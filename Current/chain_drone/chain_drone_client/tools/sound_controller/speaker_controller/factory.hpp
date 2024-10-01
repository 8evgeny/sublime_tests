#ifndef SPEAKER_CONTROLLER_FACTORY_HPP
#define SPEAKER_CONTROLLER_FACTORY_HPP

#include "speaker_controller.hpp"

namespace sound::speaker
{
    SpeakerController &create(const std::string &pathToSettings);
}

#endif // SPEAKER_CONTROLLER_FACTORY_HPP
