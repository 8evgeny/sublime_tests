#include "fenix2meta_keeper.hpp"

#include <iomanip>

namespace fenix2meta_keeper
{

Fenix2MetaKeeper::Fenix2MetaKeeper(const Settings &_settings) : settings(_settings)
{

} // -- END constructor

void Fenix2MetaKeeper::set_log_mode(TeleKeeperLogMode _status)
{
    sync.tele_mtx.lock();
    log_mode = _status;
    sync.tele_mtx.unlock();
} // -- END set_log_status

bool Fenix2MetaKeeper::setup()
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
    controller_minor_settings.cmd_manager_server.pass_decode_cmd_type   = ETH_CMD_FENIX2_METADATA;

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
        ETH_CMD_FENIX2_METADATA,
        std::bind(&Fenix2MetaKeeper::handleEthCmdFenix2MetaData, this, std::placeholders::_1));
    register_cmd_handler(std::bind(&Fenix2MetaKeeper::handleEthCmdDistributionGeneral, this, std::placeholders::_1));
    udp_controller->register_cmd_handler(this);
    // udp_controller->register_notify_handler(this);

    tp_last_cmd = std::chrono::high_resolution_clock::now() - 2 * std::chrono::milliseconds(settings.max_delay_btw_packs_ms);
    return true;
} // -- END setup

bool Fenix2MetaKeeper::check_valid()
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

void Fenix2MetaKeeper::get(Fenix2Meta &_tele, bool &is_valid)
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
    _tele.tp_keep = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();; //dbg::

    sync.tele_mtx.unlock();
} // -- END get

bool Fenix2MetaKeeper::quit()
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
        std::cout << "ERROR: mutex is lock when quit from Fenix2MetaKeeper" << std::endl;
    }
    sync.tele_mtx.unlock();

    return true;
} // -- END quit

void Fenix2MetaKeeper::handleEthCmdDistributionGeneral(std::shared_ptr<eth_cmd_processing::EthCmdBase> receive_cmd)
{
    eth_cmd_distributor->apply(receive_cmd);
} // -- END distribute gen

void Fenix2MetaKeeper::handleEthCmdFenix2MetaData(std::shared_ptr<eth_cmd_processing::EthCmdBase> _receive_cmd)
{
    std::shared_ptr<eth_cmd_processing::EthCmdFenix2MetaData> cmd =
        std::dynamic_pointer_cast<eth_cmd_processing::EthCmdFenix2MetaData>(_receive_cmd);
    // std::cout << "DBG:: Fenix2MetaKeeper -- receive telemetry package" << std::endl;
    
    sync.tele_mtx.lock();
    cmd->get(tele_data);
    static std::chrono::system_clock::time_point tp_cur;
    tp_cur = std::chrono::system_clock::now();
    if(log_mode == LOG_MODE_ON_ORIENT_ONLY)
    {
        std::cout << "LOG: [Fenix2MetaKeeper] receive telemetry package:" << std::endl;
        sys_datetime = syst_time_extract::getCurrentDateTime();
        int dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp_cur - tp_last_cmd).count();
        std::cout << "sys_time = " << std::setw(25) << std::left << sys_datetime.to_str() << "; dt_ms = " << dt_ms << std::endl;
        int alias_base_len = 8;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "track_is_init"   << "= " << std::fixed << std::setprecision(float_prec) << tele_data.track_is_init << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "trackx"  << "= " << std::fixed << std::setprecision(float_prec) << tele_data.trackx << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "tracky"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.tracky << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "new_trackw"  << "= " << std::fixed << std::setprecision(float_prec) << tele_data.new_trackw << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "new_trackh"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.new_trackh << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "trackw"  << "= " << std::fixed << std::setprecision(float_prec) << tele_data.trackw << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "trackh"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.trackh << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "diff_trackx"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.diff_trackx << std::endl;
        std::cout << "\t" << std::setw(alias_base_len) << std::left << "diff_tracky"    << "= " << std::fixed << std::setprecision(float_prec) << tele_data.diff_tracky << std::endl;
        std::cout << std::endl << std::endl;



    }
    tp_last_cmd = tp_cur;
    sync.tele_mtx.unlock();

} // -- END handle Fenix2Meta_cmd

} // -- namespace fenix2meta_keeper
