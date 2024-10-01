#ifndef ETH_CHAIN_DRONE_AP_TELEMETRY_KEEPER_FACTORY_HPP
#define ETH_CHAIN_DRONE_AP_TELEMETRY_KEEPER_FACTORY_HPP

#include <memory>
#include <string>

#include "eth_chain_drone_ap_telemetry_keeper.hpp"

namespace chain_drone_ap_tele_keeper
{
std::shared_ptr<APTeleKeeper> create(
        const std::string &path2ini,
        const std::string &section);
} // -- namespace chain_drone_ap_tele_keeper

#endif //ETH_AP_TELEMETRY_KEEPER_FACTORY_HPP
