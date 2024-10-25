#include "application.hpp"

using namespace std;
using namespace cv;
using namespace chrono;

bool Application::click_down = 0;
bool Application::click_up = 0;
Point Application::p_mouse(0, 0);
Point Application::p_down(0, 0);

Application::~Application(){cout << "Деструктор Application" << endl;}

Application::Application(const string & pathToConfig,
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
    } // END if(!create_logger_status)
#endif //USE_LOGGER

#ifdef USE_CORSAIR_400_RAW
    string section = "vtrack_data_sender";
    sender_ptr = track_pos_sender::create(config_path, section);
    if(sender_ptr == nullptr)
    {
        std::cout << "ERROR: create vtrack_data_sender failed" << std::endl;
        ok = false;
        return;
    } // END if(sender_ptr == nullptr)
    track_pos_data2send.v_track.reserve(max_objects);

    cmd_keeper_ptr = cmd400_keeper::create(config_path, "cmd400_keeper");
    if(!cmd_keeper_ptr->setup())
    {
        cout << "Application::ERROR start cmd_keeper_ptr!" << endl;
        ok = false;
        quit(); //?
        return;
    } // END if(!cmd_keeper_ptr->setup())
#endif // USE_CORSAIR_400_RAW

    switch(device_id)
    {
#ifdef USE_FOLDER_READER
    case FOLDER:
        device = make_shared<FolderReader>(config_path, ok);
        cout << "make_shared<FolderReader> OK=" << ok << endl;
        if(!ok){cout << "Not ok FolderReader!" << endl; return;}
        break;
#endif // END USE_FOLDER_READER
#ifdef USE_COLIBRI_TV
    case COLIBRITV:
        device = make_shared<ColibriTV>(config_path, ok);
        if(!ok){cout << "Not ok ColibriTV!" << endl; return;}
        device->setup();
        break;
#endif // END USE_COLIBRI_TV
#ifdef USE_VIDEO_READER
    case VIDEO:
        device = make_shared<VideoReader>(config_path, ok);
        if(!ok){return;}
        break;
#endif
#ifdef USE_WEB_CAMERA
    case WEBCAMERA:
        device = make_shared<WebCamera>(config_path, ok);
        if(!ok){return;}
        break;
#endif // END USE_WEB_CAMERA
#ifdef USE_SHARED_MEMORY
    case SHARED_MEMORY:
        device = make_shared<SharedMemory>(config_path, ok);
        if(!ok){return;}
        device->setup();
        break;
#endif // END USE_SHARED_MEMORY
#ifdef USE_RASPBERRY_HQ_CAMERA
    case RASPBERRY_HQ_CAMERA:
        device = devices::raspberry_hq_camera::create(config_path);
        device->setup();
        break;
#endif // END USE_RASPBERRY_HQ_CAMERA
#ifdef USE_IMX219_CAMERA_MIPI
    case IMX219_CAMERA_MIPI:
        device = devices::imx219_camera_mipi::create(config_path);
        device->setup();
        break;
#endif // END USE_IMX219_CAMERA_MIPI
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

#ifdef USE_CORSAIR_400_RAW
    case CORSAIR_400_RAW:
        device = devices::corsair_400_raw::create(config_path, "corsair_400_raw");
        if(device == nullptr)
        {
            std::cout << "ERROR: create CORSAIR_400_RAW device failed" << std::endl;
            ok = false;
            return;
        } // END if(device == nullptr)
        break;
#endif // USE_CORSAIR_400_RAW

#ifdef USE_GST_RTP
    case GST_RTP:
    {
        break;
    } // -- END case GST_RTP:
#endif // USE_GST_RTP
    default:
        break;
    } // -- END switch

    if(device != nullptr)
    {
        if(!parallel && !(device_id == FOLDER || device_id == VIDEO))
        {
            parallel = true;
        } // END if(!parallel && !(device_id == FOLDER || device_id == VIDEO))
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
    } // END if(device == nullptr)
    for(int key = 0; key < 256; key++){wh_2_ext[key] = Point(0, 0);}
    wh_2_ext['z'] = Point(-1, -1);
    wh_2_ext['x'] = Point(1, 1);
    wh_2_ext['4'] = Point(-1, 0);
    wh_2_ext['7'] = Point(-1, 1);
    wh_2_ext['8'] = Point(0, 1);
    wh_2_ext['9'] = Point(1, 1);
    wh_2_ext['6'] = Point(1, 0);
    wh_2_ext['3'] = Point(-1, 1);
    wh_2_ext['2'] = Point(0, -1);
    wh_2_ext['1'] = Point(-1, -1);
