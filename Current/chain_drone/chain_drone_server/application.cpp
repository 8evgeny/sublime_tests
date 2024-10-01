#include "application.hpp"
#ifdef USE_DBG
#include "opencv2/highgui.hpp"
#endif // USE_DBG
using namespace std;
using namespace cv;
using namespace std::chrono;

bool Application::click_down = 0;
bool Application::click_up = 0;
cv::Point2f Application::p_mouse(0, 0);
cv::Point2f Application::p_down(0, 0);

Application::~Application()
{
    std::cout << "Деструктор Application" << std::endl;
}

Application::Application(const std::string &pathToConfig,
                         bool &ok) : config_path(pathToConfig)
{
    cout << "config_path=" << config_path << endl;

    ok = get_ini_params(config_path);
    if(!ok){cout << "Not ok get_ini_params!" << endl; return;}

#ifdef USE_LOGGER
    bool create_logger_status;
    logger_artem::create(config_path, create_logger_status);
    if(!create_logger_status)
    {
        ok = false;
        quit();
        return;
    }
#endif //USE_LOGGER

    switch(device_id)
    {
#ifdef USE_FOLDER_READER
    case FOLDER:
        device = make_shared<FolderReader>(config_path, ok);
        if(!ok){cout << "Not ok FolderReader!" << endl; return;}
        break;
#endif
#ifdef USE_COLIBRI_TV
    case COLIBRITV:
        device = make_shared<ColibriTV>(config_path, ok);
        if(!ok){cout << "Not ok ColibriTV!" << endl; return;}
        device->setup();
        break;
#endif
#ifdef USE_VIDEO_READER
    case VIDEO:

        device = make_shared<VideoReader>(config_path, ok);
        if(!ok)
        {
            return;
        }
        break;
#endif
#ifdef USE_WEB_CAMERA
    case WEBCAMERA:
        device = make_shared<WebCamera>(config_path, ok);
        if(!ok){return;}
        break;
#endif
#ifdef USE_SHARED_MEMORY
    case SHARED_MEMORY:
        device = make_shared<SharedMemory>(config_path, ok);
        if(!ok){return;}
        device->setup();
        break;
#endif
#ifdef USE_RASPBERRY_HQ_CAMERA
    case RASPBERRY_HQ_CAMERA:
        device = devices::raspberry_hq_camera::create(config_path);
        device->setup();
        break;
#endif
#ifdef USE_IMX219_CAMERA_MIPI
    case IMX219_CAMERA_MIPI:
        device = devices::imx219_camera_mipi::create(config_path);
        device->setup();
        break;
#endif

#ifdef USE_IMX477_SQUARE_CAMERA_MIPI
    case IMX477_SQUARE_CAMERA_MIPI:
        device = devices::imx477_square_camera_mipi::create(config_path);
        device->setup();
        break;
#endif
#ifdef USE_HIKVISION
    case RTSP_H265:
        device = devices::rtsp_h265_device::create(config_path, "rtsp_h265_device");
        device->setup();
        break;
#endif // USE_HIKVISION


#ifdef USE_HVGS_GRAY_USB_CAMERA
    case HVGS_GRAY_USB_CAMERA:
    {
        device = devices::hvgs_gray_usb_camera::create(config_path, "GlobalShutterGrayUSBCamera");
        if(device != nullptr)
        {
            device->setup();
        } // END if(device != nullptr)
        else
        {
            ok = false;
            quit();
            return;
        } // END else
        break;
    } // END case HVGS_GRAY_USB_CAMERA:
#endif // USE_HVGS_GRAY_USB_CAMERA

    default:
        break;
    } // -- END switch

    if(device != nullptr)
    {
        if(!parallel && !(device_id == FOLDER || device_id == VIDEO))
        {
            parallel = true;
        } // END if(!parallel...

        if(parallel)
        {
            device->register_frame_handler(this);
            register_frame_handler(bind(&Application::handleDeviceFrame, this,
                                        placeholders::_1, placeholders::_2,
                                        placeholders::_3, placeholders::_4,
                                        placeholders::_5));
        } // -- END if(parallel)
    } // END if(device != nullptr)
    else
    {
#ifdef USE_LOGGER
        LoggerArtem::inst().log("Device doesn't exist: choose correct device in configuration file or rebuild application with current device");
#endif //USE_LOGGER
        quit();
    }

#ifdef USE_RECORDER
    if(use_recorder)
    {

        disk_monitor_ptr = std::make_shared<LvDiskMonitor>("/", check_memory_time, ok);
        if(!ok)
        {
            cout << "NOT ok disk_monitor_ptr initialization!" << endl;
            quit();
            return;
        } // if(!ok) disk_monitor_ptr


        if(adaptive_make_rec_dir)
        {
            if(!adaptive_dirs_setup())
            {
                ok = false;
                quit();
                return;
            } // END !adaptive_dirs_setup()
        } // END adaptive_make_rec_dir

        rec_settings.base.format                    = static_cast<recorder::ImageFormats>(recorder_format);
        rec_settings.base.dir_path                  = frames_record_dir;
        rec_settings.base.force_replace             = rec_force_replace;
        rec_settings.base.make_path                 = rec_make_path;
        rec_settings.base.png.compress_value        = png_compress_value;
        rec_settings.base.jpeg.quality              = jpeg_quality;
        rec_settings.watchdog.complete_all_threads.wait_total_time = watchdog_quit_ms;
        recorder_ptr = std::make_shared<recorder::RecorderSRST>(rec_settings);

        if(!recorder_ptr->setup())
        {
            cout << "NOT ok recotder setup!" << endl;
            quit();
            ok = false;
            return;
        } // END if(!recorder_ptr->setup())
    } // END if(use_recorder)
#endif // USE_RECORDER

#ifdef USE_ETH_CONTROLLER


    cout << " ------ BEGIN create fenix2frame_sender_ptr" << endl;
    settings_srv_ptr = std::make_shared<rtp::server::h264::Settings>();
    ok = rtp::server::h264::getIniSettings(config_path, rtp_server_section, *settings_srv_ptr);
    if (!ok)
    {
        cout << "ERROR: Application::rtp::server::getIniSettings!" << endl;
        return;
    } // END if (!ok)
    fenix2frame_sender_ptr = make_shared<rtp::RtpServerH264>(settings_srv_ptr);

    if (!fenix2frame_sender_ptr->setup())
    {
        cout << "Application::ERROR setup fenix2frame_sender_ptr!" << endl;
        ok = false;
        return;
    } // END if (!fenix2frame_sender_ptr->setup())

    if(!fenix2frame_sender_ptr->start())
    {
        cout << "Applicatin::ERROR start fenix2frame_sender_ptr!" << endl;
    } // END if(!fenix2frame_sender_ptr->start())
    cout << " ------ END create fenix2frame_sender_ptr" << endl;

#ifdef USE_ETH_MD
    keeper = chain_drone_ap_tele_keeper::create(config_path, section_ap_tel);
    if(keeper == nullptr)
    {
        std::cout << "ERROR: create keeper failed" << std::endl;
        quit();
        ok = false;
        return;
    } // END if(keeper == nullptr)
    keeper->set_log_mode(chain_drone_ap_tele_keeper::LOG_MODE_ON_ORIENT_ONLY);
    if(!keeper->setup())
    {
        std::cout << "ERROR setup keeper" << std::endl;
        quit();
        ok = false;
        return;
    } // END if(!keeper->setup())
#endif // USE_ETH_MD



    fenix2cmd_keeper_ptr = fenix2cmd_keeper::create(pathToConfig, "fenix2cmd_keeper");
    if(!fenix2cmd_keeper_ptr->setup())
    {
        cout << "Application::ERROR setup fenix2cmd_keeper_ptr!" << endl;
        ok = false;
        quit();
        return;
    } // END if(!trackmeta_sender->start())

#ifdef USE_TCP_SETUP
    cout << " ------ BEGIN create tcp_server_ptr" << endl;
    tcp_server_ptr = eth_controller::cmd::async::server_simplex::create(pathToConfig, section2tcp_cmd_sender);
#ifdef USE_CUDA
    setup_info_for_client.tracker_type = 1;
#else
    setup_info_for_client.tracker_type = 0;
#endif

    if (!tcp_server_ptr->setup(setup_info_for_client))
    {
        cout << "Application::ERROR setup tcp_server_ptr!" << endl;
        ok = false;
        quit();
        return;
    } // END if (!tcp_server_ptr->setup())
    cout << " ------ END create tcp_server_ptr" << endl;
#endif // USE_TCP_SETUP

    trackmeta_pos_sender_ptr = track_meta_sender::create(pathToConfig, section_trackmeta_sender);
    if(trackmeta_pos_sender_ptr == nullptr)
    {
        std::cout << "ERROR create trackmeta_pos_sender_ptr!" << std::endl;
        quit();
        ok = false;
        return;
    } // END if(trackmeta_sender == nullptr)
    ok = trackmeta_pos_sender_ptr->start();
    if(!ok)
    {
        std::cout << "ERROR start trackmeta_pos_sender_ptr!" << std::endl;
        quit();
        return;
    } // END if(!trackmeta_sender->start())
    cout << "Application::Application OK!" << endl;
#endif //USE_ETH_CONTROLLER



} // -- END Application

