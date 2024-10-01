#ifndef FENIX2CMD_KEEPER_FACTORY_HPP
#define FENIX2CMD_KEEPER_FACTORY_HPP

#include <memory>
#include <string>

#include "fenix2cmd_keeper.hpp"

namespace fenix2cmd_keeper
{
std::shared_ptr<Fenix2CmdKeeper> create(
        const std::string &path2ini,
        const std::string &section);

bool readIniSettings(const std::string &path2ini, const std::string section, Settings &settings_dst);

} // -- namespace ap_tele_keeper

#endif //FENIX2CMD_KEEPER_FACTORY_HPP
