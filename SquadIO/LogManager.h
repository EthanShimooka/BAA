#pragma once
#include "EngineObject.h"
class LogManager : public EngineObject
{
public:
	static LogManager * GetErrorManager();

protected:
	LogManager();
	~LogManager();

	static LogManager errorManager;
};

