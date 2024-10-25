#ifndef MYSERVER_HPP
#define MYSERVER_HPP

#include <iostream>
#include "stdint.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "gst/gst.h"
#include "gst-rtsp-server/gst/rtsp-server/rtsp-server.h"
#include "gst/rtp/gstrtcpbuffer.h"
#include "gst/app/gstappsrc.h"
#include <thread>
#include <atomic>


namespace rtspsrv
{
//using namespace std;
//using namespace cv;
typedef struct
{
    gboolean white;
    GstClockTime timestamp;
} MyContext;

//std::atomic<uchar> key = 255;

struct RTSPSettings
{
    gint frame_w = 1920;
    gint frame_h = 1080;
    gfloat fps = 30;
};

//bool readRTSPSrvSettings(std::string & config_path, std::string & ini_section_name, bool & ok)
//{
//    ok = true;
//} // END readRTSPSrvSettings

//static bool need_fill_buffer = false;
//gint img_w = 1920;
//gint img_h = 1080;
//float fps = 30;

/* Вызывется при необходимости запушить data на appsrc */
static void need_data(GstElement * appsrc, guint unused, MyContext * ctx); // END static void need_data(GstElement * appsrc, guint unused, MyContext * ctx)

/* Вызывается при создании нового еда пайплайна, мы можем запросить пайплайн и настроить источник (appsrc)*/

static void media_configure(GstRTSPMediaFactory * factory, GstRTSPMedia * media, gpointer user_data); // -- END media_configure

void set_image(cv::Mat img_); // -- END set_image

int gst_loop(); // -- END gst_loop
}; // END namespace rtspsrv




#endif //!MYSERVER_HPP
