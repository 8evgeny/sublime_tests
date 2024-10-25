#include "myserver.hpp"

namespace rtspsrv
{

cv::Mat img_BGR16;
RTSPSettings settings;

void need_data(GstElement *appsrc, guint unused, MyContext *ctx)
{
    GstBuffer *buffer;
    GstFlowReturn ret;

    if(img_BGR16.data)
    {
//        std::cout << "FILL img_BGR16" << std::endl;
        uint8_t * buff_img_BGR16 = img_BGR16.data;
        buffer = gst_buffer_new_wrapped(img_BGR16.data, img_BGR16.cols * img_BGR16.rows * img_BGR16.channels());
        /* Увеличиваем timestamp every 1/fps секунды*/
        GST_BUFFER_PTS (buffer) = ctx->timestamp;
        GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale_int (1, GST_SECOND, 30);
        ctx->timestamp += GST_BUFFER_DURATION (buffer);
        g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);
    } // END if(img_BGR16.data)
}

void media_configure(GstRTSPMediaFactory *factory, GstRTSPMedia *media, gpointer user_data)
{
    GstElement *element, *appsrc;
    MyContext *ctx;

    std::cout << "\n================\nMEDIA CONFIGURE\n================\n" << std::endl;

    /* Получаем элемент, используемый для предоставления потоков media */
    element = gst_rtsp_media_get_element (media);

    /* Получаем appsrc */
    appsrc = gst_bin_get_by_name_recurse_up(GST_BIN (element), "mysrc");

    /* this instructs appsrc that we will be dealing with timed buffer */
    gst_util_set_object_arg(G_OBJECT (appsrc), "format", "time");
    /* configure the caps of the video */
    g_object_set (G_OBJECT (appsrc), "caps",
                  gst_caps_new_simple ("video/x-raw",
                                       "format", G_TYPE_STRING, "RGB16",
                                       "width", G_TYPE_INT, 1920,
                                       "height", G_TYPE_INT, 1080,
                                       "framerate", GST_TYPE_FRACTION, 0, 1, NULL), NULL);

    ctx = g_new0 (MyContext, 1);
    ctx->white = FALSE;
    ctx->timestamp = 0;
    /* make sure ther datais freed when the media is gone */
    g_object_set_data_full (G_OBJECT (media), "my-extra-data", ctx,
                            (GDestroyNotify) g_free);

    /* install the callback that will be called when a buffer is needed */
    g_signal_connect(appsrc, "need-data", (GCallback) need_data, ctx);
}

void set_image(cv::Mat img_)
{
    img_BGR16 = img_.clone();
    //    need_fill_buffer = true;
}

int gst_loop()
{
    std::cout << "start gst_loop" << std::endl;
    std::cout << "RTSPServer::exec BEGIN!" << std::endl;
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
    gst_rtsp_media_factory_set_launch(factory, "( appsrc name=mysrc ! videoconvert ! video/x-raw, format=I420 ! x264enc key-int-max=0.3 bitrate=8192 ! rtph264pay name=pay0 pt=96 config-interval-1 )");

    /* уведомить, когда наши медиа готовы. Это вызывается всякий раз, когда кто-то запрашивает медиа,
     *  и создается новый конвейер с нашими приложениями. */
    g_signal_connect(factory, "media-configure", (GCallback)media_configure, NULL);

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
    std::cout << "end gst_loop" << std::endl;
    return 1;
}

};