#ifdef GUI_OK
    namedWindow(app_win_name, WINDOW_NORMAL);
#endif //GUI_OK

#ifdef DBG_VIDEO_SENDER
    cout << " ------ BEGIN create fenix2frame_sender_ptr" << endl;
    settings_srv_ptr = std::make_shared<rtp::server::Settings>();
    ok = rtp::server::getIniSettings(config_path, rtp_server_section, *settings_srv_ptr);
    if (!ok)
    {
        cout << "ERROR: Application::rtp::server::getIniSettings!" << endl;
        return;
    } // END if (!ok)
    fenix2frame_sender_ptr = make_shared<rtp::RtpServer>(settings_srv_ptr);

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

#endif // DBG_VIDEO_SENDER

    if(video_on)
    {
        if(DirContent(path4frames, fileList))
        {
            if(fileList.size())
            {
                string last_file = fileList[fileList.size() - 1];
                string last_file1 = last_file.substr(0, last_file.length() - 4);
                int last_num = stoi(last_file1) - save_frames_prefix;
                video_num = last_num + 2;
            } // END if(fileList.size())
            else{video_num = 1;}
        } // END if(DirContent(path4frames, fileList))
        else
        {
            cout << "Record direcry: " << path4frames << " NOT EXIST!" << endl;
            video_on = 0;
            ok = false;
            quit();
            return;
        } // END else
    } // END if(video_on)

    cout << "start create_rtsp_server" << endl;
    std::thread thrd_rtsp(&rtspsrv::gst_loop);
    thrd_rtsp.detach();
//    rtsp_srv_ptr = make_shared<rtsp::server::RTSPServer>();
//    rtsp_srv_ptr->start();
    cout << "Application:: end rtsp_srv_ptr->setup()" << endl;

    cout << "OK create rtsp_srv_ptr" << endl;
} // -- END Application

bool Application::FileIsExist(const string& filePath)
{
    bool isExist = false;
    ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist

bool Application::DirContent(string& path, vector<string>& fileList)
{
    fileList.clear();
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(path.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            string filename = string(ent->d_name);
            // -- typ = 4 (folder), typ = 8 (file).
            if(ent->d_type == 8 && filename != "." && filename != "..")
            {
                fileList.emplace_back(filename);
            } // END if(ent->d_type == 8 && filename != "." && filename != "..")
        } // -- END while((ent = readdir (dir)) != NULL)
        closedir(dir);
        if(fileList.size() > 1){sort(fileList.begin(), fileList.end());}
        cout << "Dir " << path << " open success." << endl;
        return 1;
    } // -- END if((dir = opendir(way)) != NULL)
    cout << "Dir " << path << " can't open!" << endl;
    return 0;
} // -- END DirContent


