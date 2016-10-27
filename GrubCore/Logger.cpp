#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>


Logger* Logger::theInstance = NULL;

/// TODO: rewrite to write this log file to the hard drive
void Logger::ClearScreen() {
	std::string name = "Debug";
	std::ofstream writeToFile;
	writeToFile.open(name + ".txt");
	writeToFile.open(name + ".txt", std::ios::out);
	writeToFile.close();

}
void Logger::Log(const EMessageType MsgType, const std::string& Contents) {
	int type = (MsgType & MESSAGETYPES);
	if (type == 0)
		return;

	std::string name = "Debug";
	std::ofstream writeToFile;
	writeToFile.open(name + ".txt", std::ios_base::app | std::ios::out);

	//writeToFile << "-------------start of Debug--------------------\n\n";
	switch (MsgType) {
	case EMessageType::LOG_UPDATE:
		if ((LOGTYPE & LOGTYPES::CONSOLEOUT) == LOGTYPES::CONSOLEOUT)
			std::cout << "UPDATE: " << Contents << std::endl;
		if ((LOGTYPE & LOGTYPES::FILEOUT) == LOGTYPES::FILEOUT)
			writeToFile << "UPDATE: " << Contents << std::endl;
		break;
	case EMessageType::LOG_INFO:
		if ((LOGTYPE & LOGTYPES::CONSOLEOUT) == LOGTYPES::CONSOLEOUT)
			std::cout << "INFO: " << Contents << std::endl;
		if ((LOGTYPE & LOGTYPES::FILEOUT) == LOGTYPES::FILEOUT)
			writeToFile << "INFO: " << Contents << std::endl;
		break;
	case EMessageType::LOG_WARNING:
		if ((LOGTYPE & LOGTYPES::CONSOLEOUT) == LOGTYPES::CONSOLEOUT)
			std::cout << "WARNING: " << Contents << std::endl;
		if ((LOGTYPE & LOGTYPES::FILEOUT) == LOGTYPES::FILEOUT)
			writeToFile << "WARNING: " << Contents << std::endl;
		break;
	case EMessageType::LOG_ERROR:
		if ((LOGTYPE & LOGTYPES::CONSOLEOUT) == LOGTYPES::CONSOLEOUT)
			std::cout << "ERROR: " << Contents << std::endl;
		if ((LOGTYPE & LOGTYPES::FILEOUT) == LOGTYPES::FILEOUT)
			writeToFile << "ERROR: " << Contents << std::endl;
		break;
	}
	//writeToFile << "\n--------------End of Debug---------------------\n";
	writeToFile.close();
}

Logger& Logger::getInstance(void) {
	if (getInstance == NULL) {
		theInstance = new Logger();
	}
	return *theInstance;
}