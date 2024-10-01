#pragma once

#include "modules/meta_struct/meta_struct.hpp"


#ifdef GST_CAPI_H264
#include "video_eth_controllers/gstc/rtp_client_h264/rtp_client_h264.hpp"
#include "video_eth_controllers/gstc/rtp_client_h264/rtp_client_h264_settings.hpp"
#endif // GST_CAPI_H264

#ifdef GST_CAPI_H265
#include "video_eth_controllers/gstc/rtp_client_h265/rtp_client_h265.hpp"
#include "video_eth_controllers/gstc/rtp_client_h265/rtp_client_h265_settings.hpp"
#endif // GST_CAPI_H265

#ifdef GST_CAPI_MJPEG
#include "video_eth_controllers/gstc/rtp_client_mjpeg/rtp_client_mjpeg.hpp"
#include "video_eth_controllers/gstc/rtp_client_mjpeg/rtp_client_mjpeg_settings.hpp"
#endif // GST_CAPI_MJPEG

#ifdef GST_CAPI_RAW
#include "video_eth_controllers/gstc/rtp_client_raw/rtp_client_raw.hpp"
#include "video_eth_controllers/gstc/rtp_client_raw/rtp_client_raw_settings.hpp"
#endif // GST_CAPI_RAW


#include "modules/cmd_struct/cmd_struct.hpp"
#include "modules/cmd_sender/fenix2cmd_sender.hpp"
#include "modules/cmd_sender/fenix2cmd_sender_factory.hpp"

#ifdef USE_TCP_SETUP
#include "modules/tcp_client_setup_info/tcp_client_setup_info_factory.hpp"
#include "modules/tcp_client_setup_info/setup_info_struct.hpp"
#endif // USE_TCP_SETUP

