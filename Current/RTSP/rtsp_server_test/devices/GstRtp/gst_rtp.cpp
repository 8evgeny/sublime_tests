#include "gst_rtp.hpp"
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

using namespace devices;
using namespace devices::gst_rtp;

GstRtp::GstRtp(const devices::gst_rtp::UserSettings &settings) : settings(settings)
{

} // -- GstRtp::GstRtp

GstRtp::~GstRtp()
{
    quit();
} // -- GstRtp::~GstRtp()

void GstRtp::setup()
{    
    switch(settings.camera_mode)
    {
        case CAM_MODE_1920_1080_60FPS:
            gen_settings.video = VideoSettings(1920, 1080, 60);
        break;

        case CAM_MODE_3840_2160_30FPS:
            gen_settings.video = VideoSettings(3840, 2160, 30);
        break;

        case CAM_MODE_4032_3040_20FPS:
            gen_settings.video = VideoSettings(4032, 3040, 20);
        break;

        default:
            std::cout << "ERROR: failed recognize GstRtp camera_mode, check ini-file. Use default 4K@30fps" << std::endl;
            gen_settings.video = VideoSettings(3840, 2160, 30);
        break;
    };

    gen_settings.output.max_buffers = settings.max_buffers;
    gen_settings.camera.sensor_id = settings.sensor_id;
    gen_settings.output.fps = static_cast<int>(gen_settings.video.fps / settings.fps_denominator);
    use_videorate = gen_settings.output.fps != gen_settings.video.fps;

#if defined(CCM_8UC1)

    pipeline =
        "nvarguscamerasrc "
        "! video/x-raw(memory:NVMM)"
            ", width=(int)" + std::to_string(gen_settings.video.width) +
            ", height=(int)" + std::to_string(gen_settings.video.height) +
            ", format=(string)NV12"
            ", framerate=(fraction)" + std::to_string(gen_settings.video.fps) + "/1 "
        "! nvvidconv ";
    if(use_videorate)
    {
        pipeline +=
            "! videorate "
            "! video/x-raw"
                ", format=(string)GRAY8"
                ", framerate=(fraction)" + std::to_string(gen_settings.output.fps) + "/1 ";
    }
    else
    {
        pipeline +=
            "! video/x-raw"
                ", format=(string)GRAY8 ";

    }
    pipeline +=
        "! appsink max-buffers=" + std::to_string(gen_settings.output.max_buffers) + " drop=True";

#elif defined(CCM_8UC3)
    /*
    Преобразование цвета COLOR_YUV2BGR_I420 I420->BGR не интегрировано в pipeline,/
    т.к. получается большая задержка между входом и выходом, что приводит к замедлению отклика
    на изменение состояния регистрируемой сцены пространства предметов;
    */
    pipeline =
        "nvarguscamerasrc "
        "! video/x-raw(memory:NVMM)"
            ", width=(int)" + std::to_string(gen_settings.video.width) +
            ", height=(int)" + std::to_string(gen_settings.video.height) +
            ", format=(string)NV12"
            ", framerate=(fraction)" + std::to_string(gen_settings.video.fps) + "/1 "
        "! nvvidconv ";

    if(use_videorate)
    {
        pipeline +=
            "! videorate "
            "! video/x-raw"
                ", format=(string)I420 "
                ", framerate=(fraction)" + std::to_string(gen_settings.output.fps) + "/1 ";
    }
    else
    {
        pipeline +=
            "! video/x-raw"
                ", format=(string)I420 ";

    }
    pipeline +=
        "! appsink max-buffers=" + std::to_string(gen_settings.output.max_buffers) +  " drop=True";
#else
    throw std::runtime_error("Not supported color space for output format");
#endif
    std::cout << "Pipeline: " << pipeline << std::endl;
} // -- END GstRtp::setup()

void GstRtp::start()
{
    gst_cap.open(pipeline, cv::CAP_GSTREAMER);
    if(!gst_cap.isOpened()) 
    {
	    std::cout << "Error: Failed to open pipeline." << std::endl;
        return;
    }
    std::cout << "GstRtp::start() -- Pipeline success create!\n";

    std::thread(&GstRtp::exec, this).detach(); // поток извлечения кадров из pipeline
} // -- END GstRtp::start()

