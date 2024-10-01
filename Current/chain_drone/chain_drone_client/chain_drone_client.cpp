#include "chain_drone_client.hpp"

using namespace std;
using namespace cv;



namespace chain_drone_cli
{

bool EthKeeper::click_down = 0;
bool EthKeeper::click_up = 0;
cv::Point2f EthKeeper::p_mouse(0, 0);
cv::Point2f EthKeeper::p_down(0, 0);



EthKeeper::EthKeeper(std::string path2setting, bool & ok)
{
    path2ini = path2setting;
    cout << "Size of telemetry packet is " << sizeof(meta_fenix2keep_folder) << endl;
    ok = get_ini_params(path2ini, rtp_client_ini_section);
    frame_w_1 = 1.f / (float)frame_w;
    frame_h_1 = 1.f / (float)frame_h;
#ifdef GST_CVAPI


    std::cout << " ------ BEGIN create frame_mjpg_eth_controller" << std::endl;
    frame_mjpg_eth_controller = rtp_eth::controller_V1::create(path2ini, "gstcv_mjpg_eth_controller");
    ok = frame_mjpg_eth_controller->launch();
    if (!ok)
    {
        std::cout << "ERROR: launch frame_mjpg_eth_controller!" << std::endl;
    } // if (!ok)
    else
    {
        std::cout << " ------ END create frame_mjpg_eth_controller" << std::endl;
    } // END else

    std::cout << " ------ BEGIN create fenix2meta_keeper_ptr" << std::endl;
    fenix2meta_keeper_ptr = fenix2meta_keeper::create(path2ini, section_fenix2meta_keeper);
    if(fenix2meta_keeper_ptr == nullptr)
    {
        std::cout << "ERROR create fenix2meta_keeper_ptr!" << std::endl;
        ok = false;
        return;
    } // END if(trackmeta_keeper == nullptr)
    std::cout << " ------ END create fenix2meta_keeper_ptr" << std::endl;

    fenix2meta_keeper_ptr->set_log_mode(fenix2meta_keeper::LOG_MODE_ON_ORIENT_ONLY);
    if(!fenix2meta_keeper_ptr->setup())
    {
        std::cout << "ERROR setup fenix2meta_keeper_ptr!" << std::endl;
        ok = false;
        return;
    } // END if(!trackmeta_keeper->start())
#endif // GST_CVAPI


#ifdef GST_CAPI_H264
    std::cout << " ------ BEGIN create frame_keeper_ptr" << std::endl;
    settings = std::make_shared<rtp::client::h264::Settings>();
    ok = rtp::client::h264::getIniSettings(path2ini, "gstc_rtp_client_h264", *settings);
    if (!ok)
    {
        cout << "ERROR: Application::rtp::client::getIniSettings!" << endl;
        return;
    }
    frame_keeper_ptr = make_shared<rtp::RtpClientH264>(settings);
#endif // END GST_CAPI_H264
#ifdef GST_CAPI_H265
    std::cout << " ------ BEGIN create frame_keeper_ptr" << std::endl;
    settings = std::make_shared<rtp::client::h265::Settings>();
    ok = rtp::client::h265::getIniSettings(path2ini, "gstc_rtp_client_h265", *settings);
    if (!ok)
    {
        cout << "ERROR: Application::rtp::client::getIniSettings!" << endl;
        return;
    }
    frame_keeper_ptr = make_shared<rtp::RtpClientH265>(settings);
#endif // END GST_CAPI_H265
#ifdef GST_CAPI_MJPEG
    std::cout << " ------ BEGIN create frame_keeper_ptr" << std::endl;
    settings = std::make_shared<rtp::client::mjpeg::Settings>();
    ok = rtp::client::mjpeg::getIniSettings(path2ini, "gstc_rtp_client_mjpeg", *settings);
    if (!ok)
    {
        cout << "ERROR: Application::rtp::client::getIniSettings!" << endl;
        return;
    }
    frame_keeper_ptr = make_shared<rtp::RtpClientMJPEG>(settings);
#endif // GST_CAPI_MJPEG
#ifdef GST_CAPI_RAW
    std::cout << " ------ BEGIN create frame_keeper_ptr" << std::endl;
    settings = std::make_shared<rtp::client::raw::Settings>();
    ok = rtp::client::raw::getIniSettings(path2ini, "gstc_rtp_client_raw", *settings);
    if (!ok)
    {
        cout << "ERROR: Application::rtp::client::getIniSettings!" << endl;
        return;
    }
    frame_keeper_ptr = make_shared<rtp::RtpClientRAW>(settings);
#endif // GST_CAPI_RAW

#if defined(GST_CAPI_H264) || defined(GST_CAPI_H265) || defined(GST_CAPI_MJPEG) || defined(GST_CAPI_RAW)

    ok = frame_keeper_ptr->setup();
    if(!ok)
    {
        std::cout << "ERROR setup frame_keeper_ptr->setup()!" << std::endl;
        ok = false;
        return;
    } // END if(!frame_keeper_ptr->start())
    if(!frame_keeper_ptr->start())
    {
        std::cout << "ERROR start frame_keeper_ptr!" << std::endl;
        ok = false;
        return;
    } // END if(!frame_keeper_ptr->start())
    std::cout << " ------ END create frame_keeper_ptr" << std::endl;
#endif // GST_CAPI

#ifdef USE_TCP_SETUP
    cout << " ------ BEGIN create tcp_client_ptr" << endl;
    tcp_client_ptr = eth_controller::cmd::async::client_simplex::create(path2ini, section2tcp_cmd_keeper);
    if (!tcp_client_ptr->setup(setup_info_from_server))
    {
        std::cout << "ERROR setup tcp_client_ptr!" << std::endl;
        ok = false;
        return;
    } // END if (!tcp_client_ptr.setup())
    cout << " ------ END create tcp_client_ptr" << endl;
#endif //USE_TCP_SETUP

    std::cout << " ------ BEGIN create fenix2cmd_sender_ptr" << std::endl;
    fenix2cmd_sender_ptr = fenix2cmd_sender::create(path2ini, section2cmd_sender);
    if(!fenix2cmd_sender_ptr->start())
    {
        cout << "Application::ERROR start fenix2cmd_sender_ptr!" << endl;
        ok = false;
        return;
    } // END if(!fenix2cmd_sender_ptr->start())
    std::cout << " ------ END create fenix2cmd_sender_ptr" << std::endl;

    if (settings->video.format == "BGR")
    {
        img2keep = cv::Mat(Size(frame_w, frame_h), CV_8UC3, Scalar(0,0,0));
    }
    if (settings->video.format == "GRAY8")
    {
        img2keep = cv::Mat(Size(frame_w, frame_h), CV_8UC1, Scalar(0));
    }
    namedWindow(winname, WINDOW_NORMAL);
    moveWindow(winname, 0, 0);
    imshow(winname, img2keep);

    pt_frame_center = cv::Point2f(round(img2keep.cols * 0.5f), round(img2keep.rows * 0.5f));
    img_work = Mat(Size(frame_w, frame_h), CV_8UC3, Scalar(0,0,0));
    img_show = Mat(Size(img_work.cols * (monitor_format), img_work.rows), img_work.type(), Scalar(255,255,255));
    pt_center = 0.5 * cv::Point(frame_w, frame_h);
    tmp_show_w = img_show.cols - img_work.cols - 2 * tmp_show_bord - 1;
    mat_poweroff = imread("../poweroff.jpg");
    cv::Mat dis2multiply = cv::Mat(mat_poweroff.size(), CV_32FC3, Scalar(0.5,0.5,0.5));
    mat_poweroff_disable = mat_poweroff.clone();
    mat_poweroff_disable += Scalar(200,200,200);
    multiply(mat_poweroff_disable, 0.75, mat_poweroff_disable);
    rct_poweroff = {frame_w + int((img_show.cols - frame_w - mat_poweroff.cols) * 0.5),
                    frame_h - str_h.y - mat_poweroff.rows,
                    mat_poweroff.cols,
                    mat_poweroff.rows};
    if (tmp_show_w > max_w_rct_aim) {tmp_show_w = max_w_rct_aim;}
    str_h = Point(0, round(fontscale * 30.f));
    str_pos0 = Point(frame_w + tmp_show_bord, tmp_show_bord + str_h.y);
    tmp_rect = Rect(Point(frame_w + tmp_show_bord, tmp_show_bord + 2 * str_h.y),Size(tmp_show_w,tmp_show_w));
    rct_work = {0, 0, frame_w, frame_h};

    /// confirm image
    sz_confirm  = Point(img_show.cols - frame_w - 2 * tmp_show_bord, 0.1 * frame_w);
    rct_confirm = Rect(frame_w + tmp_show_bord,
                       frame_h - str_h.y - mat_poweroff.rows - 2 * tmp_show_bord - sz_confirm.y,
                       sz_confirm.x,
                       sz_confirm.y);
    btn_c = 0.5 * sz_confirm;
    string yes_no_str = "space - yes     /    esc - no";
    Point yes_no_pos = btn_c -  Point(fontscale * yes_no_str.size() * 0.25 * str_h.y, - 2 * str_h.y);

    mat_confirm_deinit = cv::Mat(sz_confirm, img_show.type(), color::white);
    std::string confirm_str_deinit = "Are you shure deinit tracker?";
    Point str_pos_deinit = btn_c -  Point(fontscale * confirm_str_deinit.size() * 0.25 * str_h.y, str_h.y);
    putText(mat_confirm_deinit, confirm_str_deinit, str_pos_deinit, font, fontscale, color::black, fontthic);
    putText(mat_confirm_deinit, yes_no_str, yes_no_pos, font, fontscale, color::black, fontthic);

    mat_confirm_poweroff = cv::Mat(sz_confirm, img_show.type(), color::white);
    std::string confirm_str_poweroff = "Are you shure poweroff server?";
    Point str_pos_poweroff = btn_c -  Point(fontscale * confirm_str_poweroff.size() * 0.25 * str_h.y, str_h.y);
    putText(mat_confirm_poweroff, confirm_str_poweroff, str_pos_poweroff, font, fontscale, color::black, fontthic);
    putText(mat_confirm_poweroff, yes_no_str, yes_no_pos, font, fontscale, color::black, fontthic);
    /// mouse_position_controll
    //    Display *dpy;
    dpy = XOpenDisplay(0);
    root_window = XRootWindow(dpy, 0);
    XSelectInput(dpy, root_window, KeyReleaseMask);


#ifdef USE_SPEAKER
    ///init device
    std::string cmd_set_device = "pactl set-default-sink " + speaker_device;
    if (system(cmd_set_device.c_str()) == -1)
    {cout << "error::init_speaker_device!\n";};
    ///set_volume
    string cmd_set_volume = "pactl set-sink-volume " + speaker_device + " " + to_string(speaker_volume) + "%";
    if(system(cmd_set_volume.c_str())==-1) {cout << "error::set volume!\n";};
    std::thread thr_sound(&EthKeeper::f_sound, this, 2);
    thr_sound.detach();
#endif // USE_SPEAKER
    std::thread thr_check_connection(&EthKeeper::check_connection, this);
    thr_check_connection.detach();

    cout << "dbg:: str_pos0 = " << str_pos0 << endl;
    cout << "dbg:: tmp_show_w = " << tmp_show_w << endl;
    cout << "dbg:: tmp_rect = " << tmp_rect << endl;

    std::cout << "END EthKeeper CONSTRUCTOR!" << std::endl;

}; // END EthKeeper

bool EthKeeper::get_ini_params(const std::string& config, const std::string & ini_section_name)
{
    cout << "BEGIN get_ini_params Application" << endl;
    setlocale(LC_NUMERIC, "en_US.UTF-8");
    bool configFileExists = FileIsExist(config);
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
    bool ok = true;

    using namespace toolbox_utils::ini_reader_tool;
    cout << "       [" << ini_section_name << "]:" << endl;
    ok &= GetInteger(reader, ini_section_name, "video_width", frame_w);
    ok &= GetInteger(reader, ini_section_name, "video_height", frame_h);
    int max_time_buf = 0;
    ok &= GetInteger(reader, handler_ini_section, "max_time2disconnect", max_time_buf);
    max_time2disconnect = std::chrono::milliseconds(max_time_buf);

    cout << "       [" << handler_ini_section << "]:" << endl;
    string str_key_track_size_up, str_key_track_size_down, std_key_quit_client;
    ok &= Get(reader, handler_ini_section, "key_track_size_up", str_key_track_size_up);
    ok &= Get(reader, handler_ini_section, "key_track_size_down", str_key_track_size_down);
    ok &= Get(reader, handler_ini_section, "key_track_size_down", str_key_track_size_down);
    ok &= Get(reader, handler_ini_section, "key_quit_client", std_key_quit_client);

#ifdef USE_SPEAKER
    ok &= Get(reader, speaker_ini_section, "device", speaker_device);
    ok &= Get(reader, speaker_ini_section, "sound", speaker_sound);
    ok &= Get(reader, speaker_ini_section, "sound1", speaker_sound1);
    ok &= GetInteger(reader, speaker_ini_section, "volume", speaker_volume);
    ok &= GetInteger(reader, speaker_ini_section, "num_sound_warning", num_sound_warning);
    ok &= GetInteger(reader, speaker_ini_section, "pause_fall", pause_fall);
    ok &= GetInteger(reader, speaker_ini_section, "pause_handler", pause_handler);
#endif // USE_SPEAKER
    key_track_size_up = str_key_track_size_up.at(0);
    key_track_size_down = str_key_track_size_down.at(0);
    key_quit_client = std_key_quit_client.at(0);
    return ok;
} // -- END get_ini_params

bool EthKeeper::FileIsExist(const string& filePath)
{
    bool isExist = false;
    std::ifstream fin(filePath.c_str());
    if(fin.is_open()){isExist = true;}
    fin.close();
    return isExist;
} // -- END FileIsExist



void EthKeeper::aimFrameCallback(int event, int x, int y, int flags, void *param)
{
    cv::Point *p = reinterpret_cast<cv::Point*>(param);
    p->x = x;
    p->y = y;
    p_mouse = cv::Point(x, y);
    switch(event)
    {
    case cv::EVENT_LBUTTONDOWN:
        //        cout << "   ======= EVENT_LBUTTONDOWN =======" << endl;
        click_down = 1;
        break;
    case cv::EVENT_LBUTTONUP:
        //        cout << "   ======= EVENT_LBUTTONUP =======" << endl;
        if(click_down)
        {
            click_up = 1;
        } // END if(click_down)
        break;
    } // -- END switch(event)
} // -- END aimFrameCallback


bool EthKeeper::confirm_handler()
{

    if(confirm_deinit_request || confirm_poweroff_srv_request)
    {
        if (confirm_deinit_request)
        {
            mat_confirm_deinit.copyTo(img_show(rct_confirm));
        } // END if (confirm_deinit_request)
        if (confirm_poweroff_srv_request)
        {
            mat_confirm_poweroff.copyTo(img_show(rct_confirm));
        } // END if (confirm_poweroff_srv_request)
        rectangle(img_show, rct_confirm, color::red, 5);
        uchar confirm_key = waitKey(50);
        if (confirm_key == 32)
        {
            cout << "YES" << endl;
            key = '0';
            mouse2center();
            if (confirm_deinit_request)
            {
                fenix2cmd_to_send.deinit_track = 1;
                fenix2cmd_to_send.mode_mouse = 1;
                circle_status = 0;
#ifdef TKDNN
                square_status = 1;
#elif // (!TKDNN)
                square_status = 0;
#endif // TKDNN
                confirm_deinit_request = 0;
                flag_space2confirm = 1;
            } // END if (confirm_deinit_request)
            else if (confirm_poweroff_srv_request)
            {
                fenix2cmd_to_send.poweroff_srv = 1;
                confirm_poweroff_srv_request = 0;
            } // END if (confirm_poweroff_srv_request)
            confirm_handler_status = 0;
            return true;
        } // END if (confirm_key == 32)
        else if (confirm_key == 27)
        {
            cout << "NO" << endl;
            key = '0';
            mouse2center();
            confirm_poweroff_srv_request = 0;
            confirm_deinit_request = 0;
            return true;
        } // END if (confirm_key == 27)
        return false;
    } // END if(confirm_handler_status)
    return true;
} // END confirm_handler

#ifdef USE_SPEAKER
void EthKeeper::f_sound(int num)
{
    while(!need_quit)
    {
        if(track_fall)
            if (system(speaker_sound.c_str()) == -1)
            {
                cout << "error::speaker:: " << speaker_sound << endl;
            } // END if (system(sound.c_str()) == -1)
        if(disconnect)
        {
            if (system(speaker_sound.c_str()))
            {
                cout << "error::speaker:: " << speaker_sound << endl;
            } // END if (system(sound.c_str()) == -1)
            std::this_thread::sleep_for(std::chrono::milliseconds(pause_disconnect));
            if (system(speaker_sound.c_str()))
            {
                cout << "error::speaker:: " << speaker_sound << endl;
            } // END if (system(sound.c_str()) == -1)
            std::this_thread::sleep_for(std::chrono::milliseconds(pause_disconnect));
            if (system(speaker_sound.c_str()))
            {
                cout << "error::speaker:: " << speaker_sound << endl;
            } // END if (system(sound.c_str()) == -1)
            std::this_thread::sleep_for(std::chrono::milliseconds(pause_disconnect));
        } // END if(disconnect)
        std::this_thread::sleep_for(std::chrono::milliseconds(pause));
    } // END while(true)
    return;
} // -- END f_sound
#endif // USE_SPEAKER

void EthKeeper::check_connection()
{
    tp_check_connection0 = chrono::system_clock::now();
    tp_check_connection1 = chrono::system_clock::now();
    while(true)
    {
        if(!ok_connect)
        {
            tp_check_connection1 = chrono::system_clock::now();
            disconnect_time += (tp_check_connection1 - tp_check_connection0);
            tp_check_connection0 = tp_check_connection1;
        } // END if(!ok_connect)
        else
        {
            disconnect_time = chrono::system_clock::duration::zero();
        } // end else
        if (disconnect_time > max_time2disconnect)
        {
            disconnect = 1;
            track_fall = 0;
#ifdef USE_SPEAKER
            pause = pause_handler;
#endif // USE_SPEAKER
        } // END if (disconnect_time > max_time2disconnect)
        else
        {
            disconnect = 0;
        } // END if (disconnect_time <= max_time2disconnect)
    } // END while(true)
} // -- END check_connection

bool EthKeeper::quit()
{
    bool ok_quit = 0;
    if (fenix2cmd_sender_ptr != nullptr)
    {
        ok_quit = fenix2cmd_sender_ptr->quit();
        if (!ok_quit) {cout << "error::fenix2client:: fenix2cmd_sender_ptr not quit!" << endl;}
    } // END if (fenix2cmd_sender_ptr != nullptr)

#ifdef GST_CAPI
    if (frame_keeper_ptr != nullptr)
    {
        ok_quit = frame_keeper_ptr->stop();
        if (!ok_quit) {cout << "error::RtpClient:: frame_keeper_ptr not quit!" << endl;}
    }
#endif // GST_CAPI
    return 1;
} // -- END quit


void EthKeeper::printKeepData()
{
    cout << "dbg:: meta_fenix2keep_folder:" << endl
         << "   num_frame:       " << meta_fenix2keep_folder.num_frame << endl
         << "   time_delay_mcs:  " << meta_fenix2keep_folder.time_delay_mcs << endl
         << "   track_is_init:   " << meta_fenix2keep_folder.track_is_init << endl
         << "   gpu_type:         " << meta_fenix2keep_folder.gpu_type << endl
         << "   device:         " << meta_fenix2keep_folder.device << endl
         << "   trackx:          " << meta_fenix2keep_folder.trackx << endl
         << "   tracky:          " << meta_fenix2keep_folder.tracky << endl
         << "   new_trackw:      " << meta_fenix2keep_folder.new_trackw << endl
         << "   new_trackh:      " << meta_fenix2keep_folder.new_trackh << endl
         << "   trackw:          " << meta_fenix2keep_folder.trackw << endl
         << "   trackh:          " << meta_fenix2keep_folder.trackh << endl
         << "   diff_trackx:     " << meta_fenix2keep_folder.diff_trackx << endl
         << "   diff_tracky:     " << meta_fenix2keep_folder.diff_tracky << endl
         << "   x_m_s:           " << meta_fenix2keep_folder.x_m_s << endl
         << "   y_m_s:           " << meta_fenix2keep_folder.y_m_s << endl
         << "   x_m_ss:          " << meta_fenix2keep_folder.x_m_ss << endl
         << "   y_m_ss:          " << meta_fenix2keep_folder.y_m_ss << endl
         << "   roll_deg:        " << meta_fenix2keep_folder.roll_deg << endl
         << "   pitch_deg:       " << meta_fenix2keep_folder.pitch_deg << endl
         << "   yaw_deg:         " << meta_fenix2keep_folder.yaw_deg << endl
         << "   alt_m:           " << meta_fenix2keep_folder.alt_m << endl << endl;
    return;
} // -- END printKeepData

void EthKeeper::show_numeric_data()
{

    //    cout << "dbg:: img_show.size = " << img_show.size() << endl;
    //    cout << "dbg:: img_work.size = " << img_work.size() << endl;

    img_work.copyTo(img_show(Rect(0,0,frame_w,frame_h)));
    drawMarker(img_show, pt_center, color::red, MARKER_CROSS, frame_w, 2);
#ifdef TKDNN
    if(meta_fenix2keep_folder.work_in_round)
    {
        circle(img_show, pt_center, frame_w * 0.5, color::black, fontthic);
    }
#endif // TKDNN

    Point str_pos = str_pos0;
    cv::putText(img_show, "track reinit mod: " + to_string(track_reinit), str_pos, font, fontscale, color::black, fontthic);
    str_pos += 2 * str_h + Point(0, 2 * tmp_show_bord + tmp_show_w);
    string size_temp_now_str = "Track size now [pix]:" + to_string(round(2 * meta_fenix2keep_folder.trackw * img_work.cols));
    string size_temp_new_str = "Track size new [pix]:" + to_string(round(2 * meta_fenix2keep_folder.new_trackw * img_work.cols));
    string roll_deg_str  = "roll     [deg]: " + to_string(meta_fenix2keep_folder.roll_deg) + "; ";
    string pitch_deg_str = "pitch   [deg]: " + to_string(meta_fenix2keep_folder.pitch_deg) + "; ";
    string yaw_deg_str   = "yaw    [deg]: " + to_string(meta_fenix2keep_folder.yaw_deg) + "; ";
    string alt_m_str     = "altitude [m]  : " + to_string(meta_fenix2keep_folder.alt_m) + "; ";
    putText(img_show, size_temp_now_str, str_pos, font, fontscale, color::black, 2);
    str_pos += 2 * str_h;
    putText(img_show, size_temp_new_str, str_pos, font, fontscale, color::black, 2);
    str_pos += 2 * str_h;
    putText(img_show, roll_deg_str, str_pos, font, fontscale, color::black, 2);
    str_pos += str_h;
    putText(img_show, pitch_deg_str, str_pos, font, fontscale, color::black, 2);
    str_pos += str_h;
    putText(img_show, yaw_deg_str, str_pos, font, fontscale, color::black, 2);
    str_pos += str_h;
    putText(img_show, alt_m_str, str_pos, font, fontscale, color::black, 2);
    str_pos += str_h;
    str_pos += str_h;

    Scalar clr_poweroff(200,200,200);
    if (!square_status && !circle_status)
    {
        mat_poweroff.copyTo(img_show(rct_poweroff));
        clr_poweroff = {180,180,240};
        if (((Point)p_mouse).inside(rct_poweroff))
        {
            clr_poweroff = Scalar(100,100,255);
        } // END if (p_mouse.inside(rct_poweroff))
    } // (0;0)
    else
    {
        mat_poweroff_disable.copyTo(img_show(rct_poweroff));
    } // (!0;!0)
    rectangle(img_show, rct_poweroff, clr_poweroff, 3);


    if (meta_fenix2keep_folder.track_is_init)
    {
        putText(img_show, "TRACKER IS INIT", str_pos, font, fontscale, color::green, fontthic);
        str_pos += str_h;

        string delta_txt = "Delta position [pix/pix_max]: [" +
                to_string(meta_fenix2keep_folder.diff_trackx) + "; " +
                to_string(meta_fenix2keep_folder.diff_tracky) + "]";
        putText(img_show, delta_txt, str_pos, font, fontscale, color::black, fontthic);
        str_pos += str_h;

        string xy_m_s_str = "X', Y' [m]: [" +
                to_string(meta_fenix2keep_folder.x_m_s) + "; " +
                to_string(meta_fenix2keep_folder.y_m_s) + "]";
        putText(img_show, xy_m_s_str, str_pos, font, fontscale, color::black, fontthic);
        str_pos += str_h;

        string xy_m_ss_str = "X'', Y'' [m]: [" +
                to_string(meta_fenix2keep_folder.x_m_ss) + "; " +
                to_string(meta_fenix2keep_folder.y_m_ss) + "]";
        putText(img_show, xy_m_ss_str, str_pos, font, fontscale, color::black, fontthic);
        str_pos += str_h;

        string delay_ms = "Frame delay: [ms]" + to_string(meta_fenix2keep_folder.time_delay_mcs / 1000) ;
        putText(img_show, delay_ms,  str_pos, font, fontscale, color::black, fontthic);
        str_pos += str_h;
    } // END meta_fenix2keep_folder.track_is_init

    string square_status_str = "square_status: " + to_string(square_status);
    string circle_status_str = "circle_status: " + to_string(circle_status);
    string click_up_str = "click_up_status: " + to_string(click_up);
    string click_down_str = "click_down_status: " + to_string(click_down);
    string click_is_down_str = "click_is_down_status: " + to_string(click_is_down);
    string track_lib_type_str = "LIBRARY: " + to_string(meta_fenix2keep_folder.gpu_type);
    string device_type_str = "DEVICE: " + name_from_dev_list(meta_fenix2keep_folder.device);

    putText(img_show, "work_mode:" + to_string(work_mode),str_pos, font, fontscale, color::black,fontthic);
    str_pos += str_h;
    putText(img_show, square_status_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;
    putText(img_show, circle_status_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;
    putText(img_show, click_up_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;
    putText(img_show, click_down_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;
    putText(img_show, click_is_down_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;
    str_pos += str_h;
    putText(img_show, track_lib_type_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;
    putText(img_show, device_type_str,str_pos,font, fontscale, color::black,fontthic);
    str_pos += str_h;

    return;
} // END show_numeric_data

void EthKeeper::show_track_data()
{
    if (square_status != 2 && circle_status == 1)
    {
        bool tmp_on_img = (rct_mouse_aim.tl().x > 0 &&
                           rct_mouse_aim.tl().y > 0 &&
                           rct_mouse_aim.br().x < frame_w &&
                           rct_mouse_aim.br().y < frame_h);
        if (tmp_on_img)
        {
            cv::Mat rct_aim = img_work(rct_mouse_aim).clone();
            if(rct_aim.data)
            {
                resize(rct_aim, rct_aim, Size(tmp_show_w ,tmp_show_w));
                rct_aim.copyTo(img_show(tmp_rect));
                rectangle(img_show, tmp_rect, color::black, 3);
            } // END if(rct_aim.data)
        } // END if (tmp_on_img)
        if (circle_status && square_status != 2)
        {
            circle_pos = p_mouse;
            if (p_mouse.x >= 0 && p_mouse.y >= 0 && p_mouse.x < img_work.cols && p_mouse.y < img_work.rows && !confirm_deinit_request && !confirm_poweroff_srv_request)
            {
                circle_pos = p_mouse;
            } // END if (p_mouse.x >= 0 && p_mouse.y >= 0 && p_mouse.x < img_work.cols && p_mouse.y < img_work.rows)
            else
            {

                circle_pos = 0.5 * Point(frame_w, frame_h);
            } // END else
            fenix2cmd_to_send.mouse_pos_x = circle_pos.x * frame_w_1;
            fenix2cmd_to_send.mouse_pos_y = circle_pos.y * frame_w_1;
            circle(img_show, circle_pos, round(meta_fenix2keep_folder.new_trackw * 0.5 * frame_w), color::Green::lime, 2);
        } // END if (circle_status && square_status != 2)
    } // END if (click_down)


    if (meta_fenix2keep_folder.track_is_init)
    {
        Rect tmp_rct = Rect(meta_fenix2keep_folder.trackx * img_work.cols - rct_wh_2.x,
                            meta_fenix2keep_folder.tracky * img_work.rows - rct_wh_2.y,
                            meta_fenix2keep_folder.trackw * img_work.cols,
                            meta_fenix2keep_folder.trackh * img_work.rows);

        if (tmp_rct.tl().x > 0 &&
                tmp_rct.tl().y > 0 &&
                tmp_rct.br().x < frame_w &&
                tmp_rct.br().y < frame_h &&
                (!click_down || square_status == 2))
        {
            cv::Mat tmp_track = img_work(tmp_rct).clone();
            if (tmp_track.data)
            {
                resize(tmp_track, tmp_track, Size(tmp_show_w ,tmp_show_w));
                tmp_track.copyTo(img_show(tmp_rect));
                rectangle(img_show, tmp_rect, color::black, 3);
            } // END if (tmp_track.data)
        } // END if ((tmp_rct & Rect(0,0,img.cols, img.rows)) == tmp_rct)

        Scalar clr_rect = color::red;
        if (square_status == 2) {clr_rect = color::Green::lime;}
        cv::rectangle(img_show, tmp_rct, clr_rect, 2);
    } // END if (meta_fenix2keep_folder.track_is_init)
    return;
} // -- END show_track_data



void EthKeeper::handler_new()
{
    cvtColor(img2keep, img_work, COLOR_GRAY2BGR);
    rct_wh_2 = {0.5f * meta_fenix2keep_folder.trackw * frame_w,
                0.5f * meta_fenix2keep_folder.trackh * frame_h}; // размер инициализированного трека
    rct_wh_new_2 = {0.5f * meta_fenix2keep_folder.new_trackw * frame_w,
                    0.5f * meta_fenix2keep_folder.new_trackh * frame_h}; //
    show_numeric_data();
    show_track_data();
    if (!confirm_handler())
    {
        cv::imshow(winname, img_show);
        return;
    } // END  if (!confirm_handler())
    imshow(winname, img_show);
    key = 0;
    key = waitKey(20);


    switch(circle_status)
    {
    case 0:
    {
        if(!square_status) // {0, 0}
        {
            if (meta_fenix2keep_folder.track_is_init) // если на сервере уже иницииализирован трек или yolo
            {
                if (meta_fenix2keep_folder.track_confirm)
                {
                    square_status = 2;
                    break;
                } // !track_confirm
                else
                {
                    square_status = 1;
                } // !track_confirm
            } // END if (meta_fenix2keep_folder.track_is_init)
            cv::setMouseCallback(winname, aimFrameCallback, &p_mouse);
            if (click_down && p_mouse.inside(rct_work)) // init mouse position
            {
                circle_status = 1;
                rct_mouse_aim = {p_mouse - rct_wh_new_2, p_mouse + rct_wh_new_2};
                if(!click_is_down)
                {
                    click_is_down = 1;
                    p_down = p_mouse;
                } // -- END if(click_is_down)
            } // END (click_down && p_mouse.inside(rct_work))

            if (p_mouse.inside(rct_poweroff) && click_up) // poweroff server
            {
                confirm_poweroff_srv_request = 1;
                click_up = 0;
                click_down = 0;
                click_is_down = 0;
            } // END if (p_mouse.inside(rct_poweroff) && click_up)
            if (click_up) // init_track
            {
                click_down = 0;
                click_is_down = 0;
                click_up = 0;
            } // END if (click_up)
            break;
        } // (0;0) - WAIT_MODE

        if(square_status) // {0,2}
        {
            if (!meta_fenix2keep_folder.track_is_init)
            {
                square_status = 0;
            } // END if (!meta_fenix2keep_folder.track_is_init)
            else if(meta_fenix2keep_folder.track_confirm)
            {
                square_status = 2;
            } // END else
            else
            {
                square_status = 1;
            }

            cv::setMouseCallback(winname, aimFrameCallback, &p_mouse);

            rct_mouse_aim = {p_mouse + rct_wh_new_2, p_mouse - rct_wh_new_2};

            if (((square_status == 2 && key == 27) || square_status == 1) && p_mouse.inside(rct_work) && click_up) // esc & click_up
            {
                click_down = 0;
                click_is_down = 0;
                click_up = 0;
                circle_status = 1;
                square_status = 1;
                fenix2cmd_to_send.reinit = 1;
                fenix2cmd_to_send.mode_mouse = 1;
                fenix2cmd_to_send.track_init_posx = rct_mouse_aim.x * frame_w_1;
                fenix2cmd_to_send.track_init_posy = rct_mouse_aim.y * frame_h_1;
                key = '0';
                break;
            } // END if (key == 27)

            if (key == '`')
            {
                confirm_deinit_request = 1;
            } // END if (key == '`')

            if (square_status == 1 && key == 32)
            {
                cout << "dbg:: key = space!" << endl;
                circle_status = 0;
                track_reinit = 0;
                fenix2cmd_to_send.mode_track = 1;
                square_status = 2;
                key = '0';
                break;
            } // END (square_status == 1 && key == 32)

        } // (0;1)->(0;2) - WORK_MODE

        break;
    }  // case 0: (circle_status)

    case 1: // circle_status = 1
    {
        cv::setMouseCallback(winname, aimFrameCallback, &p_mouse);
        rct_mouse_aim = {p_mouse + rct_wh_new_2, p_mouse - rct_wh_new_2};

        if (key == '`')
        {
            confirm_deinit_request = 1;
            break;
        } // END if (key == '`')


        if (!square_status) // (1,0)
        {
            if(meta_fenix2keep_folder.track_is_init)
            {
                square_status = 1;
                break;
            } // END if(meta_fenix2keep_folder.track_is_init)

            if (click_up && p_mouse.inside(rct_work))
            {
                click_up = 0;
                click_down = 0;
                click_is_down = 0;
                fenix2cmd_to_send.reinit = 1;
                fenix2cmd_to_send.track_init_posx = rct_mouse_aim.x * frame_w_1;
                fenix2cmd_to_send.track_init_posy = rct_mouse_aim.y * frame_h_1;
                break;
            } // END click_up
            break;
        } // (1;0) - HANDLE_MODE

        if (square_status == 1) // (1;1)
        {
            if (!meta_fenix2keep_folder.track_is_init)
            {
                square_status = 0;
                break;
            }  // END if (!meta_fenix2keep_folder.track_is_init)

            if (key == 32)
            {
                cout << "dbg:: key = space!" << endl;
                circle_status = 0;
                track_reinit = 0;
                fenix2cmd_to_send.mode_track = 1;
                square_status = 2;
                key = '0';
                break;
            } // END if (key == 32)

            if (click_up && p_mouse.inside(rct_work))
            {
                click_up = 0;
                click_down = 0;
                click_is_down = 0;
                if (key == 27) // esc
                {
                    fenix2cmd_to_send.deinit_track = 1;
                    break;
                } // END if (key == 27) // esc
                else
                {
                    fenix2cmd_to_send.reinit = 1;
                    fenix2cmd_to_send.track_init_posx = rct_mouse_aim.x * frame_w_1;
                    fenix2cmd_to_send.track_init_posy = rct_mouse_aim.y * frame_h_1;
                    break;
                } // click_up && !esc
            } // END if (click_up && p_mouse.inside(rct_work))
            break;
        } // (1;1) - CONFIRM_MODE
        break;
    } // circle_status
    default:
    {
        break;
    } // END default
    } // END switch (circle_status)
    if (click_up)
    {
        click_up = 0;
        click_down = 0;
        click_is_down = 0;
    } // END if (click_up)
    if (key == key_track_size_down) {fenix2cmd_to_send.track_size_down = 1;}
    if (key == key_track_size_up) {fenix2cmd_to_send.track_size_up = 1;}

    return;
} // -- END handler_new

string EthKeeper::name_from_dev_list(uint8_t num)
{
    std::string name = "";
    switch(num)
    {
    case 0:     {return "FOLDERREADER";}
    case 1:     {return "VIDEOREADER";}
    case 5:     {return "IMX477 Camera";}
    case 6:     {return "HVGS Camera";}
    case 7:     {return "HIKVISION Camera";}
    default:    {return "UNCNOWN DEVICE";}
    };
    return "ERROR";
}  // -- END name_from_dev_list

void EthKeeper::mouse2center()
{
    /// mouse_position_controll
    Rect win_rct = getWindowImageRect(winname);
    int x = win_rct.x + 0.5 * win_rct.height;
    int y = win_rct.y + 0.5 * win_rct.height;
    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);
    XFlush(dpy);
    return;
} // -- END mouse2center

bool EthKeeper::need_quit_handler()
{
    if (need_quit)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1500));
        bool ok_quit = quit();
        if (!ok_quit)
        {
            cout << "chain_drone_client::END work not ok!" << endl;
            return true;
        } // END if (!ok_quit)
        else
        {
            cout << "chain_drone_client::END work ok!" << endl;
            return true;
        } // END if (ok_quit)
    } // END if (need_quit)

    return false;
}

void EthKeeper::work()
{
    cout << "Start work!" << endl;
    bool ok = 0;
    img_show = cv::Scalar(235,240,235);
    cv::Mat img_show_disconnect = img_show.clone();
    int num_wait = 1;
    string wait0 = "WAIT CONNECTION";
    Point wait_connection_pos = 0.5 * Point(img_show.cols, img_show.rows) - Point(3 * fontscale * 10 * wait0.size(), 3 * fontscale * 11);
    while(!frame_keeper_ptr->frame(img2keep, meta_fenix2keep_folder))
    {
        num_wait++;
        string wait = wait0;
        for(int i = 0; i < num_wait%4; i++)
        {
            wait += ".";
        } // END for(int i = 0; i < num_wait%4; i++)
        img_show_disconnect = cv::Scalar(235,240,235);;
        putText(img_show_disconnect, wait, wait_connection_pos, font, 3 * fontscale, font_clr, 3 * fontthic);
        imshow(winname, img_show_disconnect);
        key = waitKey(10);
        if (key == key_quit_client)
        {
            need_quit = 1;
            if (need_quit_handler()) {break;}
        } // if (key == key_quit_client)
        this_thread::sleep_for(chrono::milliseconds(333));
    } // waitConnection..
    if (need_quit) {return;}
    while(true)
    {

#if defined(GST_CAPI_H264) || defined(GST_CAPI_H265) || defined(GST_CAPI_MJPEG) || defined(GST_CAPI_RAW)
        ok_connect = frame_keeper_ptr->frame(img2keep, meta_fenix2keep_folder);
        if (!ok_connect)
        {
            if (disconnect)
            {
                putText(img_show, wait0, wait_connection_pos, font, 3 * fontscale, color::red, 3 * fontthic);
                imshow(winname, img_show);
                key = waitKey(10);
                if (key == key_quit_client)
                {
                    need_quit = 1;
                    if (need_quit_handler()) {break;}
                } // END if (key == key_quit_client)
            } // END if (disconnect)
            continue;
        } // END if (!ok_connect)
        img_show = cv::Scalar(235,240,235);
        num_frame++;
        //        cout << "dbg:; ok_connect[" << num_frame << "] = " << ok_connect << endl;
#endif // GST_CAPI_H264 || GST_CAPI_H265 || GST_CAPI_MJPEG || GST_CAPI_RAW
        fenix2cmd_to_send = fenix2cmd_empty;
        //        printKeepData(); // dbg::

        handler_new();
        if (fenix2cmd_to_send.mode_track) {cout << "dbg:: !!! CMD use track!!!" << endl;}
        if (fenix2cmd_to_send.mode_mouse) {cout << "dbg:: !!! CMD use mouse!!!" << endl;}

        if (prev_state == 2 && prev_init && !meta_fenix2keep_folder.track_is_init)
        {
            mouse2center();
        } // END if (prev_state == 2 && prev_init && !meta_fenix2keep_folder.track_is_init)

        if ((!square_status || square_status == 1) && !circle_status) {fenix2cmd_to_send.work_mode = 0;}
        if (circle_status == 1 && square_status != 2) {fenix2cmd_to_send.work_mode = 1;}
        if (square_status == 2) {fenix2cmd_to_send.work_mode = 2;}

        prev_state = fenix2cmd_to_send.work_mode;
        prev_init = meta_fenix2keep_folder.track_is_init;

        if (fenix2cmd_to_send != fenix2cmd_empty)
        {
            fenix2cmd_sender_ptr->set(fenix2cmd_to_send);
        } // END (fenix2cmd_to_send != fenix2cmd_empty)
#ifdef USE_SPEAKER
        if(square_status == 2)
        {
            track_fall = 0;
        } // END if(square_status == 2)
        else
        {
            track_fall = 1;
            if (!square_status && !circle_status)
            {
                pause = pause_fall;
            } // END if (!square_status && !circle_status)
            else
            {
                pause = pause_handler;
            } // END else
        } // END else
#endif // USE_SPEAKR
        if (key == key_quit_client) {need_quit = 1;}
        if (need_quit_handler()) {break;}
    } // END while true

    if (key == key_quit_client) {need_quit = 1;}

    return;
} // -- END work()

}; // -- END namespace chain_drone_cli
