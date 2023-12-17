#pragma once;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UserInterface.hpp"
#include "IWindow.hpp"

#include <GLFW/glfw3.h>
#include <memory>
#include <chrono>

class Window : public  IWindow
{
public:
	Window() = default;
	explicit Window(int weight, int height, const char* title);

	void onInit()		 override;
	void onRender()  override;
	void onDestroy() override;

	GLFWwindow* getWindowPtr()   const { return m_window; }
	const char* getGLSLVersion() const { return m_glsl_version;	}

	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	}

	~Window() = default;

private:
	GLFWwindow* m_window;
	double m_fps = 0.0;
	const char* m_title;
	const char* m_glsl_version;
	int m_width;
	int m_height;
	bool m_show_demo;
	std::unique_ptr<IUserInterface> m_userInterface;
	std::chrono::high_resolution_clock::time_point m_frameStart;
	std::chrono::high_resolution_clock::time_point m_frameEnd;
};