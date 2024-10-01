#ifndef RTP_CLIENT_H264_HPP
#define RTP_CLIENT_H264_HPP

#include <memory>
#include <atomic>
#include <condition_variable>

#include "../../modules/meta_struct/meta_struct.hpp"
#include <gst/gst.h>

#include <opencv2/core.hpp>

#include "rtp_client_raw_settings.hpp"

namespace rtp
{
class RtpClientRAW
{
public:
    RtpClientRAW(client::raw::SettingsPtr &settings);
    bool setup();
    bool start();
    bool stop();
    bool is_execute();
    bool frame(cv::Mat &frame, Fenix2Meta &fenix2meta_data);
    //time_data meta_cli;
//    Fenix2Meta fenix2meta_data;
private:
    friend void newData(GstElement *appsrc, RtpClientRAW *client);
    void workflow();

    std::string enc_type = "h264";



    GstElement *pipeline = nullptr;
    struct PipelineComponents
    {
        GstElement *udpsrc = nullptr;
        GstElement *rtpdepay = nullptr;
        GstElement *parser = nullptr;
        GstElement *decoder = nullptr;
        GstElement *converter = nullptr;
        GstElement *queue = nullptr;
        GstElement *watchdog = nullptr;
        GstElement *appsink = nullptr;
        GstElement *autovideosink = nullptr;
    } components;
    client::raw::SettingsPtr settings;
    GstBuffer *framebuffer = nullptr;
    GstMapInfo map;
    int frame_byte_len = 0;
    struct Flags
    {
        bool inited = false;

    } state;
    struct Synchronisation
    {
        std::condition_variable frameReadyCv;
        std::mutex frameMtx;
        std::atomic<bool> frameReady = {false};
        std::atomic<bool> execute = {false};
    } sync;

    ///meta data in header
    GstPad *rtph264depay_sink_pad = nullptr;

    static GstPadProbeReturn get_x_from_rtp_header (GstPad          *pad,
                                                    GstPadProbeInfo *info,
                                                    gpointer         user_data);
    static std::atomic<bool> new_frame;
    static Fenix2Meta fenix2meta_data_glob;

}; 
}

#endif // RTP_CLIENT_HPP
