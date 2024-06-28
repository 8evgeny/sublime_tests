#ifndef WEBCAMERA_HPP
#define WEBCAMERA_HPP

#include <string>
#include <atomic>
#include <condition_variable>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "tools/INIReader.h"
#include "devices/device.hpp"





class WebCamera : public Device
{
public:
    WebCamera(){}
    ~WebCamera();
    WebCamera(const std::string &path_to_ini, bool &ok);
    void setup() override {return;};
    void start() override {return;};
    bool getState() override {return true;}

    void keyHandler(uchar &key) override;
    void workflow() override;
    int getColorChannels() override;
    bool isBayerColorChannel() override;
    uint8_t *receiveFrame(int &w, int &h, int &id, int &num) override;
    void quit() override;

private:
    cv::VideoCapture *capturer = nullptr;
    // флаг нахождения программы в процессе выполнения
    std::atomic<bool> _execute = false;
    std::atomic<bool> handle_frame_execute = false;
    std::atomic<bool> frame_ready = false;

    std::mutex frame_mutex;
    std::condition_variable frameCV;

    // временной интервал между кадрами, мс (обратно FPS )
    int sourceFrameDelay_ms = 0;

    void exec();
    bool getSettings(const std::string &path_to_ini) override;
    bool getNextFrame();
    void runHandleFrame();
    void getFormatedImage(uint8_t *f, int w, int h, int id, cv::Mat &image) override;

    cv::Mat frame;
    int frameWidth = 1920;
    int frameHeight = 1080;
    int fps = 30;
    int device_id = 0;
}; // -- END class WebCamera : public Device

#endif // WEBCAMERA_HPP
