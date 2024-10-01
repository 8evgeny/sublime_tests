#include "chain_drone_client.hpp"
#include "X11/Xlib.h"
#include "X11/Xutil.h"

std::function<void(int)> quit_handler;
void systemSignalsHandler(int signal) { quit_handler(signal);} // оболочка над лямбда-выражением


int main(int argc, char *argv[])
{


    std::string config_path = "../chain_drone_client.ini";
    if(argc == 2)
    {
        std::cout << argc << "\t" << argv[1] << std::endl;
        config_path = argv[1];
    } // -- END if(argc != 2)

    /*
    Важно сначала назначить nullptr,
    т.к. если сигнал пройдет раньше,
    чем загрузится app, нужно обеспечить
    корректное поведение. В обработчике quit_handler стоит проверка на nullptr.
    */
    std::unique_ptr<chain_drone_cli::EthKeeper> app = nullptr;
    quit_handler = [&app](int sig)
    {
        signal(sig, SIG_DFL);
        if(app != nullptr)
        {
            app->quit();
            app.reset();
            system("kill -9 $pid ;");
        }
    }; // -- quit_handler

    // Install a signal handler
    signal(SIGINT,  systemSignalsHandler);
    signal(SIGABRT, systemSignalsHandler);
    signal(SIGTERM, systemSignalsHandler);
    signal(SIGKILL, systemSignalsHandler);
    signal(SIGQUIT, systemSignalsHandler);
    signal(SIGSTOP, systemSignalsHandler);


    /// Создали и настроили класс отправитель метаданных (условный сервер)
    bool ok = 0;
    std::shared_ptr<chain_drone_cli::EthKeeper> eth_keeper_ptr = nullptr;
    eth_keeper_ptr = std::make_shared<chain_drone_cli::EthKeeper>(config_path, ok);
    if (!ok)
    {
        std::cout << "ERROR: can't init EthKeeper!\nEND main!" << std::endl;
        return 0;
    } // END !ok eth_keeper_ptr
    eth_keeper_ptr->work();
    std::cout << "END main" << std::endl;
    return 1;
} // END int main()
