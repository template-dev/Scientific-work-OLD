#ifndef IVIDEOSTREAMER_HPP
#define IVIDEOSTREAMER_HPP

#include "UserInterface.hpp"

class UserInterface;
class IVideoStreamer
{
public:
	virtual ~IVideoStreamer() = default;
	virtual void onInit() = 0;
	virtual void onRecieveData() = 0;
	virtual void onSendData() = 0;
	virtual void onDestroy() = 0;
};

#endif // IVIDEOSTREAMER_HPP