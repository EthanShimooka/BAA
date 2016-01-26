#pragma once
#include "include\LogManager.h"

LogManager LogManager::logManager;

LogManager::LogManager(){
	ID = 1;
}

LogManager* LogManager::GetLogManager() 
{
	return &logManager;
}

//called before any try-catch
void LogManager::create(std::string Filename)
{
	logFile.open(Filename.c_str());
}

//commits text to file and clears text cache
void LogManager::flush()
{
	logFile << logBuffer.str();
	logFile.flush();
	logBuffer.str("");
}

//close log file
void LogManager::close()
{
	logFile.close();
}

//writes exception to log
void LogManager::logException(cException e)
{
	logBuffer << getTimeString() << e.what();
	flush();
}

//gets current time as string in the form: hours:mins:secs
std::string LogManager::getTimeString()
{
	/*stringstream timeStr;

	struct tm *pTime;
	time_t ctTime;
	time(&ctTime);
	pTime = localtime(&ctTime);

	timeStr << setw(2) << setfill('0') << pTime->tm_hour << " : ";
	timeStr << setw(2) << setfill('0') << pTime->tm_min << " : ";
	timeStr << setw(2) << setfill('0') << pTime->tm_sec << " : ";*/

	time_t result = time(NULL);

	char str[26];
	ctime_s(str, sizeof str, &result);

	return str;
	
}