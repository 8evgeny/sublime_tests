#ifndef TCP_CLIENT_SETUP_INFO_HPP
#define TCP_CLIENT_SETUP_INFO_HPP

#include "setup_info_struct.hpp"
#include "command_processing/commands_zoo/eth_cmd_base.hpp"
#include "notification_handler/iethnotifyhandler.hpp"
#include <mutex>
#include <atomic>
#include <queue>
#include <memory>

namespace eth_controller::cmd::async::client_simplex
{
    struct Settings
    {
        //net
        std::string node_alias;
        std::string src_ip_v4;
        int src_port;
        
        // spec
        int single_command_buf_size_byte = 1024; // буфер под одну сериализованную команду
        int cmd_tx_loop_delay_ms; // задержка между отправками команд TODO: сделать опцию адаптивной подстройки времени отправки, которая регулирует заполненность буфера
    }; // -- END Settings

    class TcpClientSetupInfo
    {
        public:
            TcpClientSetupInfo(Settings _settings);
            ~TcpClientSetupInfo();
            bool setup(Fenix2SetupInfo & setup_info); // первичная конфигурация и настройка соединения сокет-сокет
            bool exec(); // запуск loop регулярной отправки команд
            bool quit(); // корректное завершение работы
            bool close_socket(bool force = false); // закрывает рабочий сокет, если успешно был выполнен выход из exec() (проверяется по внутренним флагам)
            bool send_cmd(std::shared_ptr<eth_cmd_processing::EthCmdBase> cmd);
            bool is_connect_established(); // возвращает true, если соединение сокет-сокет успешно установлено
            bool is_success_quit(); // возвращает true, если выход произведен успешно
            bool is_error_connect(); // возвращает true, если возникла ошибка во время соединения
            void register_notify_handler(IEthNotifyHandler *handler); // регистрация подписчика на события, инициируемые настоящим классом
        private:
            int sockfd;
            int connfd;
            Settings settings;
            std::queue<std::shared_ptr<eth_cmd_processing::EthCmdBase>> cmd_snd_buf; // командный буфер на отправку
            uint8_t* cmd_bytebuffer;
            struct Sync
            {
                std::atomic<bool> success_setup = {false};
                std::atomic<bool> execute_tx = {false};
                std::atomic<bool> success_quit = {false};
                std::mutex cmd_snd_buf_mtx;
            } sync;
            std::vector<IEthNotifyHandler *> notify_handlers;
    }; // -- end class TcpClientSetupInfo
} // -- namespace eth_controller::cmd::async::client_simplex
 

#endif //TCP_CLIENT_SETUP_INFO_HPP
