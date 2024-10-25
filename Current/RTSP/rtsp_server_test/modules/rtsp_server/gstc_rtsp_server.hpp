#ifndef GSTC_RTSP_SERVER_HPP
#define GSTC_RTSP_SERVER_HPP

#include <gst/gst.h>
#include "gst-rtsp-server/gst/rtsp-server/rtsp-server.h"
#include "gst/rtp/gstrtcpbuffer.h"
#include "gst/app/gstappsrc.h"

//#include "gstreamer-1.0/gst/rtp/gstrtpbuffer.h"

#include "gstc_rtsp_server_settings.hpp"

#include "opencv2/core.hpp"
#include "condition_variable"
#include "thread"
#include <atomic>
#include <string>
#include <functional>
#include <chrono>

namespace rtsp::server
{

typedef struct
{
  gboolean white;
  GstClockTime timestamp;
} MyContext;

class RTSPServer
{
public:
    RTSPServer();
    ~RTSPServer();
    RTSPServer(SettingsRtspSrv settings_);
    void newFrame(cv::Mat & frame);
    bool setup();
    bool start();
    void play();
    void pause();
    void stop();

private:
    SettingsRtspSrv settings;
    std::string pipeline_str;
    cv::Mat enter_image0;
    cv::Mat enter_image1;

    // RTSP server params
    GMainLoop *loop;
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *factory;
    GstClockTime timestamp;

    // callback params
    GstBuffer *framebuffer;
    guint buffer_size = 1920 * 1080 * 3;
    GstFlowReturn ret;

    bool inited = false;
    bool f_first_call = true;
    // pipeline components
    GstElement *appsrc;
    GstElement *encoder;
    GstElement *converter;
    GstElement *pay;
    GstElement *shmsink;
    GstElement *pipeline;

    GstBus *bus;
    GstMessage *msg;

    struct Synchronisation
    {
        std::condition_variable frameReadyCv;
        std::mutex frameMtx;
        std::atomic<bool> execute = {false};
    } sync;
    static std::atomic<bool> new_frame;

    void exec();
    void setAppSrcSettings(GstRTSPMedia * media); // устанавливаем размер изображения, фпс, формат данных и т.п.
    void setEncoderSettings(GstRTSPMedia * media); // параметры x264enc(desctop) mpph264enc(khadas)
    void setPaySettings(GstRTSPMedia * media);
    void setSrvSettings(GstRTSPServer * server); // установка ip и port
    // разрешили callback функциям доступ к приватным переменным
    friend void need_data(GstElement * appsrc, guint unused, RTSPServer * server);
    friend void media_configure (GstRTSPMediaFactory * factory, GstRTSPMedia * media,  RTSPServer * server);
}; // END class RTSPServer

}; // END namespace rtsp
#endif //!GSTC_RTSP_SERVER_HPP
