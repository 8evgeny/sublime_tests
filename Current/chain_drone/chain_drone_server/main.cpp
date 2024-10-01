#include "application.hpp"


std::function<void(int)> quit_handler;
void systemSignalsHandler(int signal) { quit_handler(signal);} // оболочка над лямбда-выражением

int main(int argc, char *argv[])
{
    std::cout << "BEGIN main" << std::endl;
    /*
    Важно сначала назначить nullptr,
    т.к. если сигнал пройдет раньше, 
    чем загрузится app, нужно обеспечить
    корректное поведение. В обработчике quit_handler стоит проверка на nullptr. 
    */
    std::unique_ptr<Application> app = nullptr;
    quit_handler = [&app](int sig)
    {
        std::cout << "Call quit_handler" << std::endl;
        signal(sig, SIG_DFL);
        if(app != nullptr)
        {
            cout << "call quit (app was created))!" << endl;
            app->stop();
            return;
        } // -- END if(app != nullptr)
        else
        {
            cout << "cant quit! (app = nullptr)..." << endl;
            app->stop();
            return;
        }
    }; // -- quit_handler

    std::string config_path = "../chain_drone_server.ini"; // -- Путь к файлу конфигурации.
    // std::cout << argc << "\t" << argv[1] << std::endl;
    if(argc == 2)
    {
        config_path = argv[1];
    } // -- END if(argc != 2)
    std::cout << "config_path = "  << config_path << std::endl;
    time_keeper::TimeKeeper::inst();

    // Install a signal handler
    signal(SIGINT,  systemSignalsHandler);
    signal(SIGABRT, systemSignalsHandler);
    signal(SIGTERM, systemSignalsHandler);
    signal(SIGKILL, systemSignalsHandler);
    signal(SIGQUIT, systemSignalsHandler);
    signal(SIGSTOP, systemSignalsHandler);
    
    bool ok = 0;
    std::cout << "Create app" << std::endl;
    app = std::make_unique<Application>(config_path, ok);
    if(ok)
    {
       app->start();
    } // -- END if(ok)
    else
    {
        std::cout << "Application create failed..." << std::endl;
    } // END else

//    app.reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    app.release();
    app.reset();
    std::cout << "End main" << std::endl;
    return 0;
} // -- END main
