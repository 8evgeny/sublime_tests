#include <gst/gst.h>
#include <glib.h> // For GMainLoop
#include <iostream>
//gst-launch-1.0 -v rtspsrc location=rtsp://user:user@192.168.0.100:554 ! decodebin ! audioconvert ! autoaudiosink
using namespace std;

//static void on_pad_added(GstElement *element, GstPad *pad, gpointer data);

//static GMainLoop *loop;
// Callback function to handle new audio samples
//static GstFlowReturn new_sample(GstElement *sink, gpointer data)
//{
//    GstSample *sample;
//    g_signal_emit_by_name(sink, "pull-sample", &sample);

//    if (sample)
//    {
//        GstBuffer *buffer = gst_sample_get_buffer(sample);
//        GstMapInfo map;
//        if (gst_buffer_map(buffer, &map, GST_MAP_READ))
//        {
//            // Process the audio data in map.data
//            // For example, you can write it to a file, analyze it, etc.
//            std::cout << "Received audio sample with size: " << map.size << std::endl;
//            gst_buffer_unmap(buffer, &map);
//        }
//        gst_sample_unref(sample);
//        return GST_FLOW_OK;
//    }
//    return GST_FLOW_ERROR;
//}

GstElement *pipeline;

static void
cb_rtspsrc_pad_added(GstElement *element, GstPad *pad, gpointer data)
{
        gchar* pad_name = GST_PAD_NAME(pad);
        GstCaps *pad_caps = gst_pad_get_current_caps(pad);
        GstStructure *gstruct;
        GST_DEBUG("A new pad was created (%s) with caps %" GST_PTR_FORMAT "\n", pad_name, pad_caps);
        for (int i = 0; i < gst_caps_get_size(pad_caps); i++)
        {
                gstruct = gst_caps_get_structure(pad_caps, i);
                GST_DEBUG("   Media is: %s\n", gst_structure_get_string(gstruct, "media"));
                if (strcmp("video", gst_structure_get_string(gstruct, "media")) == 0)
                {
                        GstElement *vdepay = gst_bin_get_by_name(GST_BIN(data), "vdepay");
                        if (gst_element_link_pads(element, pad_name, vdepay, "sink") != TRUE) {
                                GST_ERROR("RTSPSrc/Depay video elements could not be linked.\n");
                        }
                        break;
                }
                if (strcmp("audio", gst_structure_get_string(gstruct, "media")) == 0)
                {
                        GstElement *adepay = gst_bin_get_by_name(GST_BIN(data), "adepay");
                        if (gst_element_link_pads(element, pad_name, adepay, "sink") != TRUE)
                        {
                                GST_ERROR("RTSPSrc/Depay audio elements could not be linked.\n");
                                exit(-1);
                        }
                        break;
                }
        }
        gst_caps_unref(pad_caps);
}

void
sigintHandler(int unused)
{
    g_print("Sending EoS");
    gst_element_send_event(pipeline, gst_event_new_eos());
}