void GstRtp::exec()
{
    //считываем первый кадр и определяем его параметры, сравниваем с запрашиваемыми
    cv::Mat first_receive_frame;
    if(!gst_cap.read(first_receive_frame))
    {
        std::cout << " --- Pipeline stop frame flow" << std::endl;
        quit();
        return;
    }

    /*
        Для GRAY8 CV_8UC1 и для I420 CV_8UC1 
        (для I420 высота изображения x1.5, т.к. содержит сегменты, 
        в которых отображаются параметры цветности. 
        см. техническую документацию I420 формата изображения)
    */
    int input_frame_type = CV_8UC1;
    if(first_receive_frame.type() != input_frame_type)
    {
        throw std::runtime_error("Error: required and received frames color types not equal!");
    }

    /*
    Сравнение резрешения запрашиваемых в gstreamer конвейере и полученных изображений
    */
#if defined(CCM_8UC1)
    if(first_receive_frame.cols != gen_settings.video.width || 
        first_receive_frame.rows != gen_settings.video.height)
#elif defined(CCM_8UC3)
    if(first_receive_frame.cols != gen_settings.video.width ||
        first_receive_frame.rows != 1.5 * gen_settings.video.height)
#endif
    {
        throw std::runtime_error("Error: required and received frames sizes not equal");
    }

#if defined(CCM_8UC1)
    int required_output_frame_type_cv = CV_8UC1;
#elif defined(CCM_8UC3)
    int required_output_frame_type_cv = CV_8UC3;
#else
    throw std::runtime_error("Not supported color space for output format");
#endif

    if(
        gen_settings.video.width < settings.square_crop_sz || 
        gen_settings.video.height < settings.square_crop_sz    
    )
    {
        std::cout << "ERROR: GstRtp square_crop_sz > video.width || video.height, use default settings" << std::endl;
        settings.square_crop_sz = std::min(gen_settings.video.width, gen_settings.video.height);
    }

    cv::Size input_frame_size = first_receive_frame.size(); // gstreamer to device map sz
    cv::Size camera_frame_size( gen_settings.video.width,   gen_settings.video.height);
    cv::Size crop_frame_size(   settings.square_crop_sz,    settings.square_crop_sz);
    cv::Size output_frame_size( settings.square_out_sz,     settings.square_out_sz); // device to application

    need_io_resize = crop_frame_size != output_frame_size;

    frame_receive =         cv::Mat(input_frame_size,   input_frame_type); // выделяем память под рабочий принимаемый перезаписываемый кадр
#if defined(CCM_8UC3)
    frame_intermediate =    cv::Mat(camera_frame_size,  required_output_frame_type_cv);
#endif 
    frame_crop =            cv::Mat(crop_frame_size,    required_output_frame_type_cv);
    if(need_io_resize)
    {
        std::cout << "DBG:: need io resize enable" << std::endl;
        frame_prepared =    cv::Mat(output_frame_size,  required_output_frame_type_cv);
    }   
    else
    {
        frame_prepared =    frame_crop;
    }

    //frame_receive ==> frame_intermediate ==> frame_crop ==> frame_prepared (для конфигурация CCM)

    frame_request_delay_ms = 1000 / gen_settings.output.fps;

    cv::Rect2i crop_roi(
        camera_frame_size.width / 2 - crop_frame_size.width / 2,
        camera_frame_size.height / 2 - crop_frame_size.height / 2,
        crop_frame_size.width, 
        crop_frame_size.height
    );
 
    sync.execute.store(true);
    while(sync.execute.load())
    {
        std::chrono::system_clock::time_point timePoint =
                std::chrono::system_clock::now() +
                std::chrono::milliseconds(frame_request_delay_ms);
        gst_cap >> frame_receive;
        if(frame_receive.empty()) 
        {
            std::cout << " --- Pipeline stop frame flow" << std::endl;
            quit();
            break;
        }
#if defined(CCM_8UC1)
        frame_receive(crop_roi).copyTo(frame_crop);
        if(need_io_resize)
        {
            cv::resize(frame_crop, frame_prepared, output_frame_size, cv::InterpolationFlags::INTER_NEAREST);
        }
#elif defined(CCM_8UC3) 
        cv::cvtColor(frame_receive, frame_intermediate, cv::COLOR_YUV2BGR_I420);
        frame_intermediate(crop_roi).copyTo(frame_crop);
        if(need_io_resize)
        {
            cv::resize(frame_crop, frame_prepared, output_frame_size, cv::InterpolationFlags::INTER_NEAREST);
        }
#else
    throw std::runtime_error("Not supported color space for output format");
#endif
        
    for(auto handler : frame_handlers)
    {
        handler->handle(frame_prepared.data, frame_prepared.cols,
                        frame_prepared.rows, 0, frame_id);
    } // -- END for(auto handler : frame_handlers)
    frame_id++;
    std::this_thread::sleep_until(timePoint);
    } // -- END while(sync.handleFrameExecute.load(std::memory_order_acquire))
    gst_cap.release();
    sync.exec_complete.store(true);
} // -- END GstRtp::exec()

void GstRtp::quit()
{
    if(sync.quit_was_call.load())
    {
        return;
    }
    std::cout << "TRY close GstRtp" << std::endl;
    sync.quit_was_call.store(true);
    sync.execute.store(false);
    std::chrono::system_clock::time_point tp_wd = std::chrono::system_clock::now() + std::chrono::milliseconds(watchdog_close_time_ms);
    while(!sync.exec_complete.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(std::chrono::system_clock::now() > tp_wd)
        {
            std::cout << "FORCE quit GstRtp" << std::endl;
            gst_cap.release();
            break;
        }
    }
    std::cout << "SUCCESS close GstRtp" << std::endl;
    
    // std::cout << "GstRtp::quit() -- gst pipeline success closed\n";
} // -- GstRtp::quit()

// uint8_t* GstRtp::receiveFrame(int &w, int &h, int &id, int &num)
// {
//     if(sync.frame_ready.load())
//     {
//         sync.frameMtx.lock();
//         w = frame_prepared.cols; 
//         h = frame_prepared.rows;
//         id = 0;
//         num = frame_id;
//         sync.frameMtx.unlock();
//         sync.frame_ready.store(false);
//         return frame_prepared.data;
//     }
//     return nullptr;    
// }

void GstRtp::getFormatedImage(uint8_t * dat, int w, int h, int id, cv::Mat & image)
{
#if defined(CCM_8UC1)
    memcpy(image.data, dat, image.total());
#elif defined(CCM_8UC3)
    memcpy(image.data, dat, 3*image.total());
#else
    throw std::runtime_error("Not supported color space for output format");
#endif
} // END getFormatedImage

bool GstRtp::isBayerColorChannel()
{
    return false;
} // -- END GstRtp::isBayerColorChannel()

void GstRtp::keyHandler(uchar &key)
{

} // -- END GstRtp::keyHandler(char &key)

void GstRtp::workflow()
{

} // -- END GstRtp::workflow()

int GstRtp::getColorChannels()
{
#if defined(CCM_8UC1)
    return 1;
#elif defined(CCM_8UC3)
    return 3;
#else
    return 0;
#endif
} // -- END GstRtp::getColorChannels()

