#ifndef RTP_SERVER_H264_HPP
#define RTP_SERVER_H264_HPP

#include <memory>
#include <condition_variable>
#include <atomic>

#include <gst/gst.h>

#include "rtp_server_h264_settings.hpp"
#include <chrono>
#include "../../modules/meta_struct/meta_struct.hpp"

namespace rtp
{


class RtpServerH264
{
public:
    RtpServerH264(rtp::server::h264::SettingsPtr &settings_ext);
    bool setup();
    bool start();
    bool stop();
    void newFrame(uint8_t *buffer, size_t size);
    void setMeta(Fenix2Meta & meta_ext);

private:
    friend void waitData(GstElement *appsrc, guint unused, RtpServerH264 *server);
    void workflow();

    GstElement *pipeline = nullptr;
    struct PipelineComponents
    {
        GstElement *appsrc = nullptr;
        GstElement *converter = nullptr;
        GstElement *encoder = nullptr;
        GstElement *rtppay = nullptr;
        GstElement *udpsink = nullptr;

    } components;
    GstBus *bus;
    GstMessage *msg;
    server::h264::SettingsPtr settings;
    GstBuffer *framebuffer = nullptr;
    struct Flags
    {
        bool inited = false;
        // std::atomic<bool> frameAvaliable;

    } state;
    struct Synchronisation
    {
        std::condition_variable frameReadyCv;
        std::mutex frameMtx;
        std::atomic<bool> execute = {false};
    } sync;

    ///meta data in header

    GstPad* rtph264pay_pad = nullptr;
    static std::atomic<bool> new_frame;
    static GstPadProbeReturn set_x_to_rtp_header1(GstPad *pad,
                                                  GstPadProbeInfo * info,
                                                  gpointer     user_data);
    static Fenix2Meta meta_data_srv_glob;
    static int num_frame_glob;

}; // END class RtpServerH264



} // END namespace rtp

#endif // RTP_SERVER_HPP
