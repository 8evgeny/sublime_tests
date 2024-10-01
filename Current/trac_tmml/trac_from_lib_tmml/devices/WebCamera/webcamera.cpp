#include "webcamera.hpp"

using namespace std;
using namespace cv;

WebCamera::~WebCamera()
{
    cout << "Деструктор WebCamera : Device" << endl;
    capturer->release();
} // -- END WebCamera::~WebCamera()

WebCamera::WebCamera(const string& path_to_ini, bool& ok)
{
    cout << "Begin Constructor WebCamera\n";
    ok = getSettings(path_to_ini);
    if(!ok){return;}

    capturer = make_unique<VideoCapture>();
    cout << "WebCamera::WebCamera:: capture open is " << capturer->open(device_id) << endl;
    if(capturer->isOpened())
    {
        if(!frame_w || !frame_h)
        {
            Mat img_buf;
            capturer->read(img_buf);
            frame_w = img_buf.cols;
            frame_h = img_buf.rows;
            chann = img_buf.channels();
            cout << "WebCamera AUTOSETTINGS FRAME SIZE: frame w; h; chann = [" << frame_w << "; " << frame_h << "; " << chann << "]\n";
            imshow("first_frame", img_buf);
            unsigned char key = waitKey(1000);
            destroyWindow("first_frame");
        } // END if(!frameWidth || !frameHeight)
        int color_chann = getColorChannels();
        cout << "SET =========== w; h; channels; fps = [" << frame_w << "; " << frame_h << "; " << color_chann << "; " << fps << "]\n";
        //capturer->set(CAP_PROP_FRAME_WIDTH, frameWidth);
        //capturer->set(CAP_PROP_FRAME_HEIGHT, frameHeight);
        capturer->set(CAP_PROP_BUFFERSIZE, 10);
        capturer->set(CAP_PROP_FPS, fps);
        int fr_w0 = int(capturer->get(CAP_PROP_FRAME_WIDTH));
        int fr_h0 = int(capturer->get(CAP_PROP_FRAME_HEIGHT));
        int chann0 = int(capturer->get(CAP_PROP_CHANNEL));
        int fps0 = int(capturer->get(CAP_PROP_FPS));
        cout << "GET ==================== w; h; channels; fps = [" << fr_w0 << "; " << fr_h0 << "; " << chann0 << "; " << fps0 << "]\n";
        //if(!fr_w0 || !fr_h0 || !fps0 || !fps0){ok = 0; return;}
        ok = 1;
    } // END if(capturer->isOpened())
    else
    {
        cout << "=============== capturer is NOT Opened !!! \n";
        ok = 0;
        return;
    } // END if(NOT capturer->isOpened())

    tp_get_fr = chrono::high_resolution_clock::now();
    thread execution(&WebCamera::exec, this);
    execution.detach();
    cout << "END Constructor WebCamera\n";
} // -- END WebCamera

void WebCamera::keyHandler(uchar &key)
{
    return void();
} // END keyHandler

int WebCamera::getColorChannels()
{
#ifdef CCM_8UC1
    return 1;
#elif CCM_8UC3
    return 3;
#endif // CCM_8UC1/3
} // END getColorChannels

bool WebCamera::isBayerColorChannel()
{
    return false;
} // END isBayerColorChannel

void WebCamera::workflow(){ }

uint8_t *WebCamera::receiveFrame(int &w, int &h, int &id, int &num)
{
    if(frame_ready.load())
    {
        frame_mutex.lock();
        w = frame.cols;
        h = frame.rows;
        return frame.data;
        frame_mutex.unlock();
        frame_ready.store(false);
    }
    return nullptr;
} // -- END receiveFrame

void WebCamera::getFrame(Mat& frame)
{
    tp_get_fr_cur = chrono::high_resolution_clock::now();
    tp_get_fr = chrono::high_resolution_clock::now();
    bool success = getNextFrame(frame);
} // -- END getFrame

int WebCamera::getFrameCounter()
{
    return frameCnt;
} // -- END getFrameCounter

