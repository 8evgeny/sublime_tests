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
        thread.run_without_iteration();
        is_display_flag = true;
    }
}

void RadarDisplay::stop()
{
}

void RadarDisplay::wait_shutdown()
{
}

void RadarDisplay::accept_radar_message(const std::shared_ptr<RadarMessage>& message)
{
}
