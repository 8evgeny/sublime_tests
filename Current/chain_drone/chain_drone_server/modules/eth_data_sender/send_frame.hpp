#pragma once
#include "video_eth_controllers/gstcv_mjpg_eth_controller/gstcv_mjpg_eth_controller.hpp"
#include "video_eth_controllers/gstcv_mjpg_eth_controller/gstcv_mjpg_eth_controller_factory.hpp"

#include "modules/fenix2meta/fenix2meta_struct.hpp"
#include "modules/fenix2meta_sender/fenix2meta_sender.hpp"
#include "modules/fenix2meta_sender/fenix2meta_sender_factory.hpp"

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <thread>
#include <memory>

class EthSender
{
public:
    EthSender(std::string path2setting, bool & ok)
    {
        path2ini = path2setting;
        std::cout << " ------ BEGIN create frame_mjpg_eth_controller" << std::endl;
//rtp_eth::controller_V1::create();
        frame_mjpg_eth_controller = rtp_eth::controller_V1::create(path2ini, "gstcv_mjpg_eth_controller");
        ok = frame_mjpg_eth_controller->launch();
        if (!ok)
        {
            std::cout << "ERROR: launch frame_mjpg_eth_controller!" << std::endl;
        } // if (!ok)
        else
        {
            std::cout << " ------ END create frame_mjpg_eth_controller" << std::endl;
        } // END else

        fenix2meta_sender_ptr = fenix2meta_sender::create(path2ini, section_fenix2meta_sender);
        if(fenix2meta_sender_ptr == nullptr)
        {
            std::cout << "ERROR create bfenix2meta_sender_ptr!" << std::endl;
            ok = false;
            return;
        } // END if(trackmeta_sender == nullptr)
        if(!fenix2meta_sender_ptr->start())
        {
            std::cout << "ERROR start fenix2meta_sender_ptr!" << std::endl;
            ok = false;
            return;
        } // END if(!trackmeta_sender->start())
    }; // END SendFrame
    std::shared_ptr<rtp_eth::controller_V1::MJPGEthController> frame_mjpg_eth_controller = nullptr;
    std::shared_ptr<Fenix2MetaSender> fenix2meta_sender_ptr = nullptr;
private:

    std::string path2ini = "../fenix2_from_lib.ini";
    Fenix2Meta fenix2meta_data_now;
    std::string section_fenix2meta_sender = "fenix2meta_sender";
}; // END class EthSender
