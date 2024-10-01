#ifndef TRACK_META_SENDER_HPP
#define TRACK_META_SENDER_HPP

#include <cstdint>
#include <mutex>
#include <atomic>
#include <memory>
#include <string>

#include TRACKER_METADATA_POS_INTERFACE_PATH
#include "udp_modules/async_udp_eth_controller_cmd/async_udp_eth_controller_cmd_factory.hpp"
#include "command_processing/commands_zoo/track_meta_pos/track_meta_pos_eth_cmd.hpp"


namespace track_meta_sender
{
    struct Settings
    {
        int fps_stream = 25; // Частота регулярной отправки

        bool use_cmd_net_id = true;
        int cmd_net_id = 0; // сетевой идентификатор отправляемой команды (подменный)
        
        std::string path2ini;
        std::string section;
    }; // -- Settings

} // -- namespace track_meta_sender

class TrackMetaPosSender
{
public:
    TrackMetaPosSender(const track_meta_sender::Settings &_settings);
    ~TrackMetaPosSender();
    bool start();
    void set(TrackMeta2AP_pos &_trackmeta_pos);
    bool quit();
private:
    TrackMetaPosSender() = delete;
    void exec();
    std::shared_ptr<eth_controller::cmd::async::udp::AsyncUDPEthControllerCmd> udp_controller;
    track_meta_sender::Settings settings;
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

        std::mutex trackmeta_data_mtx;
    } sync;

    TrackMeta2AP_pos trackmeta_pos;
    std::shared_ptr<eth_cmd_processing::EthCmdTrackerMetaDataPos> trackmeta_cmd = nullptr;
}; // -- class TrackMetaPosSender

#endif //TRACK_META_SENDER_HPP
