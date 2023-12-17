#pragma once;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "IUserInterface.hpp"
#include "Window.hpp"

#include "Fonts.hpp"

class Window;
class UserInterface : public IUserInterface
{
public:
	UserInterface(const Window* win);

	void onInit()	 override;
	void onRender()  override;
	void onDestroy() override;

private:
	void onDrawElements();

private:
	const Window* m_window;
	ImGuiWindowFlags m_windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	My_Fonts_ST m_fonts;

	static bool m_optFullScreen;
	static bool m_dockspaceOpen;
	static bool m_optPadding;
};