#ifndef FENIX2CMD_SENDER_HPP
#define FENIX2CMD_SENDER_HPP

#include <cstdint>
#include <mutex>
#include <atomic>
#include <memory>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>


#include "../fenix2cmd/fenix2cmd_struct.hpp"

#include "udp_modules/async_udp_eth_controller_cmd/async_udp_eth_controller_cmd_factory.hpp"
#include "command_processing/commands_zoo/fenix2cmd/fenix2cmd_eth_cmd.hpp"
namespace fenix2cmd_sender
{
    struct Settings
    {
        int fps_stream = 25; // Частота регулярной отправки

        bool use_cmd_net_id = true;
        int cmd_net_id = 0; // сетевой идентификатор отправляемой команды (подменный)
        
        std::string path2ini = "";
        std::string section = "fenix2cmd_sender";
    }; // -- Settings

} // -- namespace fenix2cmd_sender

class Fenix2CmdSender
{
public:
    Fenix2CmdSender(const fenix2cmd_sender::Settings &_settings);
    ~Fenix2CmdSender();
    bool start();
    void set(Fenix2Cmd & _fenix2cmd);
    bool quit();
private:
    Fenix2CmdSender() = delete;
    void exec();
    std::shared_ptr<eth_controller::cmd::async::udp::AsyncUDPEthControllerCmd> udp_controller;
    fenix2cmd_sender::Settings settings;
    struct Sync
    {

        std::atomic<bool> start_wac_call    = {false};
        std::atomic<bool> start_success     = {false};
        std::atomic<bool> start_failed      = {false};

        std::atomic<bool> execute           = {false};
        std::atomic<bool> exec_complete     = {false};
        
        std::atomic<bool> quit_was_call     = {false};
        std::atomic<bool> quit_success      = {false};
        std::atomic<bool> quit_failed       = {false};

        std::mutex fenix2cmd_data_mtx;
    } sync;

    Fenix2Cmd fenix2cmd_data;
    const Fenix2Cmd fenix2cmd_empty = {0,0,0,0,0,0,0,0};
    std::shared_ptr<eth_cmd_processing::EthCmdFenix2CmdData> fenix2cmd_cmd = nullptr;
}; // -- class Fenix2CmdSender

#endif //fenix2cmd_sender_HPP
