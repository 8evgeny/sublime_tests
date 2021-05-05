#include "RadarDisplay.h"

RadarDisplay::RadarDisplay()
{
}

RadarDisplay::~RadarDisplay()
{
}

void RadarDisplay::set_callback(const std::function<void()>& set_callback)
{
    printf("Setting new callback  \n");
    display = set_callback;
    thread.set_iteration_callback(display);
}

void RadarDisplay::run()
{
    if (!is_display_flag) {
        printf("Display starting \n");
        thread.run();
        is_display_flag = true;
    }
}

void RadarDisplay::run_without_iteration()
{
    if (!is_display_flag) {
        printf("Display starting \n");
        thread.run_without_iteration();
        is_display_flag = true;
    }
}

void RadarDisplay::stop()
{
    if (is_display_flag) {
        printf("Thread stop \n");
        thread.stop();
        is_display_flag = false;
    }
}

void RadarDisplay::wait_shutdown()
{
    printf("Thread joined \n");
    thread.join();
}

void RadarDisplay::accept_radar_message(const std::shared_ptr<RadarMessage>& message)
{
}
