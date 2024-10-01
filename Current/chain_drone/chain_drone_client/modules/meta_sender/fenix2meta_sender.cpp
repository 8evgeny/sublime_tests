#include "fenix2meta_sender.hpp"

Fenix2MetaSender::Fenix2MetaSender(const fenix2meta_sender::Settings &_settings) : settings(_settings)
{

} // -- Fenix2MetaSender

Fenix2MetaSender::~Fenix2MetaSender()
{
    quit();
} // -- ~Fenix2MetaSender()

bool Fenix2MetaSender::start()
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
            ETH_CMD_FENIX2_METADATA, settings.cmd_net_id);
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
    std::thread exec_thr(&Fenix2MetaSender::exec, this);
    exec_thr.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(5)); // for create thread
    return true;
} // -- END start

void Fenix2MetaSender::exec()
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
        fenix2meta_cmd = std::make_shared<eth_cmd_processing::EthCmdFenix2MetaData>();
        sync.fenix2meta_data_mtx.lock();
        fenix2meta_cmd->set(fenix2meta_data);
        sync.fenix2meta_data_mtx.unlock();

        std::cout << std::endl << "_________________" << std::endl;
        std::cout << "track_is_init  = " << fenix2meta_data.track_is_init << std::endl;
        std::cout << "diff_trackx    = " << fenix2meta_data.diff_trackx << std::endl;
        std::cout << "diff_tracky    = " << fenix2meta_data.diff_tracky << std::endl;
        std::cout << "trackx         = " << fenix2meta_data.trackx << std::endl;
        std::cout << "tracky         = " << fenix2meta_data.tracky << std::endl;
        std::cout << "tp_send        = " << fenix2meta_data.tp_send << std::endl;

        udp_controller->send_cmd(fenix2meta_cmd);
        std::this_thread::sleep_until(tp_dst);
    } //while(sync.execute.load())
    sync.exec_complete.store(true);
    std::cout << "NOTE: Fenix2MetaSender::exec() complete" << std::endl;
} // -- END exec

void Fenix2MetaSender::set(Fenix2Meta &_fenix2meta)
{
    sync.fenix2meta_data_mtx.lock();
    fenix2meta_data = _fenix2meta;
    sync.fenix2meta_data_mtx.unlock();
} // -- END set

bool Fenix2MetaSender::quit()
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
