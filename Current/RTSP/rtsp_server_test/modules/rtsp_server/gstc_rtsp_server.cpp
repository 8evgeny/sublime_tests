#include "gstc_rtsp_server.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

namespace rtsp::server
{
std::atomic<bool> RTSPServer::new_frame = {false};


void RTSPServer::newFrame(cv::Mat & frame)
{
    std::cout << "RTSPServer::newFrame CALLED!" << endl;
    static unsigned int cnt = 0;
    cout << "RTSPServer::newFrame cnt = " << cnt << endl;
    cout << "frame size = " << frame.size() << "; channels = " << frame.channels() << endl;
    if(f_first_call)
    {
        f_first_call = false;
        buffer_size = frame.cols * frame.rows * frame.channels();
    }
    std::lock_guard<std::mutex> lock(sync.frameMtx);

    framebuffer = gst_buffer_new_wrapped(frame.data, buffer_size);
    g_print("RTSPServer::newFrame:: buff size = %lu\n", buffer_size);
    cnt++;
    sync.frameReadyCv.notify_all();
    std::cout << "RTSPServer::newFrame notify need_data!" << endl;
} // -- END newFrame

void need_data(GstElement * appsrc, guint unused, RTSPServer * server)
{
//    std::unique_lock<std::mutex> lock(server->sync.frameMtx);
//    server->sync.frameReadyCv.wait(lock);
    cout << "need data CALLED" << endl;
    GstBuffer *buffer;
    GstFlowReturn ret;

    //    if(img_BGR16.data)
    //    {
    buffer = gst_buffer_new_wrapped(server->framebuffer, server->buffer_size);
    cout << "gst_buffer_new_wrapped, buffer_size = " << server->buffer_size << endl;

    /* Увеличиваем timestamp every 1/fps секунды*/
    GST_BUFFER_PTS(buffer) = server->timestamp;
    GST_BUFFER_DURATION(buffer) = gst_util_uint64_scale_int (1, GST_SECOND, server->settings.vid.fps);
    server->timestamp += GST_BUFFER_DURATION(buffer);
    cout << "set timestemp" << endl;

    g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);
    //    } // END if(img_BGR16.data)

}

void media_configure(GstRTSPMediaFactory * factory, GstRTSPMedia * media, RTSPServer * server)
{
    GstElement *element, *appsrc;
    //    MyContext *ctx;

    cout << "\n================\nMEDIA CONFIGURE\n================\n" << endl;

    /* Получаем элемент, используемый для предоставления потоков media */
    element = gst_rtsp_media_get_element(media);

    /* Получаем appsrc */
    appsrc = gst_bin_get_by_name_recurse_up(GST_BIN(element), "mysrc");
    cout << "ok recurse set" << endl;

    /* this instructs appsrc that we will be dealing with timed buffer */
    gst_util_set_object_arg(G_OBJECT(appsrc), "format", "time");
    cout << "ok format set" << endl;
    /* configure the caps of the video */
    cout << "w/h2set=" << server->settings.vid.width << "; " << server->settings.vid.height << endl;
    g_object_set (G_OBJECT(appsrc), "caps",
                  gst_caps_new_simple ("video/x-raw",
                                       "format", G_TYPE_STRING, "RGB16",
                                       "width", G_TYPE_INT, server->settings.vid.width,
                                       "height", G_TYPE_INT, server->settings.vid.height,
                                       "framerate", GST_TYPE_FRACTION, 0, 1, NULL), NULL);

    cout << "ok appser set" << endl;
    server->timestamp = 0;
    /* make sure ther datais freed when the media is gone */
    g_object_set_data_full (G_OBJECT(media), "my-extra-data", server,
                            (GDestroyNotify)g_free);

    /* install the callback that will be called when a buffer is needed */
    g_signal_connect(appsrc, "need-data", (GCallback)need_data, server);
}


RTSPServer::RTSPServer() //
{
    cout << "RTSPServer::constructor DEFAULT!" << endl;
} // -- END RTSPServer

RTSPServer::RTSPServer(SettingsRtspSrv settings_) : settings(settings_) // создание объекта RTSP server, назначение settings извне
{
    cout << "RTSPServer::constructor with settings!" << endl;
} // -- END RTSPServer

RTSPServer::~RTSPServer()
{
    std::cout << "Destructor RTSPServer" << std::endl;
} // -- END ~RTSPServer


bool RTSPServer::setup()
{
    return 1;
} // -- END setup

bool RTSPServer::start()
{
    std::cout << "RTSPServer::start BEGIN!" << endl;
    if (!inited)
    {
        if (!setup())
            return false;
    } // END  if (!inited)
    sync.execute.store(true);
    std::thread streametTh(&RTSPServer::exec, this);
    streametTh.detach();
    std::cout << "RTSPServer::start END!" << endl;
    return true;
} // -- END start

