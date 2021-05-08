#pragma once
#include "main.h"

class RadarDisplay {
public:
    RadarDisplay();
    ~RadarDisplay();

    virtual void run();
    void run_without_iteration();
    virtual void stop();
    virtual void wait_shutdown();
    virtual void accept_radar_message(const std::shared_ptr<RadarMessage>&);
    void set_callback(const std::function<void()>&);
    static void display_objects(bool);
    static cv::Point3d transform(double x, double y, double z);
    bool transformToPerspective = false;
    static cv::Point k(cv::Point3d one, cv::Point3d two); //коэфф глубины для перспективы
    static cv::Point3d k3(cv::Point3d one, cv::Point3d two);

private:
    CThread thread;
    bool is_display_flag = false;
    std::function<void()> display = nullptr;
};
