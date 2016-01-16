#pragma once
#ifndef LOGMANAGER_H_INCLUDED
#define LOGMANAGER_H_INCLUDED

#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <vector> //possible include, check later if breaking
#include "EngineObject.h"

//throw macro to throw exceptions
#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(ErrorNum, ErrorDesc) throw cException(errorNum, errorDesc, __FILE__, __LINE__);
#endif

class cException : public std::exception
{
private:
protected:
public:
	int errorNumber;
	std::string errorDesc;
	std::string srcFileName;
	int lineNumber;
	std::string errText;

	//override std::exception::what
	//returns string with ErrorNumber, ErrorDesc, SrcFile, LineNum
	const char* what() const throw();

	cException(int errorNumber, std::string errorDesc, std::string srcFileName, int lineNumber);
	~cException() throw() {}

};


class LogManager : public EngineObject
{
public:
	static LogManager * GetLogManager();
	
	//log buffer
	std::stringstream logBuffer;
	//create log file
	void create(std::string Filename);
	//commits contents to file
	void flush();
	//closes file
	void close();
	//logs exception to the log file
	void logException(cException e);
	//gets time as string to be used in log
	std::string getTimeString();
	//handle to log file
	std::ofstream logFile;

protected:
	LogManager();
	virtual ~LogManager(){}
	static LogManager logManager;

};

#endif //LOGMANAGER_H_INCLUDED