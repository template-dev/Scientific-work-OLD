#pragma once;

#include "IApp.hpp"
#include "Window.hpp"

#include <memory>

class App : public IApp
{
public:
	explicit App(int width, int height, const char* title);
	void onInit()	override;
	void onUpdate() override;
	void onRender() override;

private:
	int m_width;
	int m_height;
	const char* m_title;
	std::unique_ptr<IWindow> m_window;
};