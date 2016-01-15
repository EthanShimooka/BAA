#include "LogManager.h"

LogManager::LogManager()
{
}


LogManager::~LogManager()
{
}

LogManager* LogManager::GetErrorManager() {
	return &errorManager;
}