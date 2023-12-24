#ifndef ILOGGER_HPP
#define ILOGGER_HPP

class ILogger
{
public:
	virtual ~ILogger()														 = default;
	virtual void onWriteToFile(const char* msg)		 = 0;
	virtual void onAppendMsgToLog(const char* msg) = 0;
};

#endif // ILOGGER_HPP