void Application::quit()
{
    if(quit_was_called.load())
    {
        return;
    } // END if(quit_was_called.load())
    quit_was_called.store(true);

    _execute.store(false, memory_order_release);

    cout << " --- BEGIN Application::quit" << endl;
#ifdef USE_LOGGER
    cout << "\t --- BEGIN logger::quit()" << endl;
    bool logger_quit_report = LoggerArtem::inst().quit();
    if(logger_quit_report)
    {
        cout << "\tlogger quit success" << endl;
    } // END if(logger_quit_report)
    else
    {
        cout << "\t logger quit failed" << endl;
    } // END else
    cout << " \t --- END logger::quit()" << endl;
#endif //USE_LOGGER

    if(device != nullptr)
    {
        cout << "\t --- BEGIN device->quit()" << endl;
        if(device != nullptr)
        {
            device->quit();
        } // END if(device != nullptr)
        cout << "\t --- END device->quit()" << endl;
    } // END if(device != nullptr)
#ifdef GUI_OK
    destroyAllWindows();
#endif

#ifdef USE_CORSAIR_400_RAW
    cmd_keeper_ptr->quit();
    // sender_ptr->quit();
#endif //USE_CORSAIR_400_RAW


#ifdef DBG_VIDEO_SENDER
    if (fenix2frame_sender_ptr != nullptr)
    {
        bool ok_quit = fenix2frame_sender_ptr->stop();
        if (ok_quit)
        {
            cout << "fenix2frame_sender_ptr->stop()" << endl;
        } // END if (ok_quit)
        else
        {
            cout << "error::fenix2frame_sender_ptr->stop()" << endl;
        } // END else
    } // END if (fenix2frame_sender_ptr != nullptr)

#endif // DBG_VIDEO_SENDER

    cout << " --- END Application::quit" << endl;
} // -- END quit

void Application::stop()
{
    cout << "Application::stop()\n";
    need_quit = true;
}  // -- END stop()

bool Application::quit_async()
{
    /*
        Проверка на предмет раннего вызова метода quit() или quit_async();
        Для гарантии безопасного выхода требуется
        обеспечить возможность только единократного вызова quit() или quit_async()
    */
    if(_quit_async_was_called.load() || quit_was_called.load()){return true;}

    _quit_async_was_called.store(true);
    cout << "BEGIN quit_async()" << endl;
    _execute.store(false);
    // Максимально допустимое время ожидания закрытия основного цикла приложения
    // При превышении приложение закрывается не дожидаясь закрытия потока функции exec()ж
    const int watchdog_close_exec_time_ms = 3000;
    // Общее количество отсчетов, которое выполняется
    const int subdivisions_total = 100;
    // Временной интервал проверки состояния потока метода exec() за предмет завершенности (закрытости)
    int check_interval_ms = 1;
    
    // Проверки безопасности введенных пользовательских значений watchdog_close_exec_time_ms и subdivisions_total
    if(subdivisions_total > 0){check_interval_ms = watchdog_close_exec_time_ms / subdivisions_total;}
    if(check_interval_ms <= 0){check_interval_ms = 1;}

    cout << "\t watchdog_close_exec_time_ms = " << watchdog_close_exec_time_ms << endl;
    cout << "\t subdivisions_total = " << subdivisions_total << endl;
    cout << "\t check_interval_ms = " << check_interval_ms << endl;
    bool success_close_exec = false;
    for(int i = 0; i < subdivisions_total; ++i)
    {
        if(_exec_complete_success.load())
        {
            cout << "\tSuccess close exec(), total wait time = " << i * check_interval_ms << " (ms)" << endl;
            success_close_exec = true;
            break;
        } // END if(_exec_complete_success.load())
        this_thread::sleep_for(milliseconds(check_interval_ms));
    } // END for(int i = 0; i < subdivisions_total; ++i)

    if(!success_close_exec){cout << "Error close exec()!" << endl;}
    quit();
    _quit_async_complete.store(true);
    cout << "END quit_async()" << endl;
    return success_close_exec;
} // -- END quit_async

void Application::start()
{
    device->start();
    _execute.store(true, memory_order_release);
    exec();
} // -- END start




