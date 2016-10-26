#ifndef GRUB_LOGGER_H
#define GRUB_LOGGER_H
enum LOGTYPES
{
	NONE = 0x0,
	CONSOLEOUT = 0x1,
	FILEOUT = 0x2,
	ALL = 0xFFFF
};
const int LOGTYPE = LOGTYPES::NONE;

#include <iostream>

class Logger {

private:
	Logger(void) {}
	static Logger *theInstance;
public:
	enum EMessageType 
	{
		INFO,
		WARNING,
		FATAL_ERROR
	};

	static Logger& getInstance();
	static void Logger::ClearScreen();
	static void Log(const EMessageType MsgType, const std::string& Contents);
};

#endif