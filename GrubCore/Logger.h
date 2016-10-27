#ifndef GRUB_LOGGER_H
#define GRUB_LOGGER_H
enum LOGTYPES
{
	NONE = 0x0,
	CONSOLEOUT = 0x1,
	FILEOUT = 0x2,
	ALL = 0xFFFF
};
enum EMessageType
{
	LOG_UPDATE = 0x1,
	LOG_INFO = 0x2,
	LOG_WARNING = 0x4,
	LOG_ERROR = 0x8
};
const int LOGTYPE = LOGTYPES::CONSOLEOUT;
const int MESSAGETYPES = EMessageType::LOG_INFO | EMessageType::LOG_WARNING | EMessageType::LOG_ERROR;

#include <iostream>

class Logger {

private:
	Logger(void) {}
	static Logger *theInstance;
public:
	static Logger& getInstance();
	static void Logger::ClearScreen();
	static void Log(const EMessageType MsgType, const std::string& Contents);
};

#endif