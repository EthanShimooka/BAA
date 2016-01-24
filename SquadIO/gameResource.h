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

// #include "TinyXML.h"  maybe?


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


class gameResource :
	public EngineObject
{
private:
protected:
public:

	unsigned int m_ResourceID;
	unsigned int m_Scope;
	std::string m_Filename;
	RESOURCE_TYPE m_Type;

	//to be overloaded
	virtual ~gameResource(){};
	virtual void load(){};
	virtual void unload(){};
	//TODO: Might need a bool flag for resources to say 
	//whether or not they are loaded later on

	inline gameResource()
	{
		m_ResourceID = m_Scope = 0;
		m_Type = RESOURCE_NULL;
	}

};

