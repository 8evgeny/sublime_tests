#include "track_meta_pos_sender.hpp"
#include <iostream>
#include <chrono>
#include <thread>

TrackMetaPosSender::TrackMetaPosSender(const track_meta_sender::Settings &_settings) : settings(_settings)
{

} // -- TrackMetaPosSender

TrackMetaPosSender::~TrackMetaPosSender()
{
    quit();
} // -- ~TrackMetaPosSender()

bool TrackMetaPosSender::start()
{
    if(sync.start_wac_call.load())
    {
        return sync.start_success.load();
    }
    sync.start_wac_call.store(true);
    
    udp_controller = eth_controller::cmd::async::udp::create(settings.path2ini, settings.section);
    if(udp_controller == nullptr)
    {
        std::cout << "ERROR: create udp controller failed" << std::endl;
        return false;
    }

    auto mn_st = udp_controller->get_minor_settings();
    
    mn_st.cmd_manager_client.checksum_codec_type        = CHECKSUM_CODEC_XOR;   
    if(settings.use_cmd_net_id)
    {
        mn_st.cmd_manager_client.cmd_id_codec_type      = CMD_ID_CODEC_SIMPLE_DIRECT_ENC;
        mn_st.cmd_manager_client.tir_host2net.set(
            ETH_CMD_TRACKER_METADATA_POS, settings.cmd_net_id);
    }
    else
    {
        mn_st.cmd_manager_client.cmd_id_codec_type      = CMD_ID_CODEC_PASS;
    }
    
    if(!udp_controller->set_minor_settings(mn_st))
    {
        std::cout << "ERROR: udp_controller->get_minor_settings() failed" << std::endl;
        return false;
    }

    if(!udp_controller->launch())
    {
        std::cout << "ERROR: udp_controller->launch() failed" << std::endl;
        return false;
    }

    sync.execute.store(true);    
    std::thread exec_thr(&TrackMetaPosSender::exec, this);
    exec_thr.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(5)); // for create thread
    return true;
} // -- END start

void TrackMetaPosSender::exec()
{
    if(!sync.execute.load())
    {
        std::cout << "ERROR: exec not launched" << std::endl;
        return;
    }
    std::chrono::system_clock::time_point tp_dst;
    long send_delay_us = 1e6 / settings.fps_stream;
    std::chrono::microseconds send_delay(send_delay_us);
    while(sync.execute.load())
    {
        tp_dst = std::chrono::system_clock::now() + send_delay;

        trackmeta_cmd = std::make_shared<eth_cmd_processing::EthCmdTrackerMetaDataPos>();

        sync.trackmeta_data_mtx.lock();
        trackmeta_cmd->set(trackmeta_pos);
        sync.trackmeta_data_mtx.unlock();

        udp_controller->send_cmd(trackmeta_cmd);

        std::this_thread::sleep_until(tp_dst);
    }
    sync.exec_complete.store(true);
    std::cout << "NOTE: TrackMetaPosSender::exec() complete" << std::endl;
} // -- END exec

void TrackMetaPosSender::set(TrackMeta2AP_pos &_trackmeta_pos)
{
    sync.trackmeta_data_mtx.lock();
    trackmeta_pos = _trackmeta_pos;
    sync.trackmeta_data_mtx.unlock();
} // -- END set

bool TrackMetaPosSender::quit()
{
    if(sync.quit_was_call.load())
    {
        return sync.quit_success.load();
    }
    sync.quit_was_call.store(true);

    sync.execute.store(false);
    while(!sync.exec_complete.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    if(!udp_controller->quit())
    {
        std::cout << "ERROR: udp_controller->quit() failed" << std::endl;
        return false;
    }
    return true;
} // -- END quit
