#include "webcamera.hpp"
#include <thread>

WebCamera::WebCamera(const std::string &path_to_ini, bool &ok)
{
    ok = false;
    if(getSettings(path_to_ini))
    {
        capturer = new cv::VideoCapture();
        std::cout << "WebCamera::WebCamera:: capture open is " << capturer->open(device_id) << std::endl;

        if(capturer->isOpened())
        {

            if (!frameWidth || !frameHeight)
            {
                cv::Mat img_buf;
                capturer->read(img_buf);
                frameWidth = img_buf.cols;
                frameHeight = img_buf.rows;
                std::cout << "WebCamera::WebCamera AUTOSETTINGS FRAME SIZE: frame w,h = " << cv::Point(frameWidth, frameHeight) << std::endl;

            }
            std::cout << "w,h,channels,fps = " << cv::Rect(frameWidth, frameHeight, getColorChannels(), fps) << std::endl;
            capturer->set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
            capturer->set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);
            capturer->set(cv::CAP_PROP_BUFFERSIZE, getColorChannels());
            capturer->set(cv::CAP_PROP_FPS, fps);
            ok = true;
            std::thread execution(&WebCamera::exec, this);
            execution.detach();
        } // if(capturer->isOpened())
    } // END if(getSettings)
} // -- END WebCamera::WebCamera

WebCamera::~WebCamera()
{
    std::cout << "Деструктор WebCamera : Device" << std::endl;
    delete capturer;
} // -- END WebCamera::~WebCamera()

void WebCamera::keyHandler(uchar &key)
{
    return void();
}

void WebCamera::workflow()
{
    return void();
}

int WebCamera::getColorChannels()
{
#ifdef CCM_8UC1
    return 1;
#elif CCM_8UC3
    return 3;
#endif // CCM_8UC1/3
}

bool WebCamera::isBayerColorChannel()
{
    return false;
}

uint8_t *WebCamera::receiveFrame(int &w, int &h, int &id, int &num)
{
    if(frame_ready.load())
    {
        frame_mutex.lock();
        w = frame.cols;
        h = frame.rows;
        frame_mutex.unlock();
        frame_ready.store(false, std::memory_order_release);
        return frame.data;
    }
    return nullptr;
}

void WebCamera::quit()
{
    handle_frame_execute.store(false, std::memory_order_release);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void WebCamera::exec()
{
    _execute.store(true, std::memory_order_release);
    handle_frame_execute.store(true, std::memory_order_release);
    std::thread frameHandler(&WebCamera::runHandleFrame, this);
    while(_execute.load(std::memory_order_acquire))
    {
        std::chrono::system_clock::time_point timePoint =
                std::chrono::system_clock::now() +
                std::chrono::milliseconds(sourceFrameDelay_ms);
        getNextFrame();
        std::this_thread::sleep_until(timePoint);
    }
    handle_frame_execute.store(false, std::memory_order_release);
    frameCV.notify_one();
    frameHandler.join();
}

bool WebCamera::getSettings(const std::string &path_to_ini)
{
    INIReader reader(path_to_ini);
    if(reader.ParseError() < 0){
        std::cout << "ini reader: Parse error";
        return false;
    }

    int width = reader.GetInteger("webcamera", "frame_width", -1);
    if(width == -1)
    {
        std::cout << "ini reader: Parse width error\n";
        return false;
    }
    else
        frameWidth = width;

    int height = reader.GetInteger("webcamera", "frame_height", -1);
    if(height == -1){
        std::cout << "ini reader: Parse height error\n";
        return false;
    }
    else
        frameHeight = height;

    int fps_ = reader.GetInteger("webcamera", "fps", -1);
    if(fps_ == -1){
        std::cout << "ini reader: Parse fps error\n";
        return false;
    }
    else
        fps = fps_;

    int fps = reader.GetInteger("webcamera", "fps", -1);
    if(fps == -1)
    {
        std::cout << "ini reader: Parse source fps name error\n";
        return false;
    }
    else
    {
        sourceFrameDelay_ms = 1000 / fps;
    }

    device_id = reader.GetInteger("webcamera", "device_id", -1);
    if(device_id == -1)
    {
        std::cout << "ini reader: Parse source [webcamera]:device_id name error\n";
        return false;
    }

    std::cout << "WebCamera get settings success" << std::endl;

    return true;
}

bool WebCamera::getNextFrame()
{
    frame_mutex.lock();
    capturer->read(frame);
    if(!frame.empty())
    {
#if defined(CCM_8UC1)
        if(frame.channels() == 3)
        {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        }
#elif defined(CCM_8UC3)
        if(frame.channels() == 1)
        {
            cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);
        }
#else
        throw std::runtime_error("Not supported color space for output format");
#endif
        frame_ready.store(true, std::memory_order_release);
        frameCV.notify_one();
        frame_mutex.unlock();
        return true;
    }
    frame_mutex.unlock();
    return false;
}

void WebCamera::runHandleFrame()
{
    while(handle_frame_execute.load(std::memory_order_acquire))
    {
        std::unique_lock<std::mutex> lk(frame_mutex);
        frameCV.wait(lk);
        if(!handle_frame_execute.load(std::memory_order_acquire))
        {
            break;
        }
        for(auto handler : frame_handlers)
        {
            handler->handle(frame.data, frame.cols, frame.rows, 0, 0);
        }
        frame_ready.store(false, std::memory_order_release);
        lk.unlock();
    }
}

void WebCamera::getFormatedImage(uint8_t *f, int w, int h, int id, cv::Mat &image)
{
#if defined(CCM_8UC1)
    memcpy(image.data, f, image.total());
#elif definec(CCM_8UC3)
    memcpy(image.data, f, 3*image.total());
#else
    throw std::runtime_error("Not supported color space for output format");
#endif
}
