#ifndef ETH_CHAIN_DRONE_AP_TELEMETRY_KEEPER_HPP
#define ETH_CHAIN_DRONE_AP_TELEMETRY_KEEPER_HPP

// std
#include <mutex>
#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>

#include "modules/chain_drone_telemetry_ap/chain_drone_telemetry_ap.hpp"

// eth
#include "command_processing/commands_zoo/eth_cmd_base.hpp"
#include "command_processing/commands_zoo/chain_drone_ap_telemetry/chain_drone_ap_telemetry_eth_cmd.hpp"
#include "command_processing/icmdhandler.hpp"
#include "notification_handler/iethnotifyhandler.hpp"
#include "command_processing/cmd_handlers_distributor/cmd_handlers_distributor.hpp"
#include "udp_modules/async_udp_eth_controller_cmd/async_udp_eth_controller_cmd_factory.hpp"

// for log
#include "tools/sys_time_toolbox/sys_time_extract.hpp"

namespace chain_drone_ap_tele_keeper
{

enum TeleKeeperLogMode
{
    LOG_MODE_OFF,
    LOG_MODE_ON_ORIENT_ONLY //, // pitch, roll, yaw, alt
    // LOG_MODE_ON_FULL // TODO: add some modes
};

struct Settings
{
    int max_delay_btw_packs_ms  = 1'500;
    std::string path2ini        = "../settings.ini";
    std::string section_name    = "APTelemetryKeeper";
};

class APTeleKeeper : // AutoPilot Telemetry Keeper
   public ICmdHandler // обработка поступающих eth-команд
   , public IEthNotifyHandler // обработка поступающих eth-уведомлений
{
public:
    APTeleKeeper(const Settings &_settings);
    void set_log_mode(TeleKeeperLogMode _mode);
    bool setup();
    bool check_valid();
    void get(ChainDroneTelemetryAP &_tele, bool &is_valid);
    bool quit();
private:
    APTeleKeeper() = delete;
    void handleEthCmdDistributionGeneral(std::shared_ptr<eth_cmd_processing::EthCmdBase> _receive_cmd); // общий маршрутизатор приходящего потока команд по конкретным обработчикам
    void handleEthCmdChainDroneAPTelemetry(std::shared_ptr<eth_cmd_processing::EthCmdBase> _receive_cmd);
    std::shared_ptr<eth_cmd_processing::CmdHandlersDistributor> eth_cmd_distributor = nullptr;

    TeleKeeperLogMode log_mode = LOG_MODE_OFF;
    syst_time_extract::DateTime sys_datetime;
    int float_prec = 5;

    Settings settings;
    std::shared_ptr<eth_controller::cmd::async::udp::AsyncUDPEthControllerCmd> udp_controller = nullptr;
    struct Sync
    {
        std::mutex tele_mtx;
        std::atomic<bool> quit_was_call = {false};
        std::atomic<bool> success_quit = {false};
    } sync;

    std::chrono::system_clock::time_point   tp_last_cmd, // временная метка последнего поступившего пакета телеметрии
                                            tp_tmp; 
    int64_t delay_enter_cmd_ms;

    ChainDroneTelemetryAP tele_data;
}; // -- class APTeleKeeper

} // -- namespace chain_drone_ap_tele_keeper

#endif // ETH_AP_TELE
