#pragma once;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "IUserInterface.hpp"
#include "Window.hpp"
#include "Logger.hpp"

#include "Fonts.hpp"

#include <cstring>
#include <memory>

class Window;
class Logger;
class UserInterface : public IUserInterface
{
public:
	explicit UserInterface(const Window* win);

	void onInit()		 override;
	void onRender()  override;
	void onDestroy() override;

private:
	void onDrawElements();

	const Window* m_window;
	ImGuiWindowFlags m_windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	std::unique_ptr<Logger> m_logger = std::make_unique<Logger>();

	My_Fonts_ST m_fonts;

	bool isServerStart = false;

	static bool m_optFullScreen;
	static bool m_dockspaceOpen;
	static bool m_optPadding;
};