void Application::exec()
{
    bool ok = false;
    int counter = 0;
    cout << "Application::exec START" << endl;
    if(parallel)
    {
        while(!frameReady.load())
        {
            this_thread::sleep_for(milliseconds(1));
        } // END while(!frameReady.load())
    } // END if(parallel)
    else
    {
        if(!device->getFirstFrame(frame_process_0)){quit();}
        frameReady.store(true);
    } // END if(!parallel)

    frame_w = frame_process_0.cols;
    frame_h = frame_process_0.rows;
    frame_w_1 = 1.f / (float)frame_w;
    frame_h_1 = 1.f / (float)frame_h;

    cout << "exec:: frame size : frame_w = " << frame_w << "; frame_h = " << frame_h << endl;
    show2originImgRatio = (float)frame_show_width / frame_w;
    orig2show = 1.f / show2originImgRatio;
    zahvat_size = round(zahvat_size * show2originImgRatio);
    wh_2_zahvat = Point2i(zahvat_size, zahvat_size);

    frame_h_w = (float)frame_h/frame_w;
    frame_show_height = round(frame_h_w * frame_show_width);
    frame_show_width_2 = 0.5 * frame_show_width;
    frame_show_height_2 = 0.5 * frame_show_height;
    frame_show_w_1 = 1.f / frame_show_width;
    frame_show_h_1 = 1.f / frame_show_height;
    rct_center.height = round(frame_h_w * rct_center.width);
    // основной цикл выполнения пиложения
    while(_execute.load(memory_order_acquire))
    {
        if(!parallel)
        {
#ifdef USE_LOGGER
            time_point_device0 = high_resolution_clock::now();
#endif // END USE_LOGGER

#ifdef USE_ROI_TMP
            device->getFrame(frame_receive0);
            resize(frame_receive0(rct_center), frame_receive, Size(frame_w, frame_h));
#endif // END USE_ROI_TMP
#ifndef USE_ROI_TMP
            device->getFrame(frame_receive);
#endif // END NOT USE_ROI_TMP

#ifdef USE_LOGGER
            time_point_device1 = high_resolution_clock::now();
            LoggerArtem::inst().logTimedBasedFPS(
                        "Device FPS = ",
                        duration<double>(time_point_device1 - time_point_device0).count());
#endif // END USE_LOGGER
            frameReady.store(true);
        } // END if(!parallel)

        if(frameReady.load())
        {
            if(parallel) // TODO: паттерн "стратегия" с назначением lambda
            {
                /*
                Обособленный mutex'ом фрагмент не осуществляет клонирования frame,
                реализуется оптимальная передача по ссылке,
                но дополнительная потокобезопасность обеспечивается
                frame_proc_(0/1)_mutex без существенных накладных расходов
                */
                switch(process_frame_id) // id буффера на предыдущем шаге
                {
                case 0:
                {
                    frame_proc_1_mutex.lock();
                    process_frame_id = 1;
                    frame_receive = frame_process_1;
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
                    throw runtime_error("Error: incorrect process_frame_id");
                } // END default:
                    break;
                } // END switch(process_frame_id)
            } // -- END if(parallel)

            frameReady.store(false);

#ifdef GUI_OK
            putText(frame_receive, to_string(counter), Point(640,500), 1, 30, Scalar(255,0,255), 10);
            counter++;
            resize(frame_receive, frame_show, Size(frame_show_width, frame_receive.rows * show2originImgRatio));
            if(cross_on)
            {
                line(frame_show, Point(0, frame_show_height_2), Point(frame_show_width, frame_show_height_2), cross_on_color, 2);
                line(frame_show, Point(frame_show_width_2, 0), Point(frame_show_width_2, frame_show_height), cross_on_color, 2);
            } // END cross_on
#endif //GUI_OK


#ifdef USE_CORSAIR_400_RAW
            // "Заправляем" найденные рамки в структуру
            track_pos_data2send.v_track.resize(0);
#if defined(TKDNN)
            vector<trac_data>& vtd = tracShats->trac_str.vtrac_data;
            for(int i = 0; i < vtd.size(); i++)
            {
                trac_data& td = vtd[i];
                tr_pos.x = td.x;
                tr_pos.y = td.y;
                tr_pos.w = td.w;
                tr_pos.h = td.h;
                track_pos_data2send.v_track.emplace_back(tr_pos);
            } // END for(int i = 0; i < MIN(v_track_size_real, v_track_size_udp); i++)
#endif // END #if defined(TKDNN)
#if !defined(TKDNN)
            if(flag_zahvat)
            {
                tr_pos.x = aimRectShats.x;
                tr_pos.y = aimRectShats.y;
                tr_pos.w = aimRectShats.width;
                tr_pos.h = aimRectShats.height;
                track_pos_data2send.v_track.emplace_back(tr_pos);
            } // END if(flag_zahvat)
#endif // END #if !defined(TKDNN)
            sender_ptr->send(track_pos_data2send);
#endif // USE_CORSAIR_400_RAW


#ifdef DBG_VIDEO_SENDER
            fenix2frame_sender_ptr->setMeta(fenix2meta_data2send);
            cv::Mat frame_send = frame_receive;
            // resize(frame_receive, frame_send, Size(frame_send_w, frame_send_h));
            fenix2frame_sender_ptr->newFrame(frame_send.data,
                                             frame_send.cols * frame_send.rows * frame_send.channels());
#endif // DBG_VIDEO_SENDER

            mouseHandler(frame_show, rectm);
            cvtColor(frame_receive, frame_send, COLOR_BGR2BGR565);
            rtspsrv::set_image(frame_send);

            if(need_quit)
            {
                cout << "need quit" << endl;
                quit();
                break;
            } // END if(need_quit)
        } // END if(frameReady.load())
        else
        {
            bool ws_ok1 = false;
            bool need_brake_quit = false;
            while(!frameReady.load())
            {
                if(parallel)
                {
                    this_thread::sleep_for(milliseconds(5));
                } // -- END if(!parallel)
                else
                {
                    break;
                } // END if(!parallel)
            } // -- END while(!frameReady.load())
        } // -- END if(!frameReady.load())
    } // -- END while(_execute.load(memory_order_acquire))

    cout << "Complete Application::exec()" << endl;
    _exec_complete_success.store(true);
    this_thread::sleep_for(milliseconds(10));
    bool success_wait_quit_async_complete = false; // флаг успешного завершения работы метода quit_async()
    if(_quit_async_was_called.load())
    {
        for(int i = 0; i < 100; ++i)
        {
            if(_quit_async_complete.load())
            {
                success_wait_quit_async_complete = true;
                cout << "_quit_async_complete detected <<true>>" << endl;
                this_thread::sleep_for(milliseconds(20));
                break;
            } // if(_quit_async_complete.load())
        } // END for(int i = 0; i < 100; ++i)
    } // END if(_quit_async_complete.load())
    cout << "END exec" << endl;
} // -- END exec

