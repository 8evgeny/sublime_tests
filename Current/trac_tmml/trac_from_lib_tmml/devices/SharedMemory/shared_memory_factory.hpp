#ifndef SHARED_MEMORY_FACTORY_HPP
#define SHARED_MEMORY_FACTORY_HPP

#include <memory>
#include <string>
#include "shared_memory.hpp"

namespace devices::shared_memory
{
    UserSettings readSettings(const std::string &pathToSettings, bool &success);
    bool checkValidAndAdaptationSettings(UserSettings &settings);
    std::shared_ptr<SharedMemory> create(const std::string &config_path);

} // -- END namespace devices::shared_memory

#endif // SHARED_MEMORY_FACTORY_HPP
