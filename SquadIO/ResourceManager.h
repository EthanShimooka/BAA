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
#include "LogManager.h"
#include "Inc/Tinyxml2.h"  //XML library

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif


class ResourceManager :
	public EngineObject
{
private:
protected:
	inline ResourceManager(){
		m_CurrentScope = m_ResourceCount = 0;
	}

	~ResourceManager();

	static ResourceManager resourceManager;

	//scope
	unsigned int m_CurrentScope;
	//No. of resources both loaded and unloaded
	unsigned int m_ResourceCount;

public:
	SQUADIO_API static ResourceManager * GetResourceManager();

	std::map<unsigned int, std::list<gameResource*>> m_Resources;

	//fetches resource ID 
	SQUADIO_API	gameResource* findResourcebyID(unsigned int RID);

	//clears all resources and scopes
	SQUADIO_API	void clear();
	
	//loads all resouces from XML 
	SQUADIO_API bool loadFromXMLFile(std::string Filename);

	//Sets the current scope. Scene Dependent
	SQUADIO_API	void setCurrentScope(unsigned int Scope);

	//fetches resource count
	SQUADIO_API	const unsigned int getResourceCount(){
		return m_ResourceCount;
	}

};

#endif //