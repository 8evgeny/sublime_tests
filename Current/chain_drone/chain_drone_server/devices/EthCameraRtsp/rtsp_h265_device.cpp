#include "rtsp_h265_device.hpp"

using namespace std;
using namespace devices;
using namespace devices::rtsp_h265_device;


#include <thread>

#include <gst/app/gstappsink.h>

#ifdef GUI_OK
#include <opencv2/highgui.hpp>
#endif //GUI_OK
#include <opencv2/imgproc.hpp>

using namespace devices;
using namespace devices::rtsp_h265_device;



namespace devices
{
void newData(GstElement *appsink, RTSP_H265_device *client)
{
    std::lock_guard lock(client->sync.frameMtx);
    GstSample *sample = gst_app_sink_pull_sample(GST_APP_SINK(appsink));
    if (sample == NULL)
    {
        fprintf(stderr, "gst_app_sink_pull_sample returned null\n");
        return;
    }
    GstBuffer *buffer = gst_sample_get_buffer(sample);
    gst_buffer_map(buffer, &client->map, GST_MAP_READ);

    gst_buffer_unmap(buffer, &client->map);

    gst_sample_unref(sample);

    client->frameCnt++;
    client->sync.frameReady.store(true);
    client->sync.frameReadyCv.notify_one();
} // END newData

static gboolean my_bus_callback(GstBus *bus, GstMessage *message, gpointer data)
{
    // Debug message
    //g_print("Got %s message\n", GST_MESSAGE_TYPE_NAME(message));
    switch(GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_ERROR:
    {
        GError *err;
        gchar *debug;

        gst_message_parse_error(message, &err, &debug);
        g_print("Error: %s\n", err->message);
        g_error_free(err);
        g_free(debug);
        break;
    } // END GST_MESSAGE_ERROR
    case GST_MESSAGE_EOS: //  end-of-stream
    {
        g_print("Exit pipeline!\n");


        break;
    } // END GST_MESSAGE_EOS
    default:    //         unhandled message
    {

        break;
    } // END default
    } // END switch(GST_MESSAGE_TYPE(message))
    return true;
} // END my_bus_callback
} // -- END namespace devices

RTSP_H265_device::RTSP_H265_device(SettingsPtr &settings) : settings(settings)
{
#if defined(CCM_8UC3)
    settings->output.format_out = "RGBA";
#elif defined(CCM_8UC1)
    settings->output.format_out = "GRAY8";
#else
    throw std::runtime_error("Not supported color space for output format");
#endif
}

RTSP_H265_device::~RTSP_H265_device()
{
    quit();
}

void RTSP_H265_device::setup()
{

    pipeline_str = "rtspsrc location=rtsp://"
            + settings->src.login + ":" + settings->src.parol
            + "@" + settings->src.ip +  ":" + to_string(settings->src.port)
            + "/Streaming/channels/" + to_string(settings->src.channel) + "/"
            + " latency=" + to_string(settings->src.latency) + " " +
            "! application/x-rtp, payload=96 ! rtp" + settings->src.codec + "depay ! " + settings->src.codec + "parse ! avdec_" + settings->src.codec + " "
            "! videoconvert ! video/x-raw,format=(string)" + settings->output.format_out +
            ",width=" + to_string(settings->video.width) + ",height=" + to_string(settings->video.height) +
            ",framerate=" + to_string(settings->video.fps) + "/1 " +
            "! videoconvert "
            "! appsink name=" + settings->sink.name + " " +
            "emit-signals=" + settings->sink.emit_signals + " " +
            "sync=" + settings->sink.sync + " " +
            "max-buffers=" + to_string(settings->sink.max_buffers) + " " +
            "drop=" + settings->sink.drop;
    cout << "std:: pipeline: \n" << pipeline_str << endl;
    frame_byte_length = settings->video.width * settings->video.height * getColorChannels();


    gst_init(NULL, NULL);

    sync.frameReady.store(false);
    gchar *descr = g_strdup(pipeline_str.c_str());
    // Check pipeline
    error = nullptr;
    pipeline = gst_parse_launch(descr, &error);

    if(error) {
        g_print("could not construct pipeline: %s\n", error->message);
        g_error_free(error);
        exit(-1);
    }

    // Get sink
    sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");

    g_signal_connect(sink, "new-sample", (GCallback)newData, this);

    state.inited = true;
} // END setup()

void RTSP_H265_device::start()
{
    if (!state.inited)
    {
        setup();
        if (!state.inited)
            return;
    }
    sync.handleFrameExecute.store(true, std::memory_order_release);
    std::thread(&RTSP_H265_device::exec, this).detach();
    std::thread(&RTSP_H265_device::runHandleFrame, this).detach();
}

void RTSP_H265_device::quit()
{
    sync.handleFrameExecute.store(false, std::memory_order_acquire);
    sync.frameReadyCv.notify_one();

    if(pipeline)
    {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(GST_OBJECT(pipeline));
        pipeline = nullptr;
    }
}

uint8_t *RTSP_H265_device::receiveFrame(int &w, int &h, int &id, int &num)
{
    if (sync.frameReady.load())
    {
        w = settings->video.width;
        h = settings->video.height;
        id = 0;
        num = frameCnt;
        sync.frameReady.store(false);

        return map.data;
    };
    return nullptr;
}

void RTSP_H265_device::getFormatedImage(uint8_t *f, int w, int h, int id, cv::Mat &image)
{
#if defined(CCM_8UC3)
    static cv::Mat tempImg(settings->video.height, settings->video.width, CV_8UC4);
    memcpy(tempImg.data, map.data, frame_byte_length);
    cv::cvtColor(tempImg, image, cv::COLOR_RGBA2BGR);
#elif defined(CCM_8UC1)
//    cout << "dbg:: w    =  " << w << endl;
//    cout << "dbg:: h    =  " << h << endl;
//    cout << "dbg:: id   =  " << id << endl;
//    cout << "dbg:: image.size =  " << image.size() << "; channels = " << image.channels() << endl;
//    cout << "dbg:: map.size() = " << map.size << endl;
//    cout << "dbg:: frame_byte_length = " << frame_byte_length << endl;
//    cout << "dbg:: map_sz/byte_length= " << map.size / frame_byte_length << endl;
    memcpy(image.data, map.data, frame_byte_length);
#else
    throw std::runtime_error("Not supported color space for output format");
#endif
    sync.frameReady.store(false);
}

int RTSP_H265_device::getColorChannels()
{
#if defined(CCM_8UC3)
    return 4;
#elif defined(CCM_8UC1)
    return 1;
#else
    return 0;
#endif
}

bool RTSP_H265_device::isBayerColorChannel()
{
    return false;
}

void RTSP_H265_device::keyHandler(uchar &key)
{

}

void RTSP_H265_device::workflow()
{

}

void RTSP_H265_device::exec()
{
    GstBus *bus;
    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus, my_bus_callback, nullptr);
    gst_object_unref(bus);

    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
}

void RTSP_H265_device::runHandleFrame()
{
    while(sync.handleFrameExecute.load(std::memory_order_acquire))
    {
        std::unique_lock<std::mutex> lk(sync.frameMtx);
        sync.frameReadyCv.wait(lk);
        if(!sync.handleFrameExecute.load(std::memory_order_acquire))
        {
            break;
        }
        for(auto handler : frame_handlers)
        {
            handler->handle(map.data, settings->video.width,
                            settings->video.height, 0, frameCnt);
        } // -- END for(auto handler : frame_handlers)
        lk.unlock();
    } // -- END while
}


