#include <gst/rtp/rtp.h>
#include <gst/app/gstappsrc.h>

#include "pipeline.h"

static GstPadProbeReturn
cb_probe_data (GstPad          *pad,
               GstPadProbeInfo *info,
               gpointer         user_data)
{
    gint x, y;
    GstMapInfo map;
    guint16 *ptr, t;
    GstBuffer *buffer;

    //g_print("cb_probe_data\n");

    buffer = GST_PAD_PROBE_INFO_BUFFER (info);

    /* Making a buffer writable can fail (for example if it
   * cannot be copied and is used more than once)
   */
    if (buffer == NULL)
        return GST_PAD_PROBE_OK;

    /* Mapping a buffer can fail (non-writable) */
    if (gst_buffer_map (buffer, &map, GST_MAP_READ)) {
        //g_print("size: %d\n", map.size);
        for (int i=0; i < map.size; ++i) {
            g_print("%x ", map.data[i]);
        }
        g_print("\n");
        gst_buffer_unmap (buffer, &map);
    }

    GST_PAD_PROBE_INFO_DATA (info) = buffer;

    return GST_PAD_PROBE_OK;
}


static void cb_need_data (GstElement* appsrc, guint arg0, gpointer user_data) {
    static GstClockTime timestamp = 0;

    GstBuffer *buffer = gst_buffer_new_allocate (NULL, 18, NULL);

    // sample of KLV data compliant with SMPTE336M standard (the only one serviced by rtpklvpay element)
    gchar klv_data[] = {// key
                        0x06, 0x0e, 0x2b, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        // length
                        0x01,
                        // value
                        0xaa};

    gst_buffer_fill(buffer, 0, klv_data, 18);

    GST_BUFFER_PTS (buffer) = timestamp;
    GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale_int (1, GST_SECOND, 15);
    //std::cout << "Pushing KLV buffer with timestamp " << timestamp << std::endl;
    timestamp += GST_BUFFER_DURATION (buffer);

    GstFlowReturn ret = gst_app_src_push_buffer ((GstAppSrc*)appsrc, buffer);
    if (ret != GST_FLOW_OK) {
        GST_ERROR("%s\n", gst_flow_get_name(ret));
    }
}

typedef struct _SessionData
{
    int ref;
    guint sessionNum;
    GstElement *input;
} SessionData;

static SessionData *
session_ref (SessionData * data)
{
    g_atomic_int_inc (&data->ref);
    return data;
}

static void
session_unref (gpointer data)
{
    SessionData *session = (SessionData *) data;
    if (g_atomic_int_dec_and_test (&session->ref)) {
        g_free (session);
    }
}

static SessionData *
session_new (guint sessionNum)
{
    SessionData *ret = g_new0 (SessionData, 1);
    ret->sessionNum = sessionNum;
    return session_ref (ret);
}

/*
 * Used to generate informative messages during pipeline startup
 */
static void
cb_state (GstBus * bus, GstMessage * message, gpointer data)
{
    GstObject *pipe = GST_OBJECT (data);
    GstState old, newone, pending;
    gst_message_parse_state_changed (message, &old, &newone, &pending);
    if (message->src == pipe) {
        g_print ("Pipeline %s changed state from %s to %s\n",
                 GST_OBJECT_NAME (message->src),
                 gst_element_state_get_name (old), gst_element_state_get_name (newone));
    }
}

/*
 * Creates a GstGhostPad named "src" on the given bin, pointed at the "src" pad
 * of the given element
 */
static void
setup_ghost (GstElement * src, GstBin * bin)
{
    GstPad *srcPad = gst_element_get_static_pad (src, "src");
    GstPad *binPad = gst_ghost_pad_new ("src", srcPad);
    gst_element_add_pad (GST_ELEMENT (bin), binPad);
}

static SessionData *make_klv_session (guint sessionNum)
{
    GstBin *klvBin = GST_BIN (gst_bin_new (NULL));
    GstElement *klvSrc = gst_element_factory_make ("appsrc", NULL);
    //GstElement *klvSrc = gst_element_factory_make ("multifilesrc", NULL);
    GstElement *payloader = gst_element_factory_make ("rtpklvpay", NULL);

    gst_bin_add_many (klvBin, klvSrc, payloader, NULL);

    auto srcPayloaderCaps = gst_caps_new_simple("meta/x-klv", NULL);
    gst_element_link_filtered(klvSrc, payloader, srcPayloaderCaps);

    //g_object_set (klvSrc, "loop", TRUE, "location", "/home/pi/data.klv", NULL);
    g_object_set (G_OBJECT (klvSrc),
                  "stream-type", GST_APP_STREAM_TYPE_STREAM,
                  "format", GST_FORMAT_TIME,
                  NULL);
    g_signal_connect (klvSrc, "need-data", G_CALLBACK (cb_need_data), NULL);

    /*auto pad = gst_element_get_static_pad (payloader, "sink");
  gst_pad_add_probe (pad, GST_PAD_PROBE_TYPE_BUFFER,
      (GstPadProbeCallback) cb_probe_data, NULL, NULL);
  gst_object_unref (pad);*/

    setup_ghost (payloader, klvBin);

    auto session = session_new (sessionNum);
    session->input = GST_ELEMENT (klvBin);

    return session;
}

