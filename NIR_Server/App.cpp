#include "App.hpp"

#include <gst/gst.h>

App::App(int width, int height, const char* title)
	: m_width(width)
	, m_height(height)
	, m_title(title)
{
	m_window = std::make_unique<Window>(width, height, title);
}

void App::onInit()
{
	m_window->onInit();
}

void App::onUpdate()
{}

void App::onRender()
{
	m_window->onRender();
}