bool Application::FileIsExist(const string& filePath)
{
    bool isExist = false;
    std::ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist

bool Application::get_ini_params(const string &config)
{
    cout << "BEGIN get_ini_params Application" << endl;
    setlocale(LC_NUMERIC, "en_US.UTF-8");
#ifdef USE_FILESYSTEM
    bool configFileExists = std::filesystem::exists(config);
#else
    bool configFileExists = FileIsExist(config);
#endif
    if(!configFileExists)
    {
        cout << "Config file '" << config << "' not exist!" << endl;
        return 0;
    }
    INIReader reader(config);
    if(reader.ParseError() < 0)
    {
        cout << "Can't load '" << config << "'\n";
        return 0;
    }

    int temp_parallel = reader.GetInteger("main_settings", "parallel", -1);
    if(temp_parallel == -1)
    {
        cout << "parallel not declared!!" << endl;
        return 0;
    }
    else
    {
        parallel = static_cast<bool>(temp_parallel);
        cout << "parallel = " << parallel << ";\n";
    }

    gamma0 = reader.GetReal("main_settings", "gamma0", 1000000);
    if(gamma0 == 1000000) {cout << "gamma0 not declared!\n"; return 0;}
    else{cout << "gamma0 = " << gamma0 << ";\n";}
    gamma0 *= deg2rad;

    sign = reader.GetReal("main_settings", "sign", 1000000);
    if(sign == 1000000) {cout << "sign not declared!\n"; return 0;}
    else{cout << "sign = " << sign << ";\n";}


    device_id = reader.GetInteger("main_settings", "device_id", -1);
    if(device_id == -1)
    {
        cout << "device_id not declared!\n";
        return 0;
    }
    else
    {
        cout << "device_id = " << device_id << ";\n";
    }

    get_rect_manual = reader.GetInteger("main_settings", "get_rect_manual", -1);
    if(get_rect_manual == -1)
    {
        std::cout << "Not found get_rect_manual in Application::getMainSettings!\n";
        return false;
    }

    roi_mode = reader.GetInteger("main_settings", "roi_mode", -1);
    if(roi_mode == -1)
    {
        std::cout << "Not found roi_mode in Application::getMainSettings!\n";
        return false;
    }

    scale = reader.GetInteger("tracking", "scaling", -1);
    if(scale == -1)
    {
        std::cout << "Not found scaling in Application::getMainSettings!\n";
        return false;
    }
    if(scale == 1){clr_scaling = color::blue;}
    if(scale == 2){clr_scaling = color::red;}

    int frame_show_width_temp = reader.GetInteger("demonstration_settings", "width", -1);
    if(frame_show_width_temp == -1)
    {
        std::cout << "Not found width in Application::getMainSettings!\n";
        return false;
    }
    else
    {
        frame_show_width = frame_show_width_temp;
    }

    int demonstration_mode_temp = reader.GetInteger("demonstration_settings", "mode", -1);
    if(demonstration_mode_temp == -1)
    {
        std::cout << "Not found mode in Application::getMainSettings!\n";
        return false;
    }
    else
    {
        demonstration_mode = demonstration_mode_temp;
    }

    /// [callback] FENIX 2
    cout << "START [callback] section:\n";

    frame_send_w = reader.GetInteger(rtp_server_section, "video_width", -1);
    if(frame_send_w == -1) {cout << "Not found video_width in Application::get_ini_params::"<< rtp_server_section << "!\n"; return 0;}
    else {cout << "     video_width = " << frame_send_w << ";\n";}

    frame_send_h = reader.GetInteger(rtp_server_section, "video_height",  -1);
    if(frame_send_h == -1) {cout << "Not found video_height in Application::get_ini_params::"<< rtp_server_section << "!\n"; return 0;}
    else {cout << "     video_height = " << frame_send_h << ";\n";}

    string rct_increase_button_str = reader.Get("callback", "rct_increase_button", "oops");
    if(rct_increase_button_str == "oops") {cout << "Not found rct_increase_button in Application::get_ini_params()!\n"; return 0;}
    else {cout << "     rct_increase_button = " << rct_increase_button_str << ";\n";}
    rct_increase_button = rct_increase_button_str[0];

    string rct_decrease_button_str = reader.Get("callback", "rct_decrease_button", "oops");
    if(rct_decrease_button_str == "oops") {cout << "Not found rct_decrease_button in Application::get_ini_params()!\n"; return 0;}
    else {cout << "     rct_decrease_button = " << rct_decrease_button_str << ";\n";}
    rct_decrease_button = rct_decrease_button_str[0];

    rct_w_change_step = reader.GetInteger("callback", "rct_w_change_step", -1);
    if(rct_w_change_step == -1) {std::cout << "Not found rct_w_change_step in Application::get_ini_params()!\n"; return false;}
    else {cout << "     rct_w_change_step = " << rct_w_change_step << ";\n";}

    rct_h_change_step = reader.GetInteger("callback", "rct_h_change_step", -1);
    if(rct_h_change_step == -1) {std::cout << "Not found rct_h_change_step in Application::get_ini_params()!\n"; return false;}
    else {cout << "     rct_h_change_step = " << rct_h_change_step << ";\n";}
    cout << "END [callback] section:\n\n";

    zahvat_size = reader.GetInteger("tracking", "zahvat_size", -1);
    if(zahvat_size == -1) {std::cout << "Not found zahvat_size in [tracking]:Application::get_ini_params()!\n"; return false;}
    else {cout << "     zahvat_size = " << zahvat_size << ";\n";}

#ifdef USE_RECORDER
    cout << "\nSTART read ini-section [recorder]:\n";
    int use_recorder_buf = reader.GetInteger("recorder", "use_recorder", -1);
    if(use_recorder_buf == -1) {std::cout << "Not found recorder_format in Application::get_ini_params()!\n"; return false;}
    else {cout << "     use_recorder = " << use_recorder_buf << ";\n";}
    use_recorder = use_recorder_buf;

    check_memory_time = reader.GetInteger("recorder", "check_memory_time", -1);
    if(check_memory_time == -1) {std::cout << "Not found check_memory_time in Application::get_ini_params()!\n"; return false;}
    else {cout << "     check_memory_time = " << check_memory_time << ";\n";}

    min_free_memory = reader.GetInteger("recorder", "min_free_memory", -1);
    if(min_free_memory == -1) {std::cout << "Not found min_free_memory in Application::get_ini_params()!\n"; return false;}
    else {cout << "     min_free_memory = " << min_free_memory << ";\n";}


    recorder_format     = reader.GetInteger("recorder", "recorder_format", -1);
    if(recorder_format == -1) {std::cout << "Not found recorder_format in Application::get_ini_params()!\n"; return false;}
    else {cout << "     recorder_format = " << recorder_format << ";\n";}

    watchdog_quit_ms     = reader.GetInteger("recorder", "watchdog_quit_ms", -1);
    if(watchdog_quit_ms == -1) {std::cout << "Not found watchdog_quit_ms in Application::get_ini_params()!\n"; return false;}
    else {cout << "     watchdog_quit_ms = " << watchdog_quit_ms << ";\n";}

    png_compress_value     = reader.GetInteger("recorder", "png_compress_value", -1);
    if(png_compress_value == -1) {std::cout << "Not found png_compress_value in Application::get_ini_params()!\n"; return false;}
    else {cout << "     png_compress_value = " << png_compress_value << ";\n";}

    jpeg_quality     = reader.GetInteger("recorder", "jpeg_quality", -1);
    if(jpeg_quality == -1) {std::cout << "Not found jpeg_quality in Application::get_ini_params()!\n"; return false;}
    else {cout << "     jpeg_quality = " << jpeg_quality << ";\n";}

    frames_record_dir = reader.Get("recorder", "frames_record_dir", "oops");
    if(frames_record_dir == "oops") {cout << "Not found frames_record_dir in Application::get_ini_params()!\n"; return 0;}
    else {cout << "     frames_record_dir = " << frames_record_dir << ";\n";}

    int rec_force_replace_buf = reader.GetInteger("recorder", "rec_force_replace", -1);
    if(rec_force_replace_buf == -1) {std::cout << "Not found rec_force_replace in Application::get_ini_params()!\n"; return false;}
    else {cout << "     rec_force_replace = " << rec_force_replace_buf << ";\n";}
    rec_force_replace   = rec_force_replace_buf;

    int rec_make_path_buf = reader.GetInteger("recorder", "rec_make_path", -1);
    if(rec_make_path_buf == -1) {std::cout << "Not found rec_make_path in Application::get_ini_params()!\n"; return false;}
    else {cout << "     rec_make_path = " << rec_make_path_buf << ";\n";}
    rec_make_path       = rec_make_path_buf;

    int adaptive_make_rec_dir_tmp = reader.GetInteger("recorder", "adaptive_make_rec_dir", -1);
    if(adaptive_make_rec_dir_tmp == -1){std::cout << "Not found adaptive_make_rec_dir in Application::get_ini_params()!\n"; return false;}
    else {std::cout << "     adaptive_make_rec_dir = " << adaptive_make_rec_dir_tmp << ";\n";}
    adaptive_make_rec_dir = adaptive_make_rec_dir_tmp;

    std::string rec_zoo_dir_path_tmp = reader.Get("recorder", "rec_zoo_dir_path", "oops");
    if(rec_zoo_dir_path_tmp == "oops") {std::cout << "Not found rec_zoo_dir_path in Application::get_ini_params()!\n"; return false;}
    else {std::cout << "     rec_zoo_dir_path = " << rec_zoo_dir_path_tmp << std::endl;}
    rec_zoo_dir_path = rec_zoo_dir_path_tmp;

    int makepath_rec_zoo_dir_tmp = reader.GetInteger("recorder", "makepath_rec_zoo_dir", -1);
    if(makepath_rec_zoo_dir_tmp == -1){std::cout << "Not found makepath_rec_zoo_dir in Application::get_ini_params()!\n"; return false;}
    else {std::cout << "     makepath_rec_zoo_dir = " << makepath_rec_zoo_dir_tmp << ";\n";}
    makepath_rec_zoo_dir = makepath_rec_zoo_dir_tmp;

    int base_val_rec_dir_tmp = reader.GetInteger("recorder", "base_val_rec_dir", -1);
    if(base_val_rec_dir_tmp == -1){std::cout << "Not found base_val_rec_dir in Application::get_ini_params()!\n"; return false;}
    else {std::cout << "     base_val_rec_dir = " << base_val_rec_dir_tmp << ";\n";}
    base_val_rec_dir = base_val_rec_dir_tmp;
    cout << "END read ini-section [recorder]:\n";

#endif // USE_RECORDER

    cout << "END get_ini_params Application" << endl;
    return 1;
} // -- END get_ini_params
void Application::quit()
{
    cout << "Application START quit()!" << endl;
    quit_async();
    bool ok_quit = false;
    if(quit_was_called.load())
    {
        return;
    }
    quit_was_called.store(true);
    _execute.store(false, memory_order_release);

    cout << " --- BEGIN Application::quit" << endl;

#ifdef USE_LOGGER
    std::cout << "\t --- BEGIN logger::quit()" << std::endl;
    bool logger_quit_report = LoggerArtem::inst().quit();
    if(logger_quit_report)
    {
        std::cout << "\tlogger quit success" << std::endl;
    }
    else
    {
        std::cout << "\t logger quit failed" << std::endl;
    }
    std::cout << " \t --- END logger::quit()" << std::endl;
#endif //USE_LOGGER

    if(device != nullptr)
    {
        std::cout << "\t --- BEGIN device->quit()" << std::endl;
        if(device != nullptr)
        {
            device->quit();
        }
        std::cout << "\t --- END device->quit()" << std::endl;
    }
#ifdef GUI_OK
    cv::destroyAllWindows();
#endif

#ifdef USE_ETH_CONTROLLER

    if (fenix2frame_sender_ptr != nullptr)
    {
        ok_quit = fenix2frame_sender_ptr->stop();
        if (ok_quit)
        {
            cout << "fenix2frame_sender_ptr->stop()" << endl;
        } // END if (ok_quit)
        else
        {
            cout << "error::fenix2frame_sender_ptr->stop()" << endl;
        } // END else
    } // END if (fenix2frame_sender_ptr != nullptr)


    if (fenix2cmd_keeper_ptr != nullptr)
    {
        ok_quit = fenix2cmd_keeper_ptr->quit();
        if (ok_quit)
        {
            cout << "fenix2cmd_keeper_ptr->quit()" << endl;;
        } // END if (ok_quit)
        else
        {
            cout << "error::fenix2cmd_keeper_ptr->quit();" << endl;
        } // END else
    } // END if (fenix2cmd_keeper_ptr != nullptr)

#ifdef USE_ETH_MD
    if (keeper != nullptr)
    {
        cout << "\t --- BBEGIN keeper->quit()" << endl;
        keeper->quit();
        cout << "\t --- END keeper->quit()" << endl;
    } // END if (keeper != nullptr)
#endif // USE_ETH_MD
#endif // USE_ETH_CONTROLLER
    cout << " --- END Application::quit" << endl;

#ifdef USE_RECORDER
    if (use_recorder)
    {
        cout << "\t --- BEGIN LvDiskMonitor->quit()" << std::endl;
        if(disk_monitor_ptr != nullptr)
        {
            if(!disk_monitor_ptr->quit())
            {
                std::cout << "ERROR: LvDiskMonitor quit failed" << std::endl;
            } // END
            else
            {
                cout << "\t --- END LvDiskMonitor->quit()" << std::endl;
            } // END else
        } // END if(disk_monitor_ptr != nullptr)

        cout << "\t --- BEGIN recorder->quit()" << std::endl;
        if(recorder_ptr != nullptr)
        {
            recorder_ptr->quit();
        } // END if(recorder_ptr != nullptr)
        std::cout << "\t --- END recorder->quit()" << std::endl;
        cout << " --- END Application::quit" << endl;
    } // END use_recoeder
#endif // USE_RECORDER



} // -- END quit

bool Application::quit_async()
{
    cout << "Application START quit_async()!" << endl;
    /*
        Проверка на предмет раннего вызова метода quit() или quit_async();
        Для гарантии безопасного выхода требуется
        обеспечить возможность только единократного вызова quit() или quit_async()
    */
    if(_quit_async_was_called.load() || quit_was_called.load())
    {
        return true;
    }

    _quit_async_was_called.store(true);
    std::cout << "BEGIN quit_async()" << std::endl;
    _execute.store(false);
    // Максимально допустимое время ожидания закрытия основного цикла приложения
    // При превышении приложение закрывается не дожидаясь закрытия потока функции exec()ж
    const int watchdog_close_exec_time_ms = 3000;
    // Общее количество отсчетов, которое выполняется
    const int subdivisions_total = 100;
    // Временной интервал проверки состояния потока метода exec() за предмет завершенности (закрытости)
    int check_interval_ms = 1;

    // Проверки безопасности введенных пользовательских значений watchdog_close_exec_time_ms и subdivisions_total
    if(subdivisions_total > 0)
    {
        check_interval_ms = watchdog_close_exec_time_ms / subdivisions_total;
    }
    if(check_interval_ms <= 0)
    {
        check_interval_ms = 1;
    }

    std::cout << "\t watchdog_close_exec_time_ms = " << watchdog_close_exec_time_ms << std::endl;
    std::cout << "\t subdivisions_total = " << subdivisions_total << std::endl;
    std::cout << "\t check_interval_ms = " << check_interval_ms << std::endl;

    bool success_close_exec = false;

    for(int i = 0; i < subdivisions_total; ++i)
    {
        if(_exec_complete_success.load())
        {
            std::cout << "\tSuccess close exec(), total wait time = " << i * check_interval_ms << " (ms)" << std::endl;
            success_close_exec = true;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(check_interval_ms));
    }

    if(!success_close_exec)
    {
        std::cout << "Error close exec()!" << std::endl;
    }

//    quit();

    _quit_async_complete.store(true);
    std::cout << "END quit_async()" << std::endl;
    return success_close_exec;
} // -- END quit_async

void Application::start()
{
    device->start();
    _execute.store(true, memory_order_release);
#ifdef GUI_OK
    cv::namedWindow(app_win_name, WINDOW_NORMAL);
#endif //GUI_OK
    exec();
} // -- END start

#ifdef TKDNN
void Application::work_TKDNN()
{
    tracShats->update(frame_process_tracshats, aimRectShats);
    tracShats->getSearchRect(searchRect);
#if defined(GUI_OK)
    Rect2f searchRect_show(frame_show.cols * searchRect.x, frame_show.rows * searchRect.y,
                           frame_show.cols * searchRect.width, frame_show.rows * searchRect.height);
    rectangle(frame_show, searchRect_show, color::white, 1);
    if(tracShats->find_)
    {
        // приведение рамки цели к абсолютным координатам
        Rect2f rectShats(aimRectShats.x * frame_show.cols, aimRectShats.y * frame_show.rows,
                         aimRectShats.width * frame_show.cols, aimRectShats.height * frame_show.rows);
        // отрисовка рамки цели
        rectangle(frame_show, rectShats, color::white, 1);
        // отрисовка центра объекта
        Point2f center = tracShats->getTargetCenter();
        Point2f center_show = Point2f(center.x * frame_show.cols, center.y * frame_show.rows);
        circle(frame_show, center_show, 2, color::white, -1);
    } // END if(tracShats->find_)
#endif // END #if defined(GUI_OK)
} // END work_TKDNN()
#endif // TKDNN

void Application::exec()
{
    bool ok = false;
#ifdef USE_DBG
    namedWindow("win", WINDOW_NORMAL);
#endif // USE_DBG
    if(parallel)
    {
        while(!frameReady.load())
        {
            this_thread::sleep_for(chrono::milliseconds(100));
        } // END while(!frameReady.load())
    } // END if(parallel)
    else
    {
        if(!device->getFirstFrame(frame_process_0))
        {
            quit();
        } // END if(!device->getFirstFrame(frame_process_0))
        frameReady.store(true);
    } // END else

    tracShats = make_shared<TracShats>(config_path, frame_process_0, ok);
    if(!ok)
    {
        quit();
        return;
    }
    setFrameSizeParams(); // вычислили переменные класса, сязанные с размером изображения после получения первого кадра
#ifdef TKDNN
    isTracShatsFirstInitedFlag = true;
    isTracShatsInitedFlag = true;
    tracShats->trac_str.new_frame = 1;
#endif // END #if defined(TKDNN)


    // основной цикл выполнения пиложения
    while(_execute.load(memory_order_acquire))
    {

#ifdef USE_ETH_MD
        keeper->get(frame_metadata, valid); // принимаем телеметрию по ehternet
        //        int frame_num = device->getId();
        //        cout << "\ndbg:: valid = " << valid << endl;
        //        cout << "dbg:: roll = " << frame_metadata.roll_rad * rad2deg << endl;
        //        cout << "dbg:: pitch = " << frame_metadata.pitch_rad * rad2deg << endl;
        //        cout << "dbg:: yaw = " << frame_metadata.yaw_rad * rad2deg << endl;
        //        cout << "dbg:: alt = " << frame_metadata.altitude_m << endl << endl;
        //        if (valid) // если телеметрия не "просрочена"
        //        {
        //            telemetry_mux::conv_TeleAP_to_TeleGen(extTeleEth, frame_num, frame_time, frame_metadata);
        //        } // END if valid
        //        frame_metadata.exposure_ms = device->getExposureMs();
#endif // USE_ETH_MD


        deviceSyncNextFrame();
        if(frameReady.load()) // если в буфере готов фрейм
        {
            deviceAsyncNextFrame();

#ifdef USE_LOGGER
            time_point_tracker0 = std::chrono::system_clock::now();
#endif // USE_LOGGER
            found = false;
            prepareFrameForTracShats();
#if !defined(TKDNN)
            workflowShats();
#endif // END #if !defined(TKDNN)
#if defined(TKDNN)
            work_TKDNN();
#endif // END #if defined(TKDNN)

#ifdef USE_LOGGER
            time_point_tracker1 = std::chrono::system_clock::now();
            if(tracShats->isInited())
            {
                LoggerArtem::inst().logTimedBasedFPS("TrackShats FPS = ",
                                                     chrono::duration<double>(time_point_tracker1 - time_point_tracker0).count());
#ifdef TKDNN
                LoggerArtem::inst().logTimedBasedFPS("Scan FPS = ", tracShats->trac_str.scan_exec_time);
                LoggerArtem::inst().logTimedBasedFPS("YOLO FPS = ", tracShats->trac_str.yolo_exec_time);
#endif // TKDNN
            }
#endif //USE_LOGGER

            cv::Rect2f rect;
            uchar key;

#ifdef GUI_OK
            cv::resize(frame_receive, frame_show, cv::Size(frame_show_width, frame_receive.rows * show2originImgRatio));
            cv::cvtColor(frame_show, frame_show, cv::COLOR_GRAY2BGR);
            if(mouseHandler(frame_show, app_win_name, key, rect))
#elif USE_ETH_CONTROLLER
            if(ethHandler(rect))
#endif // USE_ETH_CONTROLLER
            {
                if (!tracShats->isInited())
                {
                    cout << "TRY INIT" << endl;
                    initTracShats(rect);
                }
            } // -- END if(mouseHandler(frame_show, app_win_name, key, rect))


            if(need_quit)
            {
                std::cout << "need quit" << std::endl;
                quit();
                break;
            } // END if(need_quit)

#ifdef USE_ETH_CONTROLLER
            ethControllerProc();
#endif // USE_ETH_CONTROLLER
            device->workflow();
            device->keyHandler(key);

        } // END if(frameReady.load())
        else
        {
            bool ws_ok1 = false;
            bool need_brake_quit = false;
            while(!frameReady.load())
            {
                if(!parallel)
                {
                    break;
                } // -- END if(!parallel)
                else
                {
#if !defined(TKDNN)
                    this_thread::sleep_for(milliseconds(5));
#endif // END #if !defined(TKDNN)
#if defined(TKDNN)
                    work_TKDNN();
#endif // END #if defined(TKDNN)
                } // END else
            } // -- END while(!frameReady.load())
        } // -- END if(frameReady.load())
    } // -- END while(_execute.load(memory_order_acquire))

    std::cout << "Complete Application::exec()" << std::endl;
    _exec_complete_success.store(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    bool success_wait_quit_async_complete = false; // флаг успешного завершения работы метода quit_async()
    if(_quit_async_was_called.load())
    {
        for(int i = 0; i < 100; ++i)
        {
            if(_quit_async_complete.load())
            {
                success_wait_quit_async_complete = true;
                std::cout << "_quit_async_complete detected <<true>>" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                break;
            } // END if(_quit_async_complete.load())
        } // END for(int i = 0; i < 100; ++i)
    } // END if(_quit_async_was_called.load())
    std::cout << "END exec" << std::endl;
} // -- END exec

#ifdef USE_ETH_CONTROLLER
void Application::ethControllerProc()
{
    bool ok_send_frame = 0;
    unsigned long long int time_now = std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count() % 3'600'000'000;


#ifdef TKDNN
    if(tracShats->find_)
#else // !TKDNN
    if (tracShats->isInited())
#endif // !TKDNN
    {
        Point2f pt_c = tracShats->getTargetCenter();
        if (track_confirm_flag)
        {
            dx_c_pix = 2.f * (pt_c.x - 0.5f) ; // отклонение pix/pix_max
            dy_c_pix = 2.f * (pt_c.y - 0.5f) ;
        }
        else if(fenix2cmd_keep_data.work_mode == 1)
        {
            dx_c_pix = fenix2cmd_keep_data.mouse_pos_x * 2.f - 1;
            dy_c_pix = fenix2cmd_keep_data.mouse_pos_y * 2.f - 1;
        } // END work_mode == 1
        else /*if (!fenix2cmd_keep_data.work_mode)*/
        {
            dx_c_pix = 0.f;
            dy_c_pix = 0.f;
        }
        get_point_xy_ss(dx_c_pix,
                        dy_c_pix,
                        frame_metadata.altitude_m,
                        frame_metadata.roll_rad,
                        frame_metadata.pitch_rad,
                        frame_metadata.yaw_rad,
                        dx_m_ss,
                        dy_m_ss);


        /// META2CLIENT
        fenix2meta_data2send.num_frame = device->getId();
        fenix2meta_data2send.time_delay_mcs = std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::system_clock::now().time_since_epoch()).count() % 3'600'000'000;
        fenix2meta_data2send.track_is_init = true;
        fenix2meta_data2send.trackx = pt_c.x;
        fenix2meta_data2send.tracky = pt_c.y;
        fenix2meta_data2send.new_trackw = 2 * rct_wh_2.x * frame_w_1; //rct_wh_2.x;
        fenix2meta_data2send.new_trackh = 2 * rct_wh_2.y * frame_h_1; //rct_wh_2.y;
        fenix2meta_data2send.trackw = aimRectShats.width; //rct_wh_2.x;
        fenix2meta_data2send.trackh = aimRectShats.height; //rct_wh_2.y;
        fenix2meta_data2send.diff_trackx = dx_c_pix;
        fenix2meta_data2send.diff_tracky = dy_c_pix;
        fenix2meta_data2send.x_m_s = x_m_s;
        fenix2meta_data2send.y_m_s = y_m_s;
        fenix2meta_data2send.x_m_ss = dx_m_ss;
        fenix2meta_data2send.y_m_ss = dy_m_ss;
        fenix2meta_data2send.roll_deg = frame_metadata.roll_rad * rad2deg;
        fenix2meta_data2send.pitch_deg = frame_metadata.pitch_rad * rad2deg;
        fenix2meta_data2send.yaw_deg = frame_metadata.yaw_rad * rad2deg;
        fenix2meta_data2send.alt_m = frame_metadata.altitude_m;
        fenix2meta_data2send.tp_send = time_now;
        fenix2meta_data2send.track_confirm = track_confirm_flag;
        if(tracShats->trac_str.work_in_round){fenix2meta_data2send.work_in_round = 1;}
        /// META2AP
        bool correct_data2ap = track_confirm_flag || (fenix2cmd_keep_data.work_mode == 1);
        trackmeta_pos_data_now = {dx_m_ss,
                                  dy_m_ss,
                                  correct_data2ap};

    } // END if (tracShats->isInited())
    else // !trackShats->isInited()
    {
        track_confirm_flag = 0;
        fenix2meta_data2send = {(uint32_t)device->getId(),  // id
                                time_now,                   // time now
                                0,                          // track_is_init
                                (bool)track_confirm_flag,   // track_confirm
                                CORR_TYPE,                  // gpu_type
                                device_id,                  // device
                                0,                          // tracky
                                0,
                                2 * rct_wh_2.x * frame_w_1, // new_trackw
                                2 * rct_wh_2.y * frame_h_1,
                                2 * rct_wh_2.x * frame_w_1, // track_w
                                2 * rct_wh_2.y * frame_h_1,
                                0,                          // difftrackx
                                0,
                                0,                          // x_m_s
                                0,
                                0,                          // x_m_ss
                                0,
                                frame_metadata.roll_rad * rad2deg,
                                frame_metadata.pitch_rad * rad2deg,
                                frame_metadata.yaw_rad * rad2deg,
                                frame_metadata.altitude_m,
                                time_now,                   // tp_send
                                0,                          // tp_keep
                                tracShats->trac_str.work_in_round
                               };

        if (fenix2cmd_keep_data.work_mode == 0)
        {
            trackmeta_pos_data_now = {0.f,
                                      0.f,
                                      false};
        }
        else if (fenix2cmd_keep_data.work_mode == 1)
        {
            dx_c_pix = fenix2cmd_keep_data.mouse_pos_x * 2.f - 1;
            dy_c_pix = fenix2cmd_keep_data.mouse_pos_y * 2.f - 1;

            fenix2meta_data2send.diff_trackx = dx_c_pix;
            fenix2meta_data2send.diff_tracky = dy_c_pix;
            fenix2meta_data2send.x_m_s = x_m_s;
            fenix2meta_data2send.y_m_s = y_m_s;
            fenix2meta_data2send.x_m_ss = dx_m_ss;
            fenix2meta_data2send.y_m_ss = dy_m_ss;
            fenix2meta_data2send.roll_deg = frame_metadata.roll_rad * rad2deg;
            fenix2meta_data2send.pitch_deg = frame_metadata.pitch_rad * rad2deg;
            fenix2meta_data2send.yaw_deg = frame_metadata.yaw_rad * rad2deg;
            fenix2meta_data2send.alt_m = frame_metadata.altitude_m;
            fenix2meta_data2send.track_confirm = track_confirm_flag;

            get_point_xy_ss(dx_c_pix,
                            dy_c_pix,
                            frame_metadata.altitude_m,
                            frame_metadata.roll_rad,
                            frame_metadata.pitch_rad,
                            frame_metadata.yaw_rad,
                            dx_m_ss,
                            dy_m_ss);
            trackmeta_pos_data_now = {dx_m_ss,
                                      dy_m_ss,
                                      true};
        } // END work_mode == 1
    } // END else (!trackShats->isInited())

#ifdef USE_DBG
    cout << "dbg:: track_meta2AP = " << setprecision(10) <<
            Point3f(trackmeta_pos_data_now.delta_x_rad,
                    trackmeta_pos_data_now.delta_y_rad,
                    (float)trackmeta_pos_data_now.valid) << " | " << track_confirm_flag << endl;
#endif // USE_DBG
    trackmeta_pos_sender_ptr->set(trackmeta_pos_data_now);



#ifdef USE_DBG
    cout << "dbg:: ---------" << endl <<
            "dbg:: num_frame = " << fenix2meta_data2send.num_frame << endl <<
            "dbg:: time_delay_mcs = " << fenix2meta_data2send.time_delay_mcs << endl <<
            "dbg:: track_is_init = " <<  fenix2meta_data2send.track_is_init << endl <<
            "dbg:: trackx = " <<  fenix2meta_data2send.trackx << endl <<
            "dbg:: tracky = " <<  fenix2meta_data2send.tracky << endl <<
            "dbg:: trackw = " <<  fenix2meta_data2send.trackw << endl <<
            "dbg:: trackh = " <<  fenix2meta_data2send.trackh << endl <<
            "dbg:: diff_tracky = " <<  fenix2meta_data2send.diff_tracky << endl <<
            "dbg:: tp_send = " <<  fenix2meta_data2send.tp_send << endl << endl;
    cout << "dbg:: frame_receive.channels() = " << frame_receive.channels() << endl;
    if (frame_receive.data) {cout << "dbg:: frame ok, frame size = " << frame_receive.size() << endl;}

#endif // USE_DBG

    fenix2frame_sender_ptr->setMeta(fenix2meta_data2send);

#ifdef USE_DBG
    cv::imshow("win", frame_receive);
    uchar exit_key = cv::waitKey(1);
    if (exit_key == '`') {need_quit = 1;}
#endif // USE_DBG

#ifdef USE_RECORDER
    if (use_recorder)
    {
        now_free_memory = disk_monitor_ptr->get_free_space_mb();
        if (use_recorder && tracShats->isInited() && (now_free_memory > min_free_memory))
        {
            if(!recorder_ptr->save(frame_receive, device->getId())) // запись фреймов в папку
            {
                cout << "Can't record " <<  device->getId() << " frame!" << endl;
            } // END if(!recorder_ptr->save(frame_receive, cycle_counter))
            else
            {
                std::string frame_data = "0 " +
                        to_string(tracShats->getTargetCenter().x) + " " +
                        to_string(tracShats->getTargetCenter().y) + " " +
                        to_string(aimRectShats.width) + " " +
                        to_string(aimRectShats.height) + "\n";
                ofstream write;
                std::string frame_name = to_string(rec_settings.base.base_value + device->getId());
                string filename = rec_settings.base.dir_path + frame_name + ".txt";
                write.open(filename.c_str(), ios::trunc);
                if (!write.is_open()) {cout << "Cant open file " << filename << endl; }
                write << frame_data;
                write.close();

            }
        } // END if(now_free_space <= min_free_space)
    }
#endif // USE_RECORDER

    cv::Mat frame_send;

    resize(frame_receive, frame_send, Size(frame_send_w, frame_send_h));
    fenix2frame_sender_ptr->newFrame(frame_send.data,
                                     frame_send.cols * frame_send.rows * frame_send.channels());
    //    fenix2frame_sender_ptr->newFrame(frame_receive.data,
    //                     resize                frame_receive.cols * frame_receive.rows * frame_receive.channels());
    return;
} // END ethControllerProc
#endif

void Application::setFrameSizeParams()
{
    int frame_w = frame_process_0.rows; //cols;
    int frame_h = frame_process_0.rows;
    show2originImgRatio = (float)frame_show_width / frame_w;
    // 2 FENIX
    rct_wh_2 = {zahvat_size * 0.5f, zahvat_size * 0.5f};
    pt_frame_center = 0.5 * Point2f(frame_w * show2originImgRatio, frame_h * show2originImgRatio);
    frame_w_1 = 1.f / (float)frame_w;
    frame_h_1 = 1.f / (float)frame_h;
    frame_show_w_1 = 1.f / (float)frame_show_width;
    frame_show_h_1 = 1.f / (float)(frame_h * show2originImgRatio);
    return;
} // -- END setFrameSizeParams

void Application::deviceAsyncNextFrame()
{
    /*
            Обособленный mutex'ом фрагмент не осуществляет клонирования frame,
            реализуется оптимальная передача по ссылке,
            но дополнительная потокобезопасность обеспечивается
            frame_proc_(0/1)_mutex без существенных накладных расходов
            */

    if (parallel)
    {
        switch(process_frame_id) // id буффера на предыдущем шаге
        {
        case 0:
        {
            frame_proc_1_mutex.lock();
            process_frame_id = 1;
            frame_receive = frame_process_1 ;
            frame_proc_1_mutex.unlock();
        } // END case 0:
            break;

        case 1:
        {
            frame_proc_0_mutex.lock();
            process_frame_id = 0;
            frame_receive = frame_process_0;
            frame_proc_0_mutex.unlock();
        } // END case 1:
            break;

        default:
        {
            throw std::runtime_error("Error: incorrect process_frame_id");
        } // END default
            break;
        } // END switch(process_frame_id
    } // END if(parallel)
    frameReady.store(false); // считали фрейм из буфера

    return;
} // END deviceAsyncNextFrame

void Application::deviceSyncNextFrame()
{
    if(!parallel)
    {
#ifdef USE_LOGGER
        time_point_device0 = std::chrono::high_resolution_clock::now();
#endif //USE_LOGGER
        device->getFrame(frame_receive);
#ifdef USE_LOGGER
        time_point_device1 = std::chrono::high_resolution_clock::now();
        LoggerArtem::inst().logTimedBasedFPS(
                    "Device FPS = ",
                    chrono::duration<double>(time_point_device1 - time_point_device0).count());
#endif //USE_LOGGER
        frameReady.store(true);
    } // if (!parallel)
    return;
} // -- END deviceSyncNextFrame

bool Application::processShats()
{
    // обновление рамки цели по текущему кадру
    bool found = tracShats->update(frame_process_tracshats, aimRectShats);
    //std::cout << "processShats " << found << std::endl;
    if(found)
    {
        if(tracShats->roi)
        {
            roi = tracShats->getROI();
        } // -- END if(tracShats->roi)
        return true;
    } // -- END if(tracShats->update(frame_process_tracshats, aimRectShats))
    return false;
} // -- END processShats

void Application::workflowShats()
{
    if(isTracShatsFirstInitedFlag)
    {
#ifdef GUI_OK
        if(demonstration_mode > 2 && tracShats->isInited())
        {
            cv::circle(frame_show, Point(80, 90), 5, clr_scaling, -1);
        } // -- END if(demonstration_mode > 2 && tracShats->trac_str.zahvat)
#endif //GUI_OK

        bool found = processShats();// обработка кадра
        if(found)
        {
#ifdef GUI_OK
            // приведение рамки цели к абсолютным координатам
            cv::Rect2f rectShats(aimRectShats.x * frame_show.cols,
                                 aimRectShats.y * frame_show.rows,
                                 aimRectShats.width * frame_show.cols,
                                 aimRectShats.height * frame_show.rows);
            // отрисовка рамки цели
            cv::rectangle(frame_show, rectShats, color::Green::lime, 1);
            // отрисовка центра объекта
            cv::Point2f center = tracShats->getTargetCenter();
            center = cv::Point2f(center.x * frame_show.cols, center.y * frame_show.rows);
            cv::circle(frame_show, center, 2, color::red, -1);
            // добавление метки размера объекта на кадр
            if(demonstration_mode > 1)
            {
                tracShats->getSearchRect(searchRect);
                searchRect = cv::Rect2f(searchRect.x * frame_show.cols,
                                        searchRect.y * frame_show.rows,
                                        searchRect.width * frame_show.cols,
                                        searchRect.height * frame_show.rows);
                cv::rectangle(frame_show, searchRect, color::blue, 1);
                /// FENIX 2
                string delta_txt = "Delta position: [" +
                        to_string((searchRect.x + 0.5 * searchRect.width) / show2originImgRatio - frame_receive.cols * 0.5)  + "; " +
                        to_string((searchRect.y + 0.5 * searchRect.height) / show2originImgRatio - frame_receive.rows * 0.5) + "]";
                putText(frame_show, delta_txt, Point(50, 50),FONT_ITALIC, 1, color::Green::lime, 2);

                if(demonstration_mode > 3)
                {
                    cv::Point objSize(round(aimRectShats.width * frame_receive.cols),
                                      round(aimRectShats.height * frame_receive.rows));
                    std::string txt = "Object size=[" + to_string(objSize.x) + ", " + to_string(objSize.y) + "]";
                    putText(frame_show, txt, Point(100, 100), FONT_ITALIC, 1, color::Green::lime, 2);
                } // -- END if(demonstration_mode > 3)
            } // -- END if(demonstration_mode > 1)
#endif //GUI_OK
            // -- END if(found)
        }
        else
        {
            if(!tracShats->isInited()){isTracShatsInitedFlag = false;}
        }
        // -- END if(isTracShatsFirstInitedFlag)
    }
    else if(tracShatsInitReqFlag)
    {      // инициализация трекера при поступлении запроса
        tracShatsInitReqFlag = false;
        std::cout << "Init tracker" << std::endl;
        initTracShats(aimRectShats);
    } // -- END else if(tracShatsInitReqFlag)
} // -- END workflowShats

void Application::initTracShats(Rect2f &rect)
{
    bool rect_on_frame = (rect.tl().x >= rct_frame.tl().x &&
                          rect.tl().y >= rct_frame.tl().y &&
                          rect.br().x < rct_frame.br().x &&
                          rect.br().y < rct_frame.br().y);
    if(!tracShats->isInited() && rect_on_frame)
    {
        bool initFlag = false;

        if(roi_mode)
        {
            initFlag = tracShats->init(rect, roi);
            tracShats->setWorkNumber(device->getFrameCounter());
            if(initFlag)
            {
                isRoiSetted = true;
            }
        } // END if(roi_mode)
        else
        {
            initFlag = tracShats->init(rect);
            tracShats->setWorkNumber(device->getFrameCounter());
        }
        if(initFlag)
        {
            if(!isTracShatsFirstInitedFlag){isTracShatsFirstInitedFlag = true;}
            isTracShatsInitedFlag = true;
        } // -- END if(initFlag)
    } // -- END if(!tracShats->isInited())
    prepareFrameForTracShats();
    // обработка кадра "на месте" для корректной инициализации трекера

    workflowShats();

    return;
} // -- END initTracShats

void Application::get_point_xy_ss(const float & x_pix,  // смещение в нормированных координатах
                                  const float & y_pix,
                                  const float & H,      // высота
                                  const float & alpha,  // крен
                                  const float & beta,   // тангаж
                                  const float & gamma,  // азимут
                                  float & x_m_ss,       // смещение в метрах
                                  float & y_m_ss)
{
    float tan_x_a = x_pix * tan_max;
    float tan_y_b = y_pix * tan_max;
    float tan_a = tan(alpha);
    float tan_b = tan(beta);
    x_m_s = H * (tan_x_a - tan_a) / (1.f + tan_x_a * tan_a);
    y_m_s = H * (tan_y_b - tan_b) / (1.f + tan_y_b * tan_b);
    float gamma1 = gamma0 + gamma;
    float sin_gamma1 = sin(gamma1);
    float cos_gamma1 = cos(gamma1);
    x_m_ss = cos_gamma1 * x_m_s + sign * sin_gamma1 * y_m_s;
    y_m_ss = -sign * sin_gamma1 * x_m_s + cos_gamma1 * y_m_s;
    return;
} // -- END get_point_xy_ss()


// подготовка изображения для tracShats
void Application::prepareFrameForTracShats()
{
    if(roi_mode and isRoiSetted)
    {
        // расчет абсолютных координат ROI
        cv::Rect realSizedROI(roi.x * frame_receive.cols, roi.y * frame_receive.rows,
                              roi.width * frame_receive.cols, roi.height * frame_receive.rows);
        frame_process_tracshats = frame_receive(realSizedROI).clone();
        //                        // отрисовка ROI
        //                        cv::rectangle(frame_color, realSizedROI, color::blue, 2);
        // cv::imwrite("../test_data/img1.png", frame_process_tracshats);
    }
    else
    {
        frame_process_tracshats = frame_receive; //.clone();
    }
} // -- END prepareFrameForTracShats

void Application::handleDeviceFrame(uint8_t *f, int w, int h, int num, int id)
{
    static auto prevFrameReceiveTime = std::chrono::high_resolution_clock::now();
    auto receiveTime = std::chrono::high_resolution_clock::now();

#ifdef USE_LOGGER
    LoggerArtem::inst().logTimedBasedFPS(
                "Device FPS = ",
                chrono::duration<double>(receiveTime - prevFrameReceiveTime).count());
#endif //USE_LOGGER

    prevFrameReceiveTime = receiveTime;

    static bool first_frame = true;

    if(first_frame)
    {
#if defined(CCM_8UC1)
        int cvmat_type = CV_8UC1;
#elif defined(CCM_8UC3)
        int cvmat_type = CV_8UC3;
#else
        throw std::runtime_error("Error: not recognize/supported color channel mode");
#endif
        frame_proc_0_mutex.lock();
        frame_process_0 = cv::Mat(cv::Size(w,h), cvmat_type);
        device->getFormatedImage(f, w, h, id, frame_process_0);
        frame_proc_0_mutex.unlock();

        frame_proc_1_mutex.lock();
        frame_process_1 = frame_process_0.clone();
        frame_proc_1_mutex.unlock();

        first_frame = false;
        frameReady.store(true);
    }
    else if(!frameReady.load()) // -- END if(first_frame)
    {
        switch(process_frame_id) // двойная буфферизация
        {
        case 0:
            frame_proc_1_mutex.lock();
            device->getFormatedImage(f, w, h, id, frame_process_1);
            frame_proc_1_mutex.unlock();
            break;

        case 1:
            frame_proc_0_mutex.lock();
            device->getFormatedImage(f, w, h, id, frame_process_0);
            frame_proc_0_mutex.unlock();
            break;

        default:
            throw std::runtime_error("Error: incorrect process_frame_id");
            break;
        }
        frameReady.store(true);
    } // -- END if(!frameReady.load())
} // -- END handleDeviceFrame

#ifdef USE_RECORDER
bool Application::adaptive_dirs_setup()
{
    if(!make_adaptive_rec_dir())
    {
        return false;
    }
    cout << "======dbg:: mske_adaptive_rec_dir!!!======" << endl;
    frames_record_dir = rec_dir + "/" + frames_pstfx + "/";
    std::vector<std::string > paths_pack = {
        frames_record_dir};
    cout << "dbg:: frames_record_dir = " << frames_record_dir << endl;
    // подразумевается, что все rec_dir + "$pstfx$" вновь создаваемые без теор. возможности уже текущего существования
    for(int i = 0; i < paths_pack.size(); ++i)
    {
        if(!path_processing::makePath(paths_pack[i]))
        {
            std::cout << "ERROR: create dir = " << paths_pack[i] << " failed";
            return false;
        } // END makePath
    } // END for(int i = 0; i < paths_pack.size(); ++i)
    syst_time_extract::DateTime _dt = syst_time_extract::getCurrentDateTime();
    std::ofstream ofs(rec_dir + "/timestamp.txt", std::ios::trunc | std::ios::out);
    if(!ofs.is_open())
    {
        std::cout << "ERROR: create timestamp file" << std::endl;
        return false;
    } // END if(!ofs.is_open())
    ofs << "day " << _dt.day << "\n"
        << "month " << _dt.month << "\n"
        << "year " << _dt.year << "\n"
        << "hour " << _dt.hour << "\n"
        << "min " << _dt.min << "\n"
        << "sec " << _dt.sec;
    ofs.close();

    return true;
} // -- END adaptive_dirs_setup


bool Application::make_adaptive_rec_dir()
{
    if(path_processing::isDirExist(rec_zoo_dir_path))
    {
        std::vector<std::string> rec_dirs_zoo;
        if(!path_processing::getDirsContentInDir(rec_zoo_dir_path, rec_dirs_zoo, false))
        {
            return false;
        }
        if(rec_dirs_zoo.size() > 2)
        {
            int max_val = std::stoi(rec_dirs_zoo.back());
            rec_dir = rec_zoo_dir_path + "/" + std::to_string(max_val + 1);
        }
        else
        {
            rec_dir = rec_zoo_dir_path + "/" + std::to_string(base_val_rec_dir);
        }

        if(!path_processing::makePath(rec_dir))
        {
            std::cout << "ERROR: create subdir in rec_zoo_dir_path failed" << std::endl;
            return false;
        }
    } // END if(isDirExist)
    else
    {
        if(makepath_rec_zoo_dir)
        {
            rec_dir = rec_zoo_dir_path + "/" + std::to_string(base_val_rec_dir);
            if(!path_processing::makePath(rec_dir))
            {
                std::cout << "ERROR: create dir rec_zoo_dir_path failed" << std::endl;
                return false;
            } // END if(!path_processing::makePath(rec_dir))
        } // END if(makepath_rec_zoo_dir)
        else
        {
            return false;
        } // END else
    } // END if(!isDirExist)
    return true;
} // -- END make_adaptive_rec_dir
#endif // USE_RECORDER