bool Application::get_ini_params(const string &config)
{
    cout << "BEGIN get_ini_params Application" << endl;
    setlocale(LC_NUMERIC, "en_US.UTF-8");

#ifdef USE_FILESYSTEM
    bool configFileExists = filesystem::exists(config);
#else
    bool configFileExists = FileIsExist(config);
#endif
    if(!configFileExists)
    {
        cout << "Config file '" << config << "' not exist!" << endl;
        return 0;
    } // END if(!configFileExists)
    INIReader reader(config);
    if(reader.ParseError() < 0)
    {
        cout << "Can't load '" << config << "'\n";
        return 0;
    } // END if(reader.ParseError() < 0)

    parallel =  reader.GetBoolean("main_settings", "parallel", false);
    cout << "parallel = " << parallel << ";\n";

    device_id = reader.GetInteger("main_settings", "device_id", -1);
    if(device_id == -1)
    {
        cout << "device_id not declared!\n";
        return 0;
    } // END if(device_id == -1)
    cout << "device_id = " << device_id << ";\n";


#ifdef USE_CORSAIR_400_RAW
    int handle_flag_buf = reader.GetInteger("main_settings", "handle_flag", -1);
    if(!handle_flag_buf) {handle_flag = 0;}
    else
    {
        handle_flag = 1;
    } // END if(handle_flag_buf)

#else
    handle_flag = 1;
#endif // USE_CORSAIR_400_RAW
    cout << "handle_flag = " << handle_flag << endl;

    zahvat_size = reader.GetInteger("tracking", "zahvat_size", -1);
    if(zahvat_size == -1)
    {
        cout << "Not found zahvat_size in Application::getMainSettings!\n";
        return false;
    } // END if(zahvat_size == -1)
    wh_2_zahvat = Point2i(zahvat_size, zahvat_size);

    frame_show_width = reader.GetInteger("demonstration_settings", "frame_show_width", -1);
    if(frame_show_width == -1)
    {
        cout << "Not found width in Application::getMainSettings!\n";
        return false;
    } // END if(frame_show_width == -1)

    demonstration_mode = reader.GetInteger("demonstration_settings", "demonstration_mode", -1);
    if(demonstration_mode == -1)
    {
        cout << "Not found mode in Application::getMainSettings!\n";
        return false;
    } // END if(demonstration_mode == -1)


    video_on = reader.GetInteger("recorder", "video_on", -1);
    if(video_on == -1)
    {
        cout << "Not found video_on in Application::getMainSettings!\n";
        return false;
    } // END if(video_on == -1)
    else if(video_on == 1)
    {
        path4frames = reader.Get("recorder", "path4frames", "oops");
        if(path4frames == "oops")
        {
            cout << "Not found path4frames in Application::getMainSettings!\n";
            return false;
        } // END if(path4frames == "oops")

        save_frames_skip = reader.GetInteger("recorder", "save_frames_skip", -1);
        if(save_frames_skip == -1)
        {
            cout << "Not found save_frames_skip in Application::getMainSettings!\n";
            return false;
        } // END  if(save_frames_skip == -1)

        save_frames_prefix = reader.GetInteger("recorder", "save_frames_prefix", -1);
        if(save_frames_prefix == -1)
        {
            cout << "Not found save_frames_prefix in Application::getMainSettings!\n";
            return false;
        } // END if(save_frames_prefix == -1)

        max_frames = reader.GetInteger("recorder", "max_frames", -1);
        if(max_frames == -1)
        {
            cout << "Not found max_frames in Application::getMainSettings!\n";
            return false;
        } // END if(max_frames == -1)
    } // END else if(video_on == 1)

    cout << "END get_ini_params Application" << endl;
    return 1;
} // -- END get_ini_params


