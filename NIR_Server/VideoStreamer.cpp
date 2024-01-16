#include "VideoStreamer.hpp"

VideoStreamer::VideoStreamer(UserInterface* ui)
	: m_ui(ui)
	, m_isStreaming(false)
{
	gst_init(NULL, NULL);
	GError* error = nullptr;
	//m_pipeline = gst_parse_launch("udpsrc port=5000 ! application/x-rtp, payload=96 ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! autovideosink", &error);
	m_pipeline = gst_parse_launch("uridecodebin uri=https://dl6.webmfiles.org/big-buck-bunny_trailer.webm ! videoconvert ! appsink name=sink", &error);
	if (!m_pipeline) {
		std::cerr << "Failed to create pipeline: " << error->message << std::endl;
		g_error_free(error);
		return;
	}

	if (!GST_IS_ELEMENT(m_pipeline)) {
		std::cerr << "Invalid pipeline element" << std::endl;
		m_ui->getLogger()->onAppendMsgToLog("Invalid pipeline element\n");
		m_ui->getLogger()->onWriteToFile("Invalid pipeline element\n");
		return;
	}
	m_ui->getLogger()->onAppendMsgToLog("Pipeline element created\n");
	m_ui->getLogger()->onWriteToFile("Pipeline element created\n");

	m_bus = gst_element_get_bus(m_pipeline);

	//m_sink = gst_bin_get_by_name(GST_BIN(m_pipeline), "sink");

	m_appsink = gst_bin_get_by_name(GST_BIN(m_pipeline), "sink");
	//m_appsink = (GstAppSink*)m_sink;
	if (!m_appsink) {
		std::cerr << "Failed to get AppSink element" << std::endl;
		m_ui->getLogger()->onAppendMsgToLog("Failed to get AppSink element\n");
		m_ui->getLogger()->onWriteToFile("Failed to get AppSink element\n");
		return;
	}
	m_ui->getLogger()->onAppendMsgToLog("The AppSink element was received\n");
	m_ui->getLogger()->onWriteToFile("The AppSink element was received\n");

	//gst_app_sink_set_max_buffers(m_appsink, 2); // limit number of buffers queued
	//gst_app_sink_set_drop(m_appsink, true); // drop old buffers in queue when full
	
	GstAppSinkCallbacks callbacks = { nullptr, nullptr, onNewSample };
	gst_app_sink_set_callbacks(GST_APP_SINK(m_appsink), &callbacks, this, nullptr);

	g_object_set(G_OBJECT(m_appsink), "emit-signals", true, "sync", false, nullptr);
	g_signal_connect(m_appsink, "new-sample", G_CALLBACK(onNewSampleSignal), this);

	gst_element_set_state(m_pipeline, GST_STATE_PLAYING);
}

void VideoStreamer::onInit(){}

void VideoStreamer::onRecieveData()
{
	if(m_isStreaming)
		gst_element_set_state(m_pipeline, GST_STATE_PLAYING);
}

void VideoStreamer::onSendData(){}

GstFlowReturn VideoStreamer::handleNewFrame()
{
	GstSample* sample = gst_app_sink_pull_sample(GST_APP_SINK(m_appsink));
	GstBuffer* buffer = gst_sample_get_buffer(sample);

	GstMapInfo map;
	gst_buffer_map(buffer, &map, GST_MAP_READ);

	m_ui->onFrameReceived(map.data, m_ui->getImageSize().x, m_ui->getImageSize().y);

	gst_buffer_unmap(buffer, &map);
	gst_sample_unref(sample);

	return GST_FLOW_OK;
}

void VideoStreamer::onDestroy()
{
	if(m_isStreaming)
		gst_element_set_state(m_pipeline, GST_STATE_NULL);
}

VideoStreamer::~VideoStreamer()
{
	gst_element_set_state(m_pipeline, GST_STATE_NULL);
	gst_object_unref(m_bus);
	gst_object_unref(GST_OBJECT(m_appsink));
	gst_object_unref(m_pipeline);
}

void VideoStreamer::setStreaming(bool isStreaming)
{
	m_isStreaming = isStreaming;
}