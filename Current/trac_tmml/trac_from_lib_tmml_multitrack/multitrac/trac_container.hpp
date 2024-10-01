#ifndef TRAC_CONTAINER_HPP
#define TRAC_CONTAINER_HPP

#include <iostream>
#include <opencv2/imgproc.hpp>
#include "tracshats/tracshats.hpp"
#include <list>
#include "tools/colors.h"
#include "devices/device.hpp"
#include "devices/iframehandler.h"
#include "tools/ExtendINIReader.hpp"

namespace mtrac
{

enum Colors
{
    CYAN,
    YELLOW,
    ORANGE,
    DARKORANGE,
    BROWN,
    RED,
    BLUE,
    GREEN,
    VIOL,
    WHITE,
    GRAY,
    BLACK,
    END_ENUM
}; // END enum Colors

struct TracContainer
{
    TracContainer();
    TracContainer(const std::string & config_path, cv::Mat & frame, std::shared_ptr<Device> * device_,  bool & ok);
    bool processShats();
    void prepareFrameForTracShats(cv::Mat & frame_receive);
    void workflowShats(cv::Mat & frame_receive, cv::Mat & frame_show, int pos, int pos_main);
    bool get_ini_params(const string &config_path, const string &section);
    void rect2f_in_border(cv::Rect2f & rect);
    bool init_trac(cv::Rect2f & rectm,  cv::Mat & frame_show);
    bool quit();

    std::string config_path = "";
    int num = 0;                                    // номер структуры
    cv::Scalar color = color::viol;
    std::shared_ptr<TracShats> tracShats = nullptr; // объект класса трекера
    cv::Mat frame_process_tracshats;                // кадр для обработки трекером
    bool flag_zahvat = 0;                           // трек захвачен
    bool isTracShatsFirstInitedFlag = false;        // флаг инициации трекера
    bool isTracShatsInitedFlag = false;             // флаг инициации трекера
    bool tracShatsInitReqFlag = false;              // есть запрос на инициализацию трекера
    cv::Rect2f searchRect = cv::Rect2f(0,0,0,0);    // поожение трекера на новом кадре
    cv::Rect2f roi = cv::Rect2f(0,0,0,0);           // текущий ROI
    cv::Rect2f aimRectShats = cv::Rect2f(0,0,0,0);  // текущая рамка цели
    bool isRoiSetted = 1;                           // установлен roi
    std::shared_ptr<Device> device = nullptr;       //

    bool roi_mode = 0 ; // Работать в roi
    bool get_rect_manual = 1 ; // Ручной захват цели с помощью мыши.
    bool parallel = 1 ; // режим параллельного исполнения трекера и приема кадров от device
    bool handle_flag = 1 ; // возможность управлением захвата трека на текущем устройстве при велюченным управлении через ethernet
    int demonstration_mode = 1;
    int num_trac_max = 8 ; // максимальное число одновременно инициализированных треков
    Scalar clr_pos = Scalar(0,0,0);
    Scalar clr_pos_main = Scalar(255,255,255);

    float frame_show_w_1 = 0.f;
    float frame_show_h_1 = 0.f;

}; // END struct TracContainer

}; // END namespace mtrac

#endif // TRAC_CONTAINER_HPP
