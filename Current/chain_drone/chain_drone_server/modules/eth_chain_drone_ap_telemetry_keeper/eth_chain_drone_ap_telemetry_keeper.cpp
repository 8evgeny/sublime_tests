#include "eth_chain_drone_ap_telemetry_keeper.hpp"

#include <iomanip>

namespace chain_drone_ap_tele_keeper
{

APTeleKeeper::APTeleKeeper(const Settings &_settings) : settings(_settings)
{

} // -- END constructor

void APTeleKeeper::set_log_mode(TeleKeeperLogMode _status)
{
    sync.tele_mtx.lock();
    log_mode = _status;
    sync.tele_mtx.unlock();
} // -- END set_log_status

bool APTeleKeeper::setup()
{
    eth_cmd_distributor = std::make_shared<eth_cmd_processing::CmdHandlersDistributor>();
    if(eth_cmd_distributor == nullptr)
    {
        std::cout << "ERROR: create eth_cmd_distributor failed" << std::endl;
        return false;
    }

    udp_controller = eth_controller::cmd::async::udp::create(settings.path2ini, settings.section_name);
    if(udp_controller == nullptr)
    { 
        std::cout << "ERROR: create udp_controller failed" << std::endl;
        return false;
    }

    eth_controller::cmd::async::udp::MinorSettings controller_minor_settings;
    controller_minor_settings.cmd_manager_server.checksum_codec_type    = CHECKSUM_CODEC_PASS;
    controller_minor_settings.cmd_manager_server.cmd_id_codec_type      = CMD_ID_CODEC_PASS;
    controller_minor_settings.cmd_manager_server.pass_decode_cmd_type   = ETH_CMD_AP_TELEMETRY;

    if(!udp_controller->set_minor_settings(controller_minor_settings))
    {
        std::cout << "ERROR: udp_controller->set_minor_settings" << std::endl;
        return false;
    }

    if(!udp_controller->launch())
    {
        std::cout << "ERROR: launch udp_controller failed" << std::endl;
        return false;
    }

    eth_cmd_distributor->register_cmd_handler(
        ETH_CMD_AP_TELEMETRY,
        std::bind(&APTeleKeeper::handleEthCmdChainDroneAPTelemetry, this, std::placeholders::_1));
    register_cmd_handler(std::bind(&APTeleKeeper::handleEthCmdDistributionGeneral, this, std::placeholders::_1));
    udp_controller->register_cmd_handler(this);
    // udp_controller->register_notify_handler(this);

    tp_last_cmd = std::chrono::high_resolution_clock::now() - 2 * std::chrono::milliseconds(settings.max_delay_btw_packs_ms);
    return true;
} // -- END setup

bool APTeleKeeper::check_valid()
{
    sync.tele_mtx.lock();
    bool is_valid = false;
    tp_tmp = std::chrono::high_resolution_clock::now();
    delay_enter_cmd_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_tmp - tp_last_cmd).count();
    if(delay_enter_cmd_ms < settings.max_delay_btw_packs_ms)
    {
        is_valid = true;
    }
    else
    {
        is_valid = false;
    }
    sync.tele_mtx.unlock();
    return is_valid;
} // -- END check_valid

void APTeleKeeper::get(ChainDroneTelemetryAP &_tele, bool &is_valid)
{
    sync.tele_mtx.lock();
    tp_tmp = std::chrono::high_resolution_clock::now();
    delay_enter_cmd_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_tmp - tp_last_cmd).count();
    if(delay_enter_cmd_ms < settings.max_delay_btw_packs_ms)
    {
        is_valid = true;
    }
    else
    {
        is_valid = false;
    }
    _tele = tele_data;
    sync.tele_mtx.unlock();
} // -- END get

bool APTeleKeeper::quit()
{
    if(sync.quit_was_call.load())
    {
        return false;
    }
    sync.quit_was_call.store(true);

    if(!udp_controller->quit())
    {
        std::cout << "ERROR: udp_controller quit failed" << std::endl;
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if(!sync.tele_mtx.try_lock())
    {
        std::cout << "ERROR: mutex is lock when quit from APTeleKeeper" << std::endl;
    }
    sync.tele_mtx.unlock();

    return true;
} // -- END quit

void APTeleKeeper::handleEthCmdDistributionGeneral(std::shared_ptr<eth_cmd_processing::EthCmdBase> receive_cmd)
{
    eth_cmd_distributor->apply(receive_cmd);
} // -- END distribute gen

void APTeleKeeper::handleEthCmdChainDroneAPTelemetry(std::shared_ptr<eth_cmd_processing::EthCmdBase> _receive_cmd)
{
    std::shared_ptr<eth_cmd_processing::EthCmdAPChainDroneTelemetry> cmd =
        std::dynamic_pointer_cast<eth_cmd_processing::EthCmdAPChainDroneTelemetry>(_receive_cmd);
    // std::cout << "DBG:: APTeleKeeper -- receive telemetry package" << std::endl;
    
    sync.tele_mtx.lock();
    cmd->get(tele_data);
    static std::chrono::system_clock::time_point tp_cur;
    tp_cur = std::chrono::system_clock::now();
    if(log_mode == LOG_MODE_ON_ORIENT_ONLY)
    {
        std::cout << "LOG: [APTeleKeeper] receive telemetry package:" << std::endl;
        sys_datetime = syst_time_extract::getCurrentDateTime();
        int dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_cur - tp_last_cmd).count();
        std::cout << "sys_time = " << std::setw(25) << std::left << sys_datetime.to_str() << "; dt_ms = " << dt_ms << std::endl;
        int alias_base_len = 8;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "roll"   << "= " << std::fixed << std::setprecision(float_prec) << tele_data.roll_rad << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "pitch"  << "= " << std::fixed << std::setprecision(float_prec) << tele_data.pitch_rad << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "yaw"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.yaw_rad << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "alt"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.altitude_m << std::endl;
        std::cout << std::endl << std::endl;
    }
    tp_last_cmd = tp_cur;
    sync.tele_mtx.unlock();

} // -- END handle APTelemetryCmd

} // -- namespace chain_drone_ap_tele_keeper
