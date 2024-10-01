#ifndef APPLICATION_H
#define APPLICATION_H

#include <opencv2/core/core.hpp>
#include "devices/device.hpp"
#include "devices/iframehandler.h"
#include "INIReader.h"
#include "tools/time_keeper/time_keeper.hpp"
#include "tools/colors.h"

//#ifdef TKDNN
//#include "tracshats_tkdnn/tracshats.hpp"
//#else
#include "tracshats/tracshats.hpp"
//#endif // !TKDNN

#include <cstring>
#include <thread>
#include <functional>
#include <condition_variable>
#include <signal.h>
#include <list>

#ifdef USE_FOLDER_READER
#include "devices/FolderReader/folderreader.h"
#endif // USE_FOLDER_READER

#ifdef USE_VIDEO_READER
#include "devices/VideoReader/videoreader.h"
#endif //USE_VIDEO_READER

#ifdef USE_WEB_CAMERA
#include "devices/WebCamera/webcamera.hpp"
#endif //USE_WEB_CAMERA

#ifdef USE_RASPBERRY_HQ_CAMERA
#include "devices/RaspberryHQCamera/factory.hpp"
#endif // USE_RASPBERRY_HQ_CAMERA

#ifdef USE_IMX219_CAMERA_MIPI
#include "devices/IMX219CameraMIPI/imx219_camera_mipi_factory.hpp"
#endif // USE_IMX219_CAMERA_MIPI

#ifdef USE_IMX477_SQUARE_CAMERA_MIPI
#include "devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.hpp"
#endif // USE_IMX477_SQUARE_CAMERA_MIPI


#ifdef USE_HVGS_GRAY_USB_CAMERA
#include "devices/HVGS_GRAY_USB_Camera/hvgs_gray_usb_camera_factory.hpp"
#endif // USE_HVGS_GRAY_USB_CAMERA

#ifdef USE_HIKVISION
   #include "devices/EthCameraRtsp/rtsp_h265_device_factory.hpp"
#endif // USE_HIKVISION


#ifdef USE_LOGGER
#include "logger/factory.h"
#endif //USE_LOGGER

#ifdef USE_ETH_CONTROLLER


#include "video_eth_controllers/gstc/rtp_server_h264/rtp_server_h264.hpp"
#include "video_eth_controllers/gstc/rtp_server_h264/rtp_server_h264_settings.hpp"

#include "modules/meta_struct/meta_struct.hpp"
#include "modules/fenix2cmd/fenix2cmd_struct.hpp"
#include "modules/fenix2cmd_keeper/fenix2cmd_keeper_factory.hpp"
#include "modules/fenix2cmd_keeper/fenix2cmd_keeper.hpp"

#ifdef USE_TCP_SETUP
#include "modules/tcp_server_setup_info/setup_info_struct.hpp"
#include "modules/tcp_server_setup_info/tcp_server_setup_info_factory.hpp"
#endif // USE_TCP_SETUP


#ifdef USE_ETH_MD
#include "modules/eth_chain_drone_ap_telemetry_keeper/eth_chain_drone_ap_telemetry_keeper_factory.hpp"
#include "modules/eth_chain_drone_ap_telemetry_keeper/eth_chain_drone_ap_telemetry_keeper.hpp"
#endif // USE_ETH_MD

#include "modules/trackmeta2ap/trackmeta2ap_pos.hpp"
#include "modules/track_meta_pos_sender/track_meta_pos_sender.hpp"
#include "modules/track_meta_pos_sender/track_meta_pos_sender_factory.hpp"

#include "tools/watchdog.h"

#ifdef USE_RECORDER
#include "tools/recorder_HVGS/recorder_srst.hpp"
#include "tools/disk_monitor/disk_monitor.hpp"
#include "tools/disk_monitor/live_disk_monitor.hpp"
#include "tools/sys_time_toolbox/sys_time_extract.hpp"
#endif // USE_RECORDER

#endif // USE_ETH_CONTROLLER

#include "tools/watchdog.h"

#include <iomanip>

