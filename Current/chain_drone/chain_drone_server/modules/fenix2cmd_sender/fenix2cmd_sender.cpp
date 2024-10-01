#include "fenix2cmd_sender.hpp"

Fenix2CmdSender::Fenix2CmdSender(const fenix2cmd_sender::Settings &_settings) : settings(_settings)
{

} // -- Fenix2CmdSender

Fenix2CmdSender::~Fenix2CmdSender()
{
    quit();
} // -- ~Fenix2CmdSender()

bool Fenix2CmdSender::start()
{
    if(sync.start_wac_call.load())
    {
        return sync.start_success.load();
    }
    sync.start_wac_call.store(true);
    
    eth_controller::cmd::async::udp::AsyncUDPEthControllerCmd
    eth_controller::cmd::async::tcp::

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
                    ETH_CMD_FENIX2_CMD_DATA, settings.cmd_net_id);
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
    std::thread exec_thr(&Fenix2CmdSender::exec, this);
    exec_thr.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(5)); // for create thread
    return true;
} // -- END start

void Fenix2CmdSender::exec()
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
        fenix2cmd_cmd = std::make_shared<eth_cmd_processing::EthCmdFenix2CmdData>();
        sync.fenix2cmd_data_mtx.lock();
        fenix2cmd_cmd->set(fenix2cmd_data);
        sync.fenix2cmd_data_mtx.unlock();

        //        std::cout << std::endl << "_________________" << std::endl;
        //        std::cout << "quit_server       = " << fenix2cmd_data.quit_server << std::endl;
        //        std::cout << "track_size_up     = " << fenix2cmd_data.track_size_up << std::endl;
        //        std::cout << "track_size_down   = " << fenix2cmd_data.track_size_down << std::endl;
        //        std::cout << "init_track        = " << fenix2cmd_data.init_track << std::endl;
        //        std::cout << "track_init_posx   = " << fenix2cmd_data.track_init_posx << std::endl;
        //        std::cout << "track_init_posy   = " << fenix2cmd_data.track_init_posy << std::endl;
        //        std::cout << "deinit_track      = " << fenix2cmd_data.deinit_track << std::endl;
        //        std::cout << "poweroff_srv      = " << fenix2cmd_data.poweroff_srv << std::endl;

        if (fenix2cmd_data != fenix2cmd_empty)
        {
            udp_controller->send_cmd(fenix2cmd_cmd);
            fenix2cmd_data = fenix2cmd_empty;
        }
        std::this_thread::sleep_until(tp_dst);
    } //while(sync.execute.load())
    sync.exec_complete.store(true);
    std::cout << "NOTE: Fenix2CmdSender::exec() complete" << std::endl;
} // -- END exec

void Fenix2CmdSender::set(Fenix2Cmd &_fenix2cmd)
{
    sync.fenix2cmd_data_mtx.lock();
    fenix2cmd_data = _fenix2cmd;
    _fenix2cmd = {0,0,0,0,0,0,0,0};
    sync.fenix2cmd_data_mtx.unlock();
} // -- END set

bool Fenix2CmdSender::quit()
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