void WebCamera::getFormatedImage(uint8_t *f, int w, int h, int id, Mat &image)
{

    Mat img_buf(Size(w,h), image.type());
#if defined(CCM_8UC1)
    memcpy(img_buf.data, f, img_buf.total());
#elif defined(CCM_8UC3)
    memcpy(img_buf.data, f, 3*img_buf.total());
#else
    throw runtime_error("Not supported color space for output format");
#endif

    Rect rct(round(0.5 * (w - h)), 0, h, h);
    image = img_buf(rct).clone();
    resize(image, image, Size(frame_w, frame_h));
} // END getFormatedImage

void WebCamera::quit()
{
    _execute.store(false, memory_order_release);
    this_thread::sleep_for(chrono::milliseconds(sourceFrameDelay_ms * 2));
} // -- END quit

int WebCamera::getId()
{
   return frame_id;
} // END -- getId

void WebCamera::exec()
{
    _execute.store(true, memory_order_release);
    handle_frame_execute.store(true, memory_order_release);
    thread frameHandler(&WebCamera::runHandleFrame, this);
    WatchDog timer(1000);
    bool success = 0;
    while(_execute.load(memory_order_acquire))
    {
        chrono::system_clock::time_point timePoint = chrono::system_clock::now() + chrono::milliseconds(sourceFrameDelay_ms);
        success = getNextFrame(frame);
        if(!success)
        {
            break;
        } // END if(!success)
        this_thread::sleep_until(timePoint);
        // this_thread::sleep_for(chrono::milliseconds(sourceFrameDelay_ms));
    } // -- END while(_execute.load(memory_order_acquire))
    handle_frame_execute.store(false, memory_order_release);
    frameCV.notify_one();
    frameHandler.join();
    quit();
} // -- END exec

bool WebCamera::getSettings(const string &path_to_ini)
{
    INIReader reader(path_to_ini);
    if(reader.ParseError() < 0)
    {
        cout << "ini reader: Parse error";
        return false;
    }

    frame_w = reader.GetInteger("webcamera", "frame_width", -1);
    if(frame_w == -1)
    {
        cout << "ini reader: Parse width error\n";
        return 0;
    }


    frame_h = reader.GetInteger("webcamera", "frame_height", -1);
    if(frame_h == -1){
        cout << "ini reader: Parse height error\n";
        return false;
    }

    fps = reader.GetInteger("webcamera", "fps", -1);
    if(fps == -1)
    {
        cout << "ini reader: Parse source fps name error\n";
        return false;
    }
    sourceFrameDelay_ms = 1000 / fps;

    device_id = reader.GetInteger("webcamera", "device_id", -1);
    if(device_id == -1)
    {
        cout << "ini reader: Parse source [webcamera]:device_id name error\n";
        return false;
    }
    cout << "WebCamera get settings success" << endl;
    return true;
} // END getSettings

bool WebCamera::getNextFrame(Mat& frame)
{
        frame_id++;
        capturer->read(frame);
        if(!frame.data){cout << "NOT data for frame" << endl; return 1;}
#if defined(CCM_8UC1)
        cvtColor(frame, frame, COLOR_BGR2GRAY);
#elif defined(CCM_8UC3)
        cvtColor(frame, frame, COLOR_GRAY2BGR);
#endif
        frame_ready.store(true, memory_order_release);
        frameCV.notify_one();
        return 1;
} // -- END getNextFrame

void WebCamera::runHandleFrame()
{
    while(handle_frame_execute.load(memory_order_acquire))
    {
        unique_lock<mutex> lk(frame_mutex);
        frameCV.wait(lk);
        if(!handle_frame_execute.load(memory_order_acquire))
        {
            break;
        }
        for(auto handler : frame_handlers)
        {
            handler->handle(frame.data, frame.cols, frame.rows, 0, 0);
        } // -- END for(auto handler : frame_handlers)
        lk.unlock();
        frame_ready.store(false, memory_order_release);
    } // -- END while
} // -- END runHandleFrame
