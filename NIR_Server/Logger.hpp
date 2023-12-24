#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "ILogger.hpp"
#include <cstring>
#include <fstream>
#include <memory>

class Logger : public ILogger
{
public:
	explicit Logger() = default;

	void onAppendMsgToLog(const char* msg) override;
	void onWriteToFile(const char* msg)		 override;
	char* getBuffer() const { return m_logBuffer; }

private:
	constexpr static int m_nBuffer = 1024;
	static char m_logBuffer[m_nBuffer];
	std::ofstream m_output;
};

#endif // LOGGER_HPP