#pragma once
#ifndef LOGMANAGER_H_INCLUDED
#define LOGMANAGER_H_INCLUDED

//------------------------------------------------------------------------------------------------------------------

#include "EngineObject.h"
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <exception>
#include <vector> //possible include, check later if breaking

//throw macro to throw exceptions
#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(errorNum, errorDesc) throw cException(errorNum, errorDesc, __FILE__, __LINE__);
#endif

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif



//EXCEPTION CLASS---------------------------------------------------------------------------------------------------

/**
* cException is a custom error class that wraps Exception()
*
* Parameters include error number, description, source file name,
* line number.
*
*/
class cException : public std::exception
{
private:
protected:
public:
	/// Error Number
	int errorNumber;
	/// Error Description
	std::string errorDesc;
	/// Source Filename
	std::string srcFileName;
	/// Line Number
	int lineNumber;
	/// Error Text
	std::string errText;

	/// override std::exception::what
	/// returns string with ErrorNumber, ErrorDesc, SrcFile, LineNum
	SQUADIO_API const char* what();
	
	/// 
	SQUADIO_API cException(int errorNumber, std::string errorDesc, std::string srcFileName, int lineNumber);
	~cException() throw() {}

};

//LOGMANAGER SINGLETON----------------------------------------------------------------------------------------------------

/**
* LogManager is a singleton that is instantiated at runtime, and is accessed by GetLogManager()+
*
*/
class LogManager : public EngineObject
{
public:
	/// Singleton Accessor method
	SQUADIO_API static LogManager * GetLogManager();

protected:
	/// Constructor
	LogManager();
	/// Deconstructor
   ~LogManager(){}
   /// Static instance
	static LogManager logManager;

public:
	/// log buffer
	std::stringstream logBuffer;
	/// create log file
	SQUADIO_API void create(std::string Filename);
	/// commits contents to file
	SQUADIO_API void flush();
	/// closes file
	SQUADIO_API void close();
	/// logs exception to the log file
	SQUADIO_API void logException(cException e);
	/// gets time as string to be used in log
	std::string getTimeString();
	/// handle to log file
	std::ofstream logFile;

};

#endif //LOGMANAGER_H_INCLUDED