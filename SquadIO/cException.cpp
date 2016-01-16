#include "LogManager.h"
using namespace std;

cException::cException(int aErrorNumber, string aErrorDesc, string aSrcFileName, int aLineNumber)
{
	//set exception properties
	errorNumber = aErrorNumber;
	errorDesc = aErrorDesc;
	srcFileName = aSrcFileName;
	lineNumber = aLineNumber;

	//write properties to a human-readable string
	std::stringstream errStr;
	errStr << "Error Num: " << errorNumber << "\nError Description: " << errorDesc << "\n Source File Name: " << srcFileName << "\nLine Number: " << lineNumber << "\n";

	errText = errStr.str();

}

//what method will be called by the error log manager to write exception to log file
const char* cException::what()
{
	return errText.c_str();
}

