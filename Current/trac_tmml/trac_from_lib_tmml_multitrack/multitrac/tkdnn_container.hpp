#ifndef TKDNN_CONTAINER_HPP
#define TKDNN_CONTAINER_HPP

#include <iostream>
#include <opencv2/core/core.hpp>
#include "devices/device.hpp"
#include "devices/iframehandler.h"
#include "INIReader.h"
#include "tools/time_keeper/time_keeper.hpp"
#include "tools/colors.h"
#include "tools/ExtendINIReader.hpp"

#include "tractkdnn/tractkdnn.hpp"

#include <cstring>
#include <thread>
#include <functional>
#include <condition_variable>
#include <signal.h>
#include <logger/factory.h>

class TKDNNContainer
{
public:
    TKDNNContainer();
    TKDNNContainer(const std::string& config_path, cv::Mat& frame_process_0, bool& ok);
    ~TKDNNContainer();
    bool update(cv::Rect2f & aimRectShats, cv::Mat & frame_show);
    void prepareFrameForTKDNN(cv::Mat & frame_receive); // в отличие от трека, не переделываем цвет в ч/б, т.к. это выполняется со стороны get_lib
    bool keyHandler(uchar & key, cv::Rect2f & rct);
    int isFind();
    int getIDmain() {return num_main;}
    std::shared_ptr<std::list<trac_data>> getList();    // void execTKDNN(); ДЛЯ СЛУЧАЯ ВЫДЕЛЕНИЯ НН В ОТДЕЛЬНЫЙ ПОТОК
    std::shared_ptr<TracTKDNN> trac_nnet_ptr = nullptr;  // объект класса трекера


private:

    int num_main = 0;
    std::shared_ptr<Device> device = nullptr;				// источник видеопотока

    cv::Mat frame_process_tkdnn;    // кадр для обработки трекером

    int roi_mode = 0;				// признак работы в режиме ROI
    bool isRoiSetted = false;           // признак установки ROI
    cv::Rect2f roi = cv::Rect2f(0,0,0,0);       // текущий ROI

    cv::Rect2f aimRectShats = {0,0,0,0};
    int frame_show_width = 1920;
    int frame_show_height = 1080;

#ifdef GUI_OK
    int thik = 2;
    cv::Scalar clr_txt = cv::Scalar(64,64,64);
    cv::Scalar clr_main = cv::Scalar(200,200,200);
    float font_scale = 0.7;
#endif // GUI_OK

    bool get_ini_params(const string &config_path, const string &section);

}; // END class TKDNNContainer

#endif // TKDNN_CONTAINER_HPP