#ifdef GUI_OK
void Application::aimFrameCallback(int event, int x, int y, int flags, void *param)
{
    Point *p = reinterpret_cast<Point*>(param);
    p->x = x;
    p->y = y;
    p_mouse = Point(x, y);
    switch(event)
    {
    case EVENT_LBUTTONDOWN:
        click_down = 1;
        break;
    case EVENT_LBUTTONUP:
        if(click_down){click_up = 1;}
        break;
    } // -- END switch(event)
} // -- END aimFrameCallback
#endif // END GUI_OK


#if defined(USE_CORSAIR_400_RAW)
bool Application::ethHandler(cv::Rect2f & rect_obj)
{
    cmd_keeper_ptr->get(cmd_list2keep);
    if(cmd_list2keep.record_switch_f)
    {
        if(rec_on)
        {
#ifdef USE_CORSAIR_400_RAW
            app_state.state = 4;
            sender_ptr->send(app_state);
#endif // END USE_CORSAIR_400_RAW
            rec_on = 0;
        } // END if(rec_on)
        else if(video_on)
        {
#ifdef USE_CORSAIR_400_RAW
            app_state.state = 3;
            sender_ptr->send(app_state);
#endif // END USE_CORSAIR_400_RAW
            rec_on = 1;
        } // END else if(video_on)
        cmd_list2keep.record_switch_f = 0;
    } // END if(cmd_list2keep.record_switch_f)
    return 0;
} // -- END ethHandler
#endif // END USE_CORSAIR_400_RAW