void RTSPServer::play()
{
    std::cout << "RTSPServer::play CALLED!" << endl;
} // -- END play

void RTSPServer::pause()
{
    std::cout << "RTSPServer::pause CALLED!" << endl;
} // -- END pause

void RTSPServer::stop()
{
    std::cout << "RTSPServer::stop CALLED!" << endl;
} // -- END stop


void RTSPServer::exec()
{
    std::cout << "RTSPServer::exec BEGIN!" << endl;
    cout << "start gst_loop" << endl;
    std::cout << "RTSPServer::exec BEGIN!" << endl;
    GMainLoop *loop;
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *factory;
    gst_init(NULL,NULL);
    loop = g_main_loop_new(NULL, FALSE);
    /* create a server instance */
    server = gst_rtsp_server_new();
    /* получить точки монтирования для этого сервера, у каждого сервера есть объект по умолчанию,
     *  который можно использовать для сопоставления точек монтирования URI с медиа-фабриками */
    mounts = gst_rtsp_server_get_mount_points(server);
    /* Создаём фабрику для стрима "/test". По умолчанию используется синтаксис gt-launch для создания пйплайна.
     * Любой пайплайн существет пока содержит элемент pay. Каждый элемент с pay будет стримом. */
    factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory, "( appsrc name=mysrc ! queue max-size-buffers=1 ! videoconvert ! x264enc key-int-max=0.1 bitrate=8196 latency=zerolatency ! rtph264pay name=pay0 pt=96 config-interval=10 )");

    /* уведомить, когда наши медиа готовы. Это вызывается всякий раз, когда кто-то запрашивает медиа,
     *  и создается новый конвейер с нашими приложениями. */
    g_signal_connect(factory, "media-configure", (GCallback)media_configure, this);

    /* прикрепите тестовую фабрику к /test url */
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);

    /* освобождение точек монитрования */
    g_object_unref(mounts);

    /* добавляем server к maincontext*/
    gst_rtsp_server_attach(server, NULL);

    g_print("stream ready at rtsp://127.0.0.1:8554/test\n");

    g_main_loop_run(loop);
    g_object_unref(server);
    g_object_unref(factory);
    cout << "end gst_loop" << endl;
    return;
    std::cout << "RTSPServer::exec END!" << endl;
} // -- END exec

void RTSPServer::setAppSrcSettings(GstRTSPMedia * media)
{
    cout << "RTSPServer::setAppSrcSettings called" << endl;
    GstElement * element = gst_rtsp_media_get_element(media);
    cout << "appsrcc element get from media" << endl;
    appsrc = gst_bin_get_by_name_recurse_up(GST_BIN(element), "mysrc");
    cout << "appsrcc get by name" << endl;
    gst_util_set_object_arg(G_OBJECT (appsrc), "format", "time");
    g_object_set(G_OBJECT(appsrc), "caps",
                 gst_caps_new_simple("video/x-raw",
                                     "format", G_TYPE_STRING, settings.vid.format.c_str(),
                                     "width", G_TYPE_INT, settings.vid.width,
                                     "height", G_TYPE_INT, settings.vid.height,
                                     "framerate", GST_TYPE_FRACTION, settings.vid.fps, 1,
                                     NULL),
                 NULL);
    cout << "appsrc params: " << settings.vid.format << ": " << cv::Point3f(settings.vid.width, settings.vid.height, settings.vid.fps) << endl;
    cout << "appsrcc set properties" << endl;

    g_object_set(appsrc, "emit-signals", TRUE, NULL);
    /* this instructs appsrc that we will be dealing with timed buffer */
    gst_util_set_object_arg(G_OBJECT(appsrc), "format", "time");
    cout << "init framebuffer" << endl;
    g_signal_connect(appsrc, "need-data", GCallback(need_data), this); // назначаем appsrc ждать появления данных в буфере
} // -- END setAppSrcSettings


void RTSPServer::setEncoderSettings(GstRTSPMedia * media)
{
    cout << "RTSPServer::setEncoderSettings called" << endl;
} // -- END setEncoderSettings

void RTSPServer::setPaySettings(GstRTSPMedia * media)
{
    cout << "RTSPServer::setPaySettings called" << endl;
    GstElement * element = gst_rtsp_media_get_element(media);
    pay = gst_bin_get_by_name_recurse_up(GST_BIN(element), "pay0");
} // -- END setPaySettings

void RTSPServer::setSrvSettings(GstRTSPServer * server)
{
    cout << "RTSPServer::setSrvSettings called" << endl;
} // -- END setUDPSettings

}; // END namespace rtsp
