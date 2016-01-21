/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *    
* ResourceManager.h
* External Libraies: TinyXML 2.0 
* Copyright Team Squabble Squad
* Distributed under GNU Public License
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED 

#include "EngineObject.h"
#include "gameResource.h"
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string> //maybe

// #include "TinyXML.h"  

class ResourceManager :
	public EngineObject
{
private:
protected:

	//scope
	unsigned int m_CurrentScope;
	//No. of resources both loaded and unloaded
	unsigned int m_ResourceCount;

public:
	~ResourceManager();

	std::map<unsigned int, std::list<gameResource*>> m_Resources;

	gameResource* findResourcebyID(unsigned int RID);

	//clears all resources and scopes
	void clear();
	
	//loads all resouces from XML 
	bool loadFromXMLFile(std::string Filename);

	//Sets the current scope. Scene Dependent
	void setCurrentScope(unsigned int Scope);


	const unsigned int getResourceCount(){ return m_ResourceCount;
	}

	inline ResourceManager(){
		m_CurrentScope = m_ResourceCount = 0;

	}
};

#endif //