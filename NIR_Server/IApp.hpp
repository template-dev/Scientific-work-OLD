#pragma once;

class IApp
{
public:
	virtual ~IApp()			= default;
	virtual void onInit()	= 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
};