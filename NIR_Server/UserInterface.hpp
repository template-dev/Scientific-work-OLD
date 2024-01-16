#pragma once;

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "VideoStreamer.hpp"
#include "IUserInterface.hpp"
#include "Window.hpp"
#include "Logger.hpp"

#include "Fonts.hpp"

#include <cstring>
#include <memory>

class Window;
class Logger;
class VideoStreamer;
class UserInterface : public IUserInterface
{
public:
	explicit UserInterface(const Window* win);

	void onInit() override;
	void onRender() override;
	void onDestroy() override;
	void onFrameReceived(const void* frameData, int width, int height);
	const std::shared_ptr<Logger>& getLogger() const { return m_logger; }

	const ImVec2& getImageSize() const { return m_imageSize; }

private:
	GLuint onCreateTexture(const void* frameData, int width, int height);
	void onDrawElements();

	ImVec2 m_imageSize;

	const Window* m_window;
	ImGuiWindowFlags m_windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	My_Fonts_ST m_fonts;

	bool m_isServerRunning = false;
	GLuint m_videoTexture = NULL;

	std::shared_ptr<Logger> m_logger = std::make_shared<Logger>();
	std::shared_ptr<VideoStreamer> m_videoStreamer;

	static bool m_optFullScreen;
	static bool m_dockspaceOpen;
	static bool m_optPadding;
};