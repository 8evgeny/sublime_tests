#ifndef MULTITRAC_HPP
#define MULTITRAC_HPP

#include <iostream>
#include <opencv2/imgproc.hpp>
#include "tracshats/tracshats.hpp"
#include <list>
#include <iterator>
#include "tools/colors.h"
#include "devices/device.hpp"
#include "devices/iframehandler.h"
#include "tools/ExtendINIReader.hpp"
#include "multitrac/trac_container.hpp"

namespace mtrac
{

enum CmdMultitrac
{
    ADD_TRAC,
    REMOVE_TRAC,
    QUIT
}; // END CmdMultitrac

struct withUnique
{
    int b;
    std::unique_ptr<std::list<int>> a = nullptr;
};

class Multitrac
{
public:
    Multitrac();
    Multitrac(const std::string & config_path, cv::Mat & frame, std::shared_ptr<Device> * device_,  bool & ok);
    ~Multitrac() {std::cout << "Multitrac::Destructor!\n";}
    void cmdHandler(uchar key);
    bool add_trac(Rect2f & rectm, cv::Mat & frame_receive, cv::Mat & frame_show, std::shared_ptr<Device> * device_, int id_ = -1);
    bool remove_trac();
    void update(cv::Mat & frame_receive, cv::Mat & frame_show);
    void prepare_v_trac(cv::Mat & frame_receive);
    void set_new_frame(bool flag);
    int get_ltrac_size() {return l_trac_ptr.size();}
    std::list<std::shared_ptr<mtrac::TracContainer>> l_trac_ptr;
    std::list<std::shared_ptr<mtrac::TracContainer>>::iterator iter_now;
private:
    withUnique ptr;
    int pos_main = 0;
    int num_trac_max = 1;
    std::string config_path;
}; // END class Multitrac

}; // END namespace mtrac
#endif // MULTITRAC_HPP
