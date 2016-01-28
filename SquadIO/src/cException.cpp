#pragma once
#include "include\LogManager.h"

cException::cException(int aErrorNumber, std::string aErrorDesc, std::string aSrcFileName, int aLineNumber)
{
	//set exception properties
	errorNumber = aErrorNumber;
	errorDesc = aErrorDesc;
	srcFileName = aSrcFileName;
	lineNumber = aLineNumber;

	//write properties to a human-readable string
	std::stringstream errStr;
	errStr << "*** ERROR NUM: " << errorNumber << " ***"<<
		"\n Error Description: " << errorDesc << "\n Source File Name: " <<
		srcFileName << "\n Line Number: " << lineNumber << "\n";

	errText = errStr.str();

}

//what method will be called by the error log manager to write exception to log file
const char* cException::what()
{
	return errText.c_str();
}
