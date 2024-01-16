#ifndef VIDEOSTREAMER_HPP
#define VIDEOSTREAMER_HPP

#include "IVideoStreamer.hpp"
#include "UserInterface.hpp"

#include <iostream>
#include <mutex>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>

class UserInterface;
class VideoStreamer : public IVideoStreamer
{
public:
	explicit VideoStreamer(UserInterface* ui);
	~VideoStreamer();

	void onInit() override;
	void onRecieveData() override;
	void onSendData() override;
	void onDestroy() override;
	void setStreaming(bool isStreaming);

private:
	GstElement* m_pipeline = nullptr;
	GstElement* m_sink = nullptr;
	GstElement* m_appsink = nullptr;
	//GstAppSink* m_appsink = nullptr;
	GstBus* m_bus = nullptr;
	std::mutex m_mutex;
	UserInterface* m_ui;
	bool m_isStreaming;

	static GstFlowReturn onNewSample(GstAppSink* sink, gpointer user_data) {
		return ((VideoStreamer*)user_data)->handleNewFrame();
	}

	static void onNewSampleSignal(GstAppSink* sink, gpointer user_data) {
		g_signal_emit_by_name(sink, "pull-sample", nullptr);
	}

	GstFlowReturn handleNewFrame();
};

#endif // VIDEOSTREAMER_HPP