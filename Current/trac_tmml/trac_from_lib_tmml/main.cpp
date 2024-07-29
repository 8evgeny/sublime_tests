#include "application.hpp"



using namespace std;
using namespace cv;

function<void(int)> quit_handler;
void systemSignalsHandler(int signal) { quit_handler(signal);} // оболочка над лямбда-выражением

int main(int argc, char *argv[])
{
    cout << "BEGIN main" << endl;

//    string path2ini = "../tracking.ini";

//    vector<Rect2f> v_rct(5, Rect2f(0,1.f,2.f,3.f));
//    track_pos_sender::vtrackDataStruct data2send;
//    int counter = 0;
//    cout << "\ndata2send vector size = " << data2send.size << endl;
//    for(int i = 0; i < data2send.v_track.size(); i++)
//    {
//        cout << "[" << i << "]: " <<
//                data2send.v_track[i].x << " " <<
//                data2send.v_track[i].y << " " <<
//                data2send.v_track[i].w << " " <<
//                data2send.v_track[i].h << " | " <<
//                sizeof(data2send.v_track[i])
//             << endl;
//    } // END for(int i = 0; i < data2send.v_track.size(); i++)

//    while(true)
//    {
//        for(int i = 0; i < data2send.size ;i++)
//        {
//            data2send.v_track[i] = track_pos_sender::trackPos{v_rct[i].x + (float)counter, v_rct[i].y, v_rct[i].width, v_rct[i].height};
//            cout << "[" << counter << "]data2send[" << i << "]: "
//                 << data2send.v_track[i].x << "|" <<
//                    sizeof(data2send.v_track[i].x) << " " <<
//                    data2send.v_track[i].y << "|" <<
//                    sizeof(data2send.v_track[i].y) << " " <<
//                    data2send.v_track[i].w << "|" <<
//                    sizeof(data2send.v_track[i].w) << " " <<
//                    data2send.v_track[i].h << "|" <<
//                    sizeof(data2send.v_track[i].h) << " " <<
//                    "size = " << sizeof(data2send.v_track[i])
//                 << endl;
//        } // END for(i = 0..data2send.size()
//        cout << "Size data2send = " << sizeof(data2send) << " = v_track" << sizeof(data2send.v_track) << "(" << data2send.v_track.size() << ") + size" << sizeof(data2send.size) << endl;;

//        sender_ptr->send(data2send);
//        cout << endl;
//        counter++;
//        this_thread::sleep_for(milliseconds(1000));
//    } // END while(true)

//    cout << "dbg::end main" << endl;
//    return 0;
    /*
    Важно сначала назначить nullptr,
    т.к. если сигнал пройдет раньше,
    чем загрузится app, нужно обеспечить
    корректное поведение. В обработчике quit_handler стоит проверка на nullptr.
    */
    unique_ptr<Application> app = nullptr;
    quit_handler = [&app](int sig)
    {
        cout << "Call quit_handler" << endl;
        signal(sig, SIG_DFL);
        if(app != nullptr)
        {
            app->quit();
            app.release();
        }
    }; // -- quit_handler

    string config_path = "../tracking.ini"; // -- Путь к файлу конфигурации.
    // cout << argc << "\t" << argv[1] << endl;
    if(argc == 2)
    {
        config_path = argv[1];
    } // -- END if(argc != 2)
    cout << "config_path = "  << config_path << endl;
    time_keeper::TimeKeeper::inst();

    // Install a signal handler
    signal(SIGINT,  systemSignalsHandler);
    signal(SIGABRT, systemSignalsHandler);
    signal(SIGTERM, systemSignalsHandler);
    signal(SIGKILL, systemSignalsHandler);
    signal(SIGQUIT, systemSignalsHandler);
    signal(SIGSTOP, systemSignalsHandler);
    
    bool ok = 0;
    cout << "Create app" << endl;
    app = make_unique<Application>(config_path, ok);
    if(ok)
    {
        app->start();
    } // -- END if(ok)
    else
    {
        cout << "Application create failed..." << endl;
    }
    cout << "quit app->start()" << endl;
    this_thread::sleep_for(chrono::milliseconds(50));

    app.reset();
    cout << "End main" << endl;
    return 0;
} // -- END main