#ifdef GUI_OK
bool Application::mouseHandler(Mat& img, Rect2f& object_rect)
{
    if(handle_flag)
    {
#if !defined(TKDNN)
        if(!isTracShatsInitedFlag)
        {
            if(click_down)
            {
                if(zahvat_size)
                {
                    if(first_click_down)
                    {
                        first_click_down = 0;
                        p_down = p_mouse;
                    } // -- END if(first_click_down)
                    Rect rct(p_mouse - wh_2_zahvat, p_mouse + wh_2_zahvat);
                    rectangle(img, rct, color::white, 1);
                } // END if(zahvat_size)
                else
                {
                    if(first_click_down)
                    {
                        first_click_down = 0;
                        p_down = p_mouse;
                    } // -- END if(first_click_down)
                    int left  = MIN(p_mouse.x, p_down.x);
                    int right = MAX(p_mouse.x, p_down.x);
                    int top   = MIN(p_mouse.y, p_down.y);
                    int down  = MAX(p_mouse.y, p_down.y);
                    Rect rct(Point(left, top), Point(right, down));
                    rectangle(img, rct, color::white, 1);
                } // END if(!zahvat_size)
            } //--END if(click_down)
        } // -- END if(!isTracShatsInitedFlag)
#endif // END #if !defined(TKDNN)
    } // END if(handle_flag)
    if(rec_on){circle(img, Point(30, 60), 10, color::white, -1);}
    imshow(app_win_name, img);
    //moveWindow(win_name, 10, 10);
    key = waitKey(1);
    if(handle_flag)
    {
        keyHandler();
        device->keyHandler(key);
        if(key == '`'){need_quit = 1; return 0;}

#if !defined(TKDNN)
        if(!isTracShatsInitedFlag)
        {
            setMouseCallback(app_win_name, aimFrameCallback, &p_mouse);
            if(click_up)
            {
                if(zahvat_size)
                {
                    click_up = 0;
                    click_down = 0;
                    first_click_down = 1;
                    object_rect = Rect(p_mouse - wh_2_zahvat, p_mouse + wh_2_zahvat);
                    return true;
                } // END if(zahvat_size)
                else
                {
                    click_up = 0;
                    int left  = MIN(p_mouse.x, p_down.x);
                    int right = MAX(p_mouse.x, p_down.x);
                    int top   = MIN(p_mouse.y, p_down.y);
                    int down  = MAX(p_mouse.y, p_down.y);
                    Rect rct(Point(left, top), Point(right, down));
                    if(rct.area() > 0)
                    {
                        click_down = 0;
                        first_click_down = 1;
                        object_rect = rct;
                        return true;
                    } // -- END if(rct.area()>0)
                } // END if(!zahvat_size)
            } //--END if(click_up)
        } // -- END if(!isTracShatsInitedFlag)
#endif // END  #if !defined(TKDNN)
    } // END  if(handle_flag)
    return false;
} // -- END mouseHandler
#endif // GUI_OK

#ifdef GUI_OK
void Application::keyHandler()
{
    switch(key)
    {
    case 's': // включение/выключение записи
    {
        if(rec_on)
        {
            rec_on = 0;
            break;
        } // END if(rec_on)
        else if(video_on)
        {
            rec_on = 1;
            break;
        } // END else if(video_on)
    } // case 's':

    case 27: // деинциализация трекера по клавише ESC
    {
        break;
    } // END case 27
    case '`':       // выход из программы по клавише '`'.
    {
        cout << "Exit on keypress" << endl;
        break;
    } // END case '`'
    default:
    {
        break;
    } // END default
    } // -- END switch(key)
} // -- END keyHandler
#endif // END GUI_OK


void Application::handleDeviceFrame(uint8_t *f, int w, int h, int num, int id)
{
    static auto prevFrameReceiveTime = high_resolution_clock::now();
    auto receiveTime = high_resolution_clock::now();

#ifdef USE_LOGGER
    LoggerArtem::inst().logTimedBasedFPS(
                "Device FPS = ",
                duration<double>(receiveTime - prevFrameReceiveTime).count());
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
        throw runtime_error("Error: not recognize/supported color channel mode");
#endif
        frame_proc_0_mutex.lock();
        frame_process_0 = Mat(Size(w,h), cvmat_type);
        device->getFormatedImage(f, w, h, id, frame_process_0);
        frame_proc_0_mutex.unlock();

        frame_proc_1_mutex.lock();
        frame_process_1 = frame_process_0.clone();
        frame_proc_1_mutex.unlock();

        first_frame = false;
        frameReady.store(true);
    } // END if(first_frame)
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
            throw runtime_error("Error: incorrect process_frame_id");
            break;
        } // END switch(process_frame_id)
        frameReady.store(true);
    } // -- END if(!frameReady.load())
} // -- END handleDeviceFrame
