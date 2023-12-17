#pragma once;

class IUserInterface
{
public:
	virtual ~IUserInterface() = default;
	virtual void onInit()	  = 0;
	virtual void onRender()   = 0;
	virtual void onDestroy()  = 0;
};