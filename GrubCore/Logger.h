#ifndef GRUB_LOGGER_H
#define GRUB_LOGGER_H
#include <iostream>
#include <fstream>
#include <string>

//Possible log output types
enum LOGTYPES
{
	NONE = 0x0,
	CONSOLEOUT = 0x1,
	FILEOUT = 0x2,
	ALL = 0xFFFF
};
//Possible message types
enum EMessageType
{
	LOG_UPDATE = 0x1,
	LOG_INFO = 0x2,
	LOG_WARNING = 0x4,
	LOG_ERROR = 0x8,
	LOG_ALL = 0xFFFF
};
//Current log outputs
const int LOGTYPE = LOGTYPES::CONSOLEOUT;
//Current message types that are being filtered.
const int MESSAGETYPES = EMessageType::LOG_INFO | EMessageType::LOG_WARNING | EMessageType::LOG_ERROR;

#include <iostream>

class Logger 
{
public:
	//Logger is a static class, should not be constucted or deleted.
	Logger() = delete;
	~Logger() = delete;
	/**
	Takes a message type as well as a string to be logged.
	*/
	static void Log(const EMessageType MsgType, const std::string& Contents);
};

#endif