static SessionData *make_video_session (guint sessionNum) {
    GstBin *videoBin = GST_BIN (gst_bin_new (NULL));
    GstElement *videoSrc = gst_element_factory_make ("v4l2src", NULL);
    GstElement *encoder = gst_element_factory_make ("omxh264enc", NULL);
    GstElement *payloader = gst_element_factory_make ("rtph264pay", NULL);

    g_object_set (videoSrc, "device", "/dev/video0", NULL);

    gst_bin_add_many (videoBin, videoSrc, encoder, payloader, NULL);

    auto srcEncoderCaps = gst_caps_new_simple ("video/x-raw",
                                               "width", G_TYPE_INT, 1280,
                                               "height", G_TYPE_INT, 720,
                                               NULL);
    gst_element_link_filtered (videoSrc, encoder, srcEncoderCaps);

    auto encoderPayloaderCaps = gst_caps_new_simple("video/x-h264", "profile", G_TYPE_STRING, "high", NULL);
    gst_element_link_filtered (encoder, payloader, encoderPayloaderCaps);

    setup_ghost (payloader, videoBin);

    auto session = session_new (sessionNum);
    session->input = GST_ELEMENT (videoBin);

    return session;
}

/*
 * This function sets up the UDP sinks and sources for RTP/RTCP, adds the
 * given session's bin into the pipeline, and links it to the properly numbered
 * pads on the rtpbin
 */
static void
add_stream (GstPipeline * pipe, GstElement * rtpBin, SessionData * session)
{
    GstElement *rtpSink = gst_element_factory_make ("udpsink", NULL);
    GstElement *rtcpSink = gst_element_factory_make ("udpsink", NULL);
    GstElement *rtcpSrc = gst_element_factory_make ("udpsrc", NULL);
    int basePort;
    gchar *padName;

    basePort = 5000 + (session->sessionNum * 6);

    gst_bin_add_many (GST_BIN (pipe), rtpSink, rtcpSink, rtcpSrc,
                      session->input, NULL);

    g_object_set (rtpSink, "port", basePort,
                  "host", "192.168.0.158",
                  "sync",TRUE,
                  "async", TRUE,
                  NULL);

    g_object_set (rtcpSink,
                  "port", basePort + 1,
                  "host", "192.168.0.158",
                  "sync",FALSE,
                  "async", FALSE,
                  NULL);

    g_object_set (rtcpSrc, "port", basePort + 2, NULL);

    padName = g_strdup_printf ("send_rtp_sink_%u", session->sessionNum);
    gst_element_link_pads (session->input, "src", rtpBin, padName);
    g_free (padName);

    padName = g_strdup_printf ("send_rtp_src_%u", session->sessionNum);
    gst_element_link_pads (rtpBin, padName, rtpSink, "sink");
    g_free (padName);

    padName = g_strdup_printf ("send_rtcp_src_%u", session->sessionNum);
    gst_element_link_pads (rtpBin, padName, rtcpSink, "sink");
    g_free (padName);

    padName = g_strdup_printf ("recv_rtcp_sink_%u", session->sessionNum);
    gst_element_link_pads (rtcpSrc, "src", rtpBin, padName);
    g_free (padName);

    g_print ("New RTP stream on %i/%i/%1\n", basePort, basePort + 1, basePort + 2);

    session_unref (session);
}

Pipeline::Pipeline() {
    pipe = GST_PIPELINE (gst_pipeline_new (NULL));
    auto bus = gst_element_get_bus (GST_ELEMENT (pipe));
    g_signal_connect (bus, "message::state-changed", G_CALLBACK (cb_state), pipe);
    gst_bus_add_signal_watch (bus);
    gst_object_unref (bus);

    auto rtpBin = gst_element_factory_make ("rtpbin", NULL);
    g_object_set (rtpBin, "rtp-profile", GST_RTP_PROFILE_AVPF, NULL);

    gst_bin_add (GST_BIN (pipe), rtpBin);

    auto videoSession = make_video_session (0);
    auto audioSession = make_klv_session (1);
    add_stream (pipe, rtpBin, videoSession);
    add_stream (pipe, rtpBin, audioSession);

    gst_element_set_state (GST_ELEMENT (pipe), GST_STATE_NULL);
}

Pipeline::~Pipeline() {
    g_print ("Stopping server pipeline\n");
    gst_element_set_state (GST_ELEMENT (pipe), GST_STATE_NULL);
    gst_object_unref (pipe);
}

void Pipeline::play() {
    g_print ("Starting server pipeline\n");
    gst_element_set_state (GST_ELEMENT (pipe), GST_STATE_PLAYING);
}
