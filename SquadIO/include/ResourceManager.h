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

#include "sdl2\SDL.h"
#include "sdl2\SDL_image.h"

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string> //maybe
#include "LogManager.h"
#include "Tinyxml2.h"  //XML library

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

/**
*  ResourceManager is a class singleton a that handles parsing of file
paths from XML doccuments, and provides an interface for dynamic 
loading and unloading from memory, depending on the scene scope
specified in the resource XML file.
*
*/
class ResourceManager :
	public EngineObject
{
private:
protected:
	/// Singleton instantiation.
	inline ResourceManager(){
		m_CurrentScope = m_ResourceCount = 0;
	}
	/// Class Destructor
	~ResourceManager();
	/// Static Instantiation
	static ResourceManager resourceManager;
	/// Game-state current scope
	unsigned int m_CurrentScope;
	/// Number of resources both loaded and unloaded
	unsigned int m_ResourceCount;

public:

	/// Singleton Accessor function
	SQUADIO_API static ResourceManager * GetResourceManager();
	/// Map of pointers to corrisponding gameResource objects
	/// and an unsigned int as an accessor number
	std::map<unsigned int, std::list<gameResource*>> m_Resources;

	/// fetches resource ID 
	SQUADIO_API	gameResource* findResourcebyID(unsigned int RID);
	SQUADIO_API	gameResource* findResourcebyFilename(std::string RFN);

	/// clears all resources and scopes
	SQUADIO_API	void clear();
	
	/// loads all resouces from XML 
	SQUADIO_API bool loadFromXMLFile(std::string Filename);

	/// Sets the current scope. Scene Dependent
	SQUADIO_API	void setCurrentScope(unsigned int Scope);

	/// fetches resource count
	SQUADIO_API	const unsigned int getResourceCount(){
		return m_ResourceCount;
	}

};

#endif //