#pragma once;

class IWindow
{
public:
	virtual ~IWindow()			 = default;
	virtual void onInit()		 = 0;
	virtual void onRender()	 = 0;
	virtual void onDestroy() = 0;
};