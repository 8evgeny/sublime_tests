#ifndef FENIX2META_SENDER_HPP
#define FENIX2META_SENDER_HPP

#include <cstdint>
#include <mutex>
#include <atomic>
#include <memory>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>


#include "../fenix2meta/fenix2meta_struct.hpp"
#include "eth_controller_toolbox/udp_modules/async_udp_eth_controller_cmd/async_udp_eth_controller_cmd_factory.hpp"
#include "eth_controller_toolbox/command_processing/commands_zoo/fenix2meta/fenix2_eth_cmd.hpp"
namespace fenix2meta_sender
{
    struct Settings
    {
        int fps_stream = 25; // Частота регулярной отправки

        bool use_cmd_net_id = true;
        int cmd_net_id = 0; // сетевой идентификатор отправляемой команды (подменный)
        
        std::string path2ini = "";
        std::string section = "fenix2meta_sender";
    }; // -- Settings

} // -- namespace fenix2meta_sender

class Fenix2MetaSender
{
public:
    Fenix2MetaSender(const fenix2meta_sender::Settings &_settings);
    ~Fenix2MetaSender();
    bool start();
    void set(Fenix2Meta & _fenix2meta);
    bool quit();
private:
    Fenix2MetaSender() = delete;
    void exec();
    std::shared_ptr<eth_controller::cmd::async::udp::AsyncUDPEthControllerCmd> udp_controller;
    fenix2meta_sender::Settings settings;
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

        std::mutex fenix2meta_data_mtx;
    } sync;

    Fenix2Meta fenix2meta_data;
    std::shared_ptr<eth_cmd_processing::EthCmdFenix2MetaData> fenix2meta_cmd = nullptr;
}; // -- class Fenix2MetaSender

#endif //fenix2meta_sender_HPP