#include "colors.h"
#include <cstring>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <thread>
#include <memory>
#include <fstream>
#include "eth_cnt_common_utils/eth_cnt_common_utils.hpp"
#include "eth_cnt_common_utils/eth_cnt_common_utils.hpp"
#include "toolbox_common_utils/toolbox_common_utils.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace chain_drone_cli
{

enum ChainDroneWorkMode
{
    WAIT_MODE,          // нет ни трекера, ни управления мышью. сервер отправляет сигнал {0,0,0}
    HANDLE_ISINIT_MODE, // независимо от состояния трекера, сервер отправляет сигнал {cx,cy,1} - положение мыши на клиенте
    HANDLE_NOINIT_MODE, // если NOINIT - не можем перейти в состояние AUTOMATIC
    AUTOMATIC_MODE      // сервер отправляет сигнал {qx, qy, 1} - положение трекера
};

class EthKeeper
{
public:
    EthKeeper(std::string path2setting, bool & ok);
    void work();
    bool quit();

private:

    std::string path2ini = "../eth_ini_send.ini";

#ifdef GST_CAPI_H264
    std::shared_ptr<rtp::RtpClientH264> frame_keeper_ptr = nullptr;
    std::string rtp_client_ini_section = "gstc_rtp_client_h264";
    rtp::client::h264::SettingsPtr settings = nullptr;
#endif // GST_CAPI_H264
#ifdef GST_CAPI_H265
    std::shared_ptr<rtp::RtpClientH265> frame_keeper_ptr = nullptr;
    std::string rtp_client_ini_section = "gstc_rtp_client_h265";
    rtp::client::h265::SettingsPtr settings = nullptr;
#endif // GST_CAPI_H265
#ifdef GST_CAPI_MJPEG
    std::shared_ptr<rtp::RtpClientMJPEG> frame_keeper_ptr = nullptr;
    std::string rtp_client_ini_section = "gstc_rtp_client_mjpeg";
    rtp::client::mjpeg::SettingsPtr settings = nullptr;
#endif  // HST_CAPI_MJPEG
#ifdef GST_CAPI_RAW
    std::shared_ptr<rtp::RtpClientRAW> frame_keeper_ptr = nullptr;
    std::string rtp_client_ini_section = "gstc_rtp_client_raw";
    rtp::client::raw::SettingsPtr settings = nullptr;
#endif  // HST_CAPI_RAW
    std::shared_ptr<Fenix2CmdSender> fenix2cmd_sender_ptr = nullptr;
    std::string section2cmd_sender = "fenix2cmd_sender";
    Fenix2Cmd fenix2cmd_to_send;
    Fenix2Cmd fenix2cmd_empty = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    Fenix2Meta meta_fenix2keep_folder;
    int num_frame = 0;


#ifdef USE_TCP_SETUP
    Fenix2SetupInfo setup_info_from_server;
    std::string section2tcp_cmd_keeper = "fenxi2tcp_cmd_keeper";
    eth_controller::cmd::async::client_simplex::Settings tcp_cli_settings;
    std::shared_ptr<eth_controller::cmd::async::client_simplex::TcpClientSetupInfo> tcp_client_ptr = nullptr;
#endif // USE_TCP_SETUP


    // данные для захвата цели мышью
    static bool click_down;
    static bool click_up;
    static cv::Point2f p_mouse;
    static cv::Point2f p_down;
    bool track_reinit = 1;
    bool click_is_down = 0;

    int prev_state = 0 ;
    bool prev_init = 0;


    void workflow(){};

    ChainDroneWorkMode work_mode = WAIT_MODE; // dbg::
    int circle_status = 0;
    int square_status = 0;
    bool autodetect_mode = 0; // передаём показания трекера. значение положения мыши не учитывается(circle0,square2)
    std::atomic<bool> need_quit = 0;
    uchar key;

    cv::Point circle_pos = {0,0}; // точка соответствует положению мыши
    cv::Rect2f rct_mouse_aim = {0,0,0,0}   ;

    // imshow
    cv::Point2f pt_frame_center = {0.f,0.f};
    int frame_w = 1920;
    int frame_h = 1080;
    float frame_w_1 = 1.f / frame_w;
    float frame_h_1 = 1.f / frame_h;

    //confirm gui
    cv::Point sz_confirm = {800, 200}; // р-р окна подтверждения, задаётся в конструкторе в относительныхз координатах
    cv::Rect rct_confirm = {0,0,0,0}; // рамка окна подтверждения
    cv::Point btn_c = 0.5 * sz_confirm; // центр окна подтверждения относительно
    bool confirm_handler_status = 0; // флаг вызова окна подтверждения - если !autodetect_mode - на АП передаём нулевое смещение
    bool confirm_deinit_request = 0; // флаг запроса на сброса состояния до (circle0,square0)
    bool confirm_deinit = 0; // флаг подтверждения сброса трекера
    bool confirm_poweroff_srv_request = 0; //  флаг включения запроса на подтверждение выключения сервера
    bool poweroff_srv = 0; // флаг выключения
    cv::Rect rct_poweroff = {0,0,0,0}; // рамка положения кнопки выключения
    bool need_poweroff = 0; // если при вызове подтверждения выключения ответили да, = 1 и отправляем на сервер команду
    bool flag_space2confirm = 0;
    /// Mouse position controll
    Display *dpy = XOpenDisplay(0);
    Window root_window;


    cv::Mat img2keep; // изображение для приёма данных по ethernet
    std::string winname = "CLIENT FENIX2";
    cv::Mat img_show; // изображение для показа с нанесёнными данными
    cv::Mat img_work; // принятое изображение в BGR
    cv::Mat img_info; // изображение для нанесения числовых данных (панель справа)
    cv::Mat mat_poweroff; // изображение активной кнопки выключения сервера
    cv::Mat mat_poweroff_disable; // изображение "отключенной" кнопки выключения сервера
    cv::Mat mat_confirm_deinit;// изображения окна подтверждения
    cv::Mat mat_confirm_poweroff;
    cv::Mat img_rsz; // увеличенное изображение внутри рамки захвата или рамки трека
    cv::Rect rct_work = {0,0,frame_w, frame_h};
    // Параметры для формирования боковой панели терминалки
    float monitor_format = 16.f / 9.f; // соотношение для определения разсера боковой панели с данными

    int tmp_show_bord = 8 ;
    int font = cv::FONT_ITALIC; // шрифт надписей
    int fontthic = 2;           // толщина надписей
    float fontscale = 1;        // размер надписей
    cv::Scalar font_clr = cv::Scalar(0,0,0);    // цвет надписей
    cv::Point str_h = {0, 20};  // междустрочный интервал (по у)
    cv::Point str_pos0 = {0,0}; // положение первой надписи
    int tmp_show_w = 0;         // ширина окна, показывающего увеличенное изображение внутри рамки трека или рамки захвата
    int max_w_rct_aim = 512 ;   // максимальный размер tmp_show_w
    cv::Rect tmp_rect = cv::Rect(0,0,0,0);  // положение окна рамки захвата или трека (зависит от режима)
    cv::Point pt_center = 0.5 * cv::Point(frame_w, frame_h); // центр "рабочей" области - изображения с камеры

    /// diconnect controller
    std::atomic<bool> ok_connect = 0;
    std::atomic<bool> disconnect = 1;
    std::chrono::system_clock::time_point tp_check_connection0, tp_check_connection1;
    std::chrono::duration<double> disconnect_time = std::chrono::system_clock::duration::zero();
    std::chrono::duration<double> max_time2disconnect = std::chrono::milliseconds(1000);

    ///key_handler_from_ini
    std::string handler_ini_section = "key_handler";
    uchar key_track_size_down = '[' ;
    uchar key_track_size_up = ']' ;
    uchar key_reinit_mode_change = 27 ;
    uchar key_track_deinit = '`' ;
    uchar key_quit_client = 'q' ;
    // INI::[callback]
    cv::Point2f rct_wh_new_2 = {128.f, 128.f}; // размер рамки захвата для нового трека
    cv::Point2f rct_wh_2 = {128.f, 128.f}  ; // размер инициализированного трека

    std::atomic<int> track_fall = 0;
    std::atomic<int> pause = 1000;
    bool ok_keep_frame = 0;
    bool need_warning = 1;
#ifdef USE_SPEAKER
    std::string speaker_ini_section = "speaker";
    std::string speaker_device = "alsa_output.pci-0000_00_1f.3.analog-stereo" ;
    std::string speaker_sound = "(speaker-test -t sine -f 1000 >/dev/null)& pid=$!; sleep 0.3s; kill -9 $pid ;";
    std::string speaker_sound1 = "(speaker-test -t sine -f 1000 >/dev/null)& pid=$!; sleep 0.3s; kill -9 $pid ;";
    int speaker_volume = 10;
    int num_sound_warning = 3;
    int pause_handler = 1000 ;
    int pause_fall = 50 ;
    int pause_disconnect = 20 ;
    void f_sound(int num = 1);  // вызов звукового сигнала
#endif // USE_SPEAKER
    bool need_quit_handler();
    void check_connection();
    void handler_new();
    std::string name_from_dev_list(uint8_t num); // возвращает строку, соответствующую номеру девайса
    bool compare_keep_image();
    void printKeepData();       // dbg:: вывод принимаемых данных в терминал
    void show_numeric_data();   // отрисовка боковой панели с численными данными
    void show_track_data();     // отрисовка рамкизахвата на боковой панели
    bool confirm_handler();     // обработка события вызова подтверждения команды
    inline void click_down_reaction();  // обработка нажатия мыши
    bool click_up_reaction();   // обработка события отжатия ЛКМ
    void mouse2center();        // перемещаем курсор в центр перекрестия
    bool FileIsExist(const std::string & filePath);
    bool get_ini_params(const std::string & config, const std::string & ini_section_name);
    bool mouseHandler(cv::Mat &img, const std::string &win_name, uchar &key);
    static void aimFrameCallback(int event, int x, int y, int flags, void *param);
    void keyHandler(uchar & key);
}; // END EthKeeper

}; // END namespace chain_drone_cli
