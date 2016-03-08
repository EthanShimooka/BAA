/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* gameResource.h
* External Libraies: TinyXML 2.0
* Team Squabble Squad
* 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#include "EngineObject.h"
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string> //maybe




// To be used with ResourceManager. Refer to Resource Manager for 
// RESOURCE_TYPE enums. Class to be overriden in respect to file
// type.

typedef enum {
	RESOURCE_NULL = 0,
	RESOURCE_IMG = 1,
	RESOURCE_MOV = 2,
	RESOURCE_AUDIO = 3,
	RESOURCE_TEXT = 4,
}RESOURCE_TYPE;


/**
* gameResource is an abstract container for various resources,
 such as graphics and audio, text and cfg files. The resource
 is to be overridden by file type for each respective manager.
*
*/

class gameResource :
	public EngineObject
{
private:
protected:
public:

	/// Resource Id
	unsigned int m_ResourceID;
	/// Scope of resource
	unsigned int m_Scope;
	/// Is loaded.
	bool m_Bloaded;
	/// Name of Resource encapsulated
	std::string m_Filename;
	/// Resource Type 
	RESOURCE_TYPE m_Type;
	/// width of sprite sheet
	unsigned int width = 1;
	/// height of sprite sheet
	unsigned int height = 1;
	/// max frames of sprite sheet
	unsigned int max = 1;
	/// Destructor
	virtual ~gameResource(){};
	/// Virtual function for loading into memory. To be Overridden
	virtual void load(){};
	/// Virtual function for unloading from memory. To be Overridden
	virtual void unload(){};

	/// initalizer
	inline gameResource()
	{
		m_ResourceID = m_Scope = 0;
		m_Type = RESOURCE_NULL;
	}

};