int main(int argc, char *argv[])
{
     GstElement *rtspsource, *rtpvdepay, *rtpadepay, *vparse, *aparse, *mux, *file;
     GstBus *bus;
     GstMessage *msg;
     GstStateChangeReturn ret;

     signal(SIGINT, sigintHandler);

     /* Initialize GStreamer */
     gst_init(&argc, &argv);

     /* connects to RTSP server, creates pads for each stream
      * (e.g. video/audio) in RTP source, sends those packets to
      * rest of pipeline */
     rtspsource = gst_element_factory_make("rtspsrc", "src");

     /* depayloads video from RTP packet source */
     rtpvdepay = gst_element_factory_make("rtph264depay", "vdepay");

     /* parses video info for storage elements */
     vparse = gst_element_factory_make("h264parse", "vparse");

     /* depayloads audio from RTP packet source */
     rtpadepay = gst_element_factory_make("rtpmp4gdepay", "adepay");

     /* parses audio info for storage elements */
     aparse = gst_element_factory_make("aacparse", "aparse");

     /* packages streams in mp4 file */
     mux = gst_element_factory_make("mp4mux", "mux");

     /* writes to file */
     file = gst_element_factory_make("filesink", "file");

     /* creates the empty pipeline */
     pipeline = gst_pipeline_new("test-pipeline");

     /* stop if anything failed to create */
     if (!pipeline || !rtspsource || !rtpvdepay || !rtpadepay || !vparse || !aparse || !mux || !file) {
             GST_ERROR("Not all elements could be created.\n");
             return -1;
     }

     /* builds pipeline and links things that are static */
     gst_bin_add_many(GST_BIN(pipeline), rtspsource, rtpvdepay, rtpadepay, vparse, aparse, mux, file, NULL);
     if (gst_element_link_many(rtpvdepay, vparse, mux, file, NULL) != TRUE) {
             g_printerr("Static video elements could not be linked.\n");
             gst_object_unref(pipeline);
             return -1;
     }
     if (gst_element_link_many(rtpadepay, aparse, mux, NULL) != TRUE) {
             g_printerr("Static audio elements could not be linked.\n");
             gst_object_unref(pipeline);
             return -1;
     }

     /* specify RTSP souce properties */
     g_object_set(G_OBJECT(rtspsource), "location", "rtsp://192.168.0.100:554", NULL);
     g_object_set(G_OBJECT(rtspsource), "latency", 0, NULL);
     g_object_set(G_OBJECT(rtspsource), "user-id", "user", NULL);
     g_object_set(G_OBJECT(rtspsource), "user-pw", "user", NULL);

     /* specifcy file properties */
     g_object_set(G_OBJECT(file), "location", "/tmp/capture.mp4", NULL);

     /* connect callback for pads on RTSP source when it discovers them */
     g_signal_connect(rtspsource, "pad-added", G_CALLBACK(cb_rtspsrc_pad_added), pipeline);

     /* start playing (connects to RTSP source) */
     ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
     if (ret == GST_STATE_CHANGE_FAILURE)
     {
             g_printerr("Unable to set the pipeline to the playing state.\n");
             gst_object_unref(pipeline);
             return -1;
     }

     /* wait until error or EOS */
     bus = gst_element_get_bus(pipeline);
     msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType) (GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

     /* parse messages from bus */
     if (msg != NULL)
     {
             GError *err;
             gchar *debug_info;

             switch (GST_MESSAGE_TYPE (msg)) {
             case GST_MESSAGE_ERROR:
                     gst_message_parse_error(msg, &err, &debug_info);
                     GST_ERROR("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                     GST_DEBUG("  Debugging information: %s\n", debug_info ? debug_info : "none");
                     g_clear_error(&err);
                     g_free(debug_info);
                     break;
             case GST_MESSAGE_EOS:
                     GST_INFO("End-Of-Stream reached.\n");
                     break;
             default:
                     /* We should not reach here because we only asked for ERRORs and EOS */
                     GST_ERROR("Unexpected message received.\n");
                     break;
             }
             gst_message_unref(msg);
     }

     /* Free resources */
     gst_object_unref (bus);
     gst_element_set_state (pipeline, GST_STATE_NULL);
     gst_object_unref (pipeline);

//    GstElement *pipeline, *rtspsrc, *rtpdepay, *decoder, *audioconvert, *audiosink, *appsink;
//    GstBus *bus;
//    GstMessage *msg;
//    GError *error = NULL;
//    // Initialize GStreamer
//    gst_init(&argc, &argv);
//    // Create the elements
//    rtspsrc = gst_element_factory_make("rtspsrc", "rtsp-source");
//    rtpdepay = gst_element_factory_make("rtpmp4gdepay", "rtp-depayloader"); // Adjust depayloader based on your audio codec (e.g., rtpmp4gdepay for AAC)
//    decoder = gst_element_factory_make("decodebin", "decoder");
//    audioconvert = gst_element_factory_make("audioconvert", "audio-converter");
//    audiosink = gst_element_factory_make("autoaudiosink", "audio-sink");    // For direct playback
//    appsink = gst_element_factory_make("appsink", "audio-appsink");         // To capture samples in C++
//    // Create the empty pipeline
//    pipeline = gst_pipeline_new("rtsp-audio-pipeline");

//    if (!pipeline || !rtspsrc /*|| !rtpdepay*/ || !decoder || !audioconvert || !audiosink || !appsink )
//    {
//        g_printerr("Not all elements could be created.\n");
//        return -1;
//    }
//    // Set the RTSP source URI
//    g_object_set(G_OBJECT(rtspsrc), "location", "rtsp://user:user@192.168.0.100:554", NULL);
//    // Configure appsink to emit "new-sample" signal
//    g_object_set(G_OBJECT(appsink), "emit-signals", TRUE, "sync", FALSE, NULL);
//    g_signal_connect(appsink, "new-sample", G_CALLBACK(new_sample), NULL);
//    // Add elements to the pipeline
//    gst_bin_add_many(GST_BIN(pipeline), rtspsrc, /*rtpdepay,*/ decoder, audioconvert, audiosink, appsink, NULL);
//    // Link the elements
//    // RTSP source to depayloader (dynamic linking for rtspsrc)
//    if (!gst_element_link(rtspsrc,  decoder))
//    {
//        g_printerr("Could not link rtspsrc to decoder.\n");
//        gst_object_unref(pipeline);
//        return -1;
//    }
//    if (!gst_element_link_many(rtpdepay, decoder, audioconvert, audiosink, NULL) || !gst_element_link(audioconvert, appsink))
//    {
//        g_printerr("Elements could not be linked.\n");
//        gst_object_unref(pipeline);
//        return -1;
//    }
//    // Start playing the pipeline
//    gst_element_set_state(pipeline, GST_STATE_PLAYING);
//    // Create a GMainLoop to handle events
//    loop = g_main_loop_new(NULL, FALSE);
//    // Listen for messages on the bus
//    bus = gst_element_get_bus(pipeline);
//    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
//    // Parse message
//    if (msg != NULL)
//    {
//        GstMessageType type = GST_MESSAGE_TYPE(msg);
//        if (type == GST_MESSAGE_ERROR)
//        {
//            gst_message_parse_error(msg, &error, NULL);
//            g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), error->message);
//            g_clear_error(&error);
//        }
//        else if (type == GST_MESSAGE_EOS)
//        {
//            g_print("End-Of-Stream reached.\n");
//        }
//        gst_message_unref(msg);
//    }
//    // Clean up
//    g_main_loop_unref(loop);
//    gst_object_unref(bus);
//    gst_element_set_state(pipeline, GST_STATE_NULL);
//    gst_object_unref(pipeline);

//    GstElement *pipeline, *rtspsrc, *decodebin, *audioconvert, *audiosink;
//    GstBus *bus;
//    GstMessage *msg;
//    GstStateChangeReturn ret;
//    // Initialize GStreamer
//    gst_init(&argc, &argv);
//    if (!gst_is_initialized()) { g_printerr("Error init GST.\n"); return -1; }
//    // Create elements
//    rtspsrc = gst_element_factory_make("rtspsrc", "source");
//    decodebin = gst_element_factory_make("decodebin", "decoder");
//    audioconvert = gst_element_factory_make("audioconvert", "convert");
//    audiosink = gst_element_factory_make("autoaudiosink", "sink");
//    // Create the empty pipeline
//    pipeline = gst_pipeline_new("rtsp-client-pipeline");
//    if (!pipeline || !rtspsrc || !decodebin || !audioconvert || !audiosink)
//    {
//        g_printerr("Not all elements could be created.\n");
//        return -1;
//    }
//    // Set the RTSP URL
//    g_object_set(G_OBJECT(rtspsrc), "location", "rtsp://user:user@192.168.0.100:554", NULL);
//    // Build the pipeline: rtspsrc -> decodebin -> audioconvert -> audiosink
//    gst_bin_add_many(GST_BIN(pipeline), rtspsrc, decodebin, audioconvert, audiosink, NULL);
//    // Link rtspsrc to decodebin. Decodebin handles dynamic linking.
//    // The "pad-added" signal on decodebin is crucial for dynamic linking.
//    if (!gst_element_link(rtspsrc, decodebin))
//    {
//        g_printerr("Elements could not be linked (rtspsrc -> decodebin).\n");
//        gst_object_unref(pipeline);
//        return -1;
//    }
//    // Connect the "pad-added" signal of decodebin to a handler function
//    // This handler will link the decoded streams to the appropriate sinks (e.g., videosink)
//    g_signal_connect(decodebin, "pad-added", G_CALLBACK(on_pad_added), audiosink);
//    // Set the pipeline to the PLAYING state
//    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
//    if (ret == GST_STATE_CHANGE_FAILURE) {
//        g_printerr("Unable to set the pipeline to the playing state.\n");
//        gst_object_unref(pipeline);
//        return -1;
//    }
//    // Listen to the bus for messages (errors, EOS, etc.)
//    bus = gst_element_get_bus(pipeline);
//    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
//    // Parse message
//    if (msg != NULL) {
//        GError *err;
//        gchar *debug_info;

//        switch (GST_MESSAGE_TYPE(msg)) {
//            case GST_MESSAGE_ERROR:
//                gst_message_parse_error(msg, &err, &debug_info);
//                g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
//                g_printerr("Debugging info: %s\n", debug_info ? debug_info : "none");
//                g_clear_error(&err);
//                g_free(debug_info);
//                break;
//            case GST_MESSAGE_EOS:
//                g_print("End-Of-Stream reached.\n");
//                break;
//            default:
//                // We should not reach here because we only asked for ERRORs and EOS
//                g_printerr("Unexpected message received.\n");
//                break;
//        }
//        gst_message_unref(msg);
//    }
//    // Free resources
//    gst_object_unref(bus);
//    gst_element_set_state(pipeline, GST_STATE_NULL);
//    gst_object_unref(pipeline);

    return 0;
}

// Handler for the "pad-added" signal of decodebin
//static void on_pad_added(GstElement *element, GstPad *pad, gpointer data)
//{
//    GstPad *sinkpad;
//    GstElement *videosink = (GstElement *)data;

//    g_print("Dynamic pad created on %s: %s\n", GST_ELEMENT_NAME(element), GST_PAD_NAME(pad));

//    // Check if the new pad is a video pad
//    GstCaps *new_pad_caps = gst_pad_get_current_caps(pad);
//    GstStructure *new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
//    const gchar *new_pad_type = gst_structure_get_name(new_pad_struct);

//    if (g_str_has_prefix(new_pad_type, "video/x-raw") || g_str_has_prefix(new_pad_type, "video/x-h264"))
//    {
//        sinkpad = gst_element_get_static_pad(videosink, "sink");
//        if (gst_pad_is_linked(sinkpad))
//        {
//            g_print("We are already linked. Ignoring.\n");
//            goto exit;
//        }
//        if (gst_pad_link(pad, sinkpad) != GST_PAD_LINK_OK)
//        {
//            g_printerr("Type is '%s' but link failed.\n", new_pad_type);
//        }
//        else
//        {
//            g_print("Link succeeded (type '%s').\n", new_pad_type);
//        }
//        gst_object_unref(sinkpad);
//    }

//exit:
//    if (new_pad_caps != NULL)
//        gst_caps_unref(new_pad_caps);
//}
