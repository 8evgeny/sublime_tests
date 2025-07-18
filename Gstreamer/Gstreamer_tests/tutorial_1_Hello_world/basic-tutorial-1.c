#include <gst/gst.h>
//https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c#
int tutorial_main (int argc, char *argv[])
{
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    /* Initialize GStreamer */
    gst_init (&argc, &argv);
/*
    This must always be your first GStreamer command. Among other things, gst_init():
        Initializes all internal structures
        Checks what plug-ins are available
        Executes any command-line option intended for GStreamer
*/
    /* Build the pipeline */
    pipeline = gst_parse_launch("playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm", NULL);
        //This line is the heart of this tutorial, and exemplifies two key points: gst_parse_launch() and playbin.
        //We are building a pipeline composed of a single element called playbin.

    /* Start playing */
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    /* Wait until error or EOS */
    bus = gst_element_get_bus (pipeline);
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* See next tutorial for proper error message handling/parsing */
    if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR)
    {
        g_printerr ("An error occurred! Re-run with the GST_DEBUG=*:WARN environment variable set for more details.\n");
    }// END if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR)

    /* Free resources */
    gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
    return 0;
}// END int tutorial_main (int argc, char *argv[])

int
main (int argc, char *argv[])
{
  return tutorial_main (argc, argv);
}// END main (int argc, char *argv[])