struct TracContainer
{
    TracContainer(int id_new) {id = id_new;};
    void setId(int id_new) {id = id_new;}
    int getID(){return id;}
    cv::Rect2f getRct() {return rct;}
    bool isInited() {return is_inited;}
    bool init_track(cv::Rect2f);
private:
    int id = 0;
    bool is_inited = false;
    cv::Rect2f rct = {0,0,0,0};
    cv::Scalar color = color::viol;
    bool found = false;
    std::unique_ptr<TracShats> trac_ptr;
    std::string name = "track N" + std::to_string(id);

}; // END TracContainer

class Application : public IFrameHandler // обработка приема фреймов

        #ifdef USE_ETH_CONTROLLER_CMD_PROCESSING // Наследование от дополнительных классов в случае работы с eth
        , public ICmdHandler // обработка приема eth-команд
        , public IEthNotifyHandler // обработка приемка eth-уведомлений
        #endif //USE_ETH_CONTROLLER_CMD_PROCESSING
{
public:
    Application(const std::string &pathToConfig, bool &ok);
    ~Application();
    void quit(); // TODO: сделать private, т.к. небезопасен при внешнем вызове
    void stop() {std::cout << "Call stop!\n"; need_quit = 1; }
    /*
    Вызывает quit только при завершении работы цикла в exec();
    (но с определенным лимитом по времени ожидания watchdog_wait_close_exec_time);
    Возвращает true в случае, если удалось дождаться закрытия exec за
    выделенное лимитированное время. quit() вызывается вне зависимости от успешности операции
    ожидания.
    */
    bool quit_async();
    void start();
    void exec();    // основная функция выполнения приложения
private:
    // перечень устройств-источников видеопотока
    enum Devices
    {
        FOLDER = 0,
        VIDEO = 1,
        WEBCAMERA = 2,
        RASPBERRY_HQ_CAMERA = 3,
        IMX219_CAMERA_MIPI = 4,
        IMX477_SQUARE_CAMERA_MIPI = 5,
        HVGS_GRAY_USB_CAMERA = 6,
        RTSP_H265 = 7,
        SHARED_MEMORY = 8
    }; // -- END enum Devices
    Rect2f rct_frame = Rect2f(0, 0, 0.99999, 0.99999); // переменная для проверки нахождения рамки внутри кадра

    std::atomic<bool> _execute = false;     // флаг нахождения программы в процессе выполнения
    std::atomic<bool> _exec_complete_success = false; // флаг успешного завершения метода exec(), исполняемого в отдельном потоке
    std::atomic<bool> _quit_async_complete = false; // флаг окончания выполнения метода quit_async()

    std::atomic<bool> quit_was_called = false; // устанавливается при первом вызове метода quit() данного класса
    std::atomic<bool> _quit_async_was_called = false; // флаг устанавливается при первом вызове метода quit_async();

    std::atomic<bool> frameReady = false; // флаг готовности фрейма

    std::mutex frame_proc_0_mutex, frame_proc_1_mutex;

    cv::Mat frame_receive;
    cv::Mat frame_process_0; // двойная буфферизация
    cv::Mat frame_process_1;

    cv::Mat frame_process_tracshats;    // кадр для обработки трекером
    cv::Mat frame_show;                 // кадр для показа на экране

    int frame_send_w = 1080;
    int frame_send_h = 1080;

#ifdef USE_RECORDER
    std::shared_ptr<recorder::RecorderSRST> recorder_ptr = nullptr;
    recorder::RecorderSRSTSettings rec_settings;
    bool use_recorder = false;
    //recorder INI - params;
    int             recorder_format     = recorder::IMG_FORMAT_PNG; // IMG_FORMAT_PNG
    int             watchdog_quit_ms    = 30'000;
    int             png_compress_value  = 1;
    int             jpeg_quality        = 100;

    bool rec_make_path     = true;
    bool rec_force_replace = true;
    std::string     frames_record_dir          = "../record_results/record_jpeg_quality100/";
    bool make_adaptive_rec_dir();
    bool adaptive_dirs_setup();

    //adaptive gen rec dir
    bool adaptive_make_rec_dir = false;
    std::string rec_zoo_dir_path = "../recs";
    bool makepath_rec_zoo_dir = false;
    int base_val_rec_dir = 1e7;
    std::string frames_pstfx = "frames";
    std::string rec_dir = "";

    long min_free_memory = 870000 ; // минимальная память мегабайт
    long now_free_memory = 0 ; // минимальная память мегабайт
    int check_memory_time = 1500 ; // миллисекунд
    std::shared_ptr<LvDiskMonitor> disk_monitor_ptr = nullptr;

#endif // USE_RECORDER

    std::atomic<int> process_frame_id = 0; // номер (0,1) текущего обрабатываемого фрейма в главном цикле программы

    // флаг готовности кадра для обработки трекером

    bool isTracShatsFirstInitedFlag = false;           // флаг инициации трекера
    bool isTracShatsInitedFlag = false;                // флаг инициации трекера
    bool tracShatsInitReqFlag = false;
    bool found = false;
      cv::Rect2f searchRect{0,0,0,0};

      // данные для захвата цели мышью
    int get_rect_manual = 1;       // признак разрешения ручного захвата цели
    static bool click_down;
    static bool click_up;
    static cv::Point2f p_mouse;
    static cv::Point2f p_down;
    bool first_click_down = 1;

    // данные для работы в режиме ROI
    int roi_mode = 0;				// признак работы в режиме ROI
    bool isRoiSetted = false;           // признак установки ROI
    int scaleROI = 5;                   // масштаб ROI относительно размера цели
    int scale = 0;
    cv::Scalar clr_scaling = color::green;

    float show2originImgRatio = 1;              // соотношение размеров (ширины) демонстрационного кадра к оригинальному, высота адаптируется
    cv::Rect2f roi = cv::Rect2f(0,0,0,0);       // текущий ROI
    cv::Rect2f aimRectShats = cv::Rect2f(0,0,0,0); // текущая рамка цели

    // results demonstration
    int frame_show_width = 640;         // ширина отображаемого кадра
    int demonstration_mode = 0;         // признак режима показа

    // устройство считвания кадров
    std::shared_ptr<Device> device = nullptr;				// источник видеопотока
    std::shared_ptr<TracShats> tracShats = nullptr;         // трекер

    uint8_t device_id = 0; // в соответствии с enum Devices

    std::string config_path;

    bool parallel = 0;
    bool need_quit = false;		// флаг запроса на выход из приложения, устанавливается методами

#ifdef GUI_OK
    std::string app_win_name = "Application";
#endif // GUI_OK

    // Временные точки для нахождения времени обработки кадра.
    std::chrono::system_clock::time_point
    time_point_tracker0, time_point_tracker1,
    time_point_device0, time_point_device1;
    // обработка изображения (трекинг)
    inline bool processShats();
    // рабочий цикл трекеров
    inline void workflowShats();
    void initTracShats(cv::Rect2f& rect);
#ifdef GUI_OK
    // колл-бэк метод обработки событий мыши
    static void aimFrameCallback(int event, int x, int y, int flags, void* param);
    // обработчик событий мыши (основной регулярный цикл)
    bool mouseHandler(cv::Mat& img, const string& win_name,
                      uchar& key, cv::Rect2f& object_rect);

    // обработчик событий клавиатуры
    bool keyHandler(uchar &key);
#endif //GUI_OK

    /// META_SENDER
    int camera_ange = 0 ; // угол в градусах камеры относительно носа аппарата
    float camera_max_angle_x_deg = 60 ;
    float camera_max_angle_y_deg = 40 ;
    const std::string section_trackmeta_sender = "trackmeta_sender"; // раздел ini-файла для инициализации модуля
    TrackMeta2AP_pos trackmeta_pos_data_now; // отклонение шаблона от центра кадра
    std::shared_ptr<TrackMetaPosSender> trackmeta_pos_sender_ptr = nullptr; // модуль отправуи метаданных

    // INI::[callback]
//    float rct_w = 128.f ;
//    float rct_h = 128.f ;
    float zahvat_size = 24;
    cv::Point2f rct_wh_2 = {12, 12};
    cv::Rect2f rct_mouse_aim = {0,0,0,0};
    float rct_w_change_step   = 8.f ;
    float rct_h_change_step   = 8.f ;
    uchar rct_increase_button = ']' ;
    uchar rct_decrease_button = '[' ;
    // imshow
    cv::Point2f pt_frame_center = {0.f,0.f};
    float frame_w_1 = 1.f / 1920.f;
    float frame_h_1 = 1.f / 1080.f;
    float frame_show_w_1 = 1.f / 1920.f;
    float frame_show_h_1 = 1.f / 1080.f;

#ifdef USE_ETH_MD
    std::shared_ptr<chain_drone_ap_tele_keeper::APTeleKeeper> keeper = nullptr;
    std::string section_ap_tel = "APTelemetryKeeper";
    int max_session_duration_s = 25;
    int delay_step_ms = 100;
    ChainDroneTelemetryAP frame_metadata;
    unsigned long int frame_time = 0; // время получения кадра от девайса
//    ParitelTelemetryGen frame_metadata, frame_metadata_0, frame_metadata_1;
    float deg2rad = M_PI / 180.f;
    float rad2deg = 180.f / M_PI;
#endif // USE_ETH_MD
    bool valid = 1;

#ifdef USE_ETH_CONTROLLER


    std::shared_ptr<rtp::RtpServerH264> fenix2frame_sender_ptr = nullptr;
    rtp::server::h264::SettingsPtr settings_srv_ptr = nullptr;
    std::string rtp_server_section = "gstc_rtp_server_h264";

    std::shared_ptr<fenix2cmd_keeper::Fenix2CmdKeeper> fenix2cmd_keeper_ptr = nullptr;

    Fenix2Cmd fenix2cmd_zero_data = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    Fenix2Cmd fenix2cmd_keep_data;
    const Fenix2Meta fenix2meta_empty;
    Fenix2Meta fenix2meta_data2send;
    bool need_reinit = 0;
    cv::Rect2f rct_reinit = {0,0,0,0};

#ifdef USE_TCP_SETUP
    /// TCP server
    Fenix2SetupInfo setup_info_for_client;
    std::string section2tcp_cmd_sender = "fenxi2tcp_cmd_sender";
    eth_controller::cmd::async::server_simplex::Settings tcp_srv_settings;
    std::shared_ptr<eth_controller::cmd::async::server_simplex::TcpServerSetupInfo> tcp_server_ptr = nullptr;
#endif // USE_TCP_SETUP

    ///rotate vec for meta_pos_sender
    int camera_mount_angle = 90;    // угол поворота (изи ini-файла) вектора отклолнений углов
    float dx_c_pix = 0 ;          // ini:: отклонение pix/pix_max
    float dy_c_pix = 0 ;          // ini::
    float max_angle_deg_2 = 45.f * 0.5 ;    // ini:: половина угола поля зрения камеры, охватывающий 0 - pix_max
    float tan_max = tan(max_angle_deg_2 * deg2rad); // тангенс половины угла поля зрания (по х и у равны)
    float gamma0 = 0.f;// начальный угол рыскания
    float sign = 1; // знак, определяющий правую/левую сиситему координат
    void get_point_xy_ss(const float & x_pix,  // смещение в нормированных координатах
                         const float & y_pix,
                         const float & H,      // высота, метры
                         const float & alpha,  // крен, радианы
                         const float & beta,   // тангаж, радианы
                         const float & gamma,  // азимут, радианы
                         float & x_m_ss,       // смещение в метрах
                         float & y_m_ss);
    float dx_m_ss = 0; // вычисленное смещение в метрах
    float dy_m_ss = 0;
    float x_m_s = 0; // вычисленное смещение в метрах
    float y_m_s = 0;

    bool ethHandler(Rect2f & rct);
    void ethControllerProc();
#endif // END USE_ETH_CONTROLLER

    // подготовка изображения для tracShats
    inline void prepareFrameForTracShats();
    bool get_ini_params(const std::string& config);
    // обработчик события поступления кадра при приёме от устройства
    void setFrameSizeParams();
    inline void deviceSyncNextFrame();
    inline void deviceAsyncNextFrame();
    void handleDeviceFrame(uint8_t * f, int w, int h, int num, int id);
    bool FileIsExist(const std::string& filePath);

#ifdef TKDNN
    void work_TKDNN();
#endif // TKDNN
    int track_confirm_flag = 0;

    //multitrac
    std::list<std::unique_ptr<TracContainer>> l_trac;


}; // -- END class Application
#endif // APPLICATION_H
