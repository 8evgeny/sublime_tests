#ifndef WEBCAMERA_HPP
#define WEBCAMERA_HPP

#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <condition_variable>
#include <dirent.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <string>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "tools/watchdog.h"
#include "tools/INIReader.h"
#include "devices/device.hpp"

class WebCamera : public Device
{
public:
    WebCamera(){}
    ~WebCamera();
    WebCamera(const std::string &path_to_ini, bool &ok);
    void setup() override {return;};
    bool getState() override {return true;}
    void getFrame(cv::Mat& frame) override;
    int getFrameCounter() override;
    void keyHandler(uchar &key) override;
    void workflow() override;
    int getColorChannels() override;
    bool isBayerColorChannel() override;
    uint8_t *receiveFrame(int &w, int &h, int &id, int &num) override;
    void quit() override;    
    int getId() override;

private:
    std::unique_ptr<cv::VideoCapture> capturer = nullptr;
    // флаг нахождения программы в процессе выполнения
    std::atomic<bool> _execute = false;
    std::atomic<bool> handle_frame_execute = false;
    std::atomic<bool> frame_ready = false;
    std::chrono::system_clock::time_point tp_get_fr, tp_get_fr_cur;

    std::mutex frame_mutex;
    std::condition_variable frameCV;

    // временной интервал между кадрами, мс (обратно FPS )
    int sourceFrameDelay_ms = 0;

    void exec();
    bool getSettings(const std::string &path_to_ini) override;
    bool getNextFrame(cv::Mat& frame);
    void runHandleFrame();
    void getFormatedImage(uint8_t *f, int w, int h, int id, cv::Mat &image) override;

    cv::Mat frame;
    int frame_w = 1080 ;
    int frame_h = 1080 ;
    int fps = 30;
    int device_id = 0;
    int chann = 0;
    int frameCnt = 0;
}; // -- END class WebCamera : public Device

#endif // WEBCAMERA_HPP
