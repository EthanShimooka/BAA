#pragma once
#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <windows.h>
#include <math.h>
#include "include/ResourceManager.h"
#include "include/SDLRenderObject.h"
#include "include/RenderResource.h"

///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {SE_TIMER_EXPIRED=0}SCENE_EVENT_TYPE;

class SceneManager; //definition lower down in this file

///////////////////////////////////////////////////////////////////////////////////////////////


/**
* SceneListener abstract class. To be overridden.
*
*/
class SceneListener : public EngineObject {
public:	
	SCENE_EVENT_TYPE m_ListenFor;

	virtual void Event(SceneManager* Manager, void* customData) const = 0;

};

///////////////////////////////////////////////////////////////////////////////////////////////


/**
*   ***DEFINED IN HEADER (SceneManager.h)***
*  The Timer class is used for keying events in the
 Scenelistnert class.
*
*/
class Timer : public EngineObject {
private:
protected:
public:
	/// Timer Object ID
	unsigned int m_ID;
	/// Timer start time. Assigned in Timer::start()
	DWORD m_StartTime;
	/// user defined interval
	DWORD m_Interval;
	/// flag for interval used in update()
	bool m_Expired;

	/// timer object constructor
	Timer() {
		m_ID = 0;
		m_StartTime = 0;
		m_Interval = 0;
		m_Expired = false;
	}


	/// Sets a start time and begins interval.
	void start() {
		m_StartTime = timeGetTime();
		m_Expired = false;
	}

	/// invokes timegettime(), returns system time, in milliseconds.
	/// checks for interval and returns when interval is reached.
	void update(){
		if (m_Expired)
			return;
		
		DWORD ElapsedTime = timeGetTime() - m_StartTime;

		if (ElapsedTime >= m_Interval){
			m_Expired = true;
		}
	}
}; //end class Timer

/////////////////////////////////////////////////////////////////////////////////////////////



/**
*
*
*/
class SceneObject : public SDLRenderObject {
private:
protected:
public:
}; //end class SceneObject


/////////////////////////////////////////////////////////////////////////////////////////////



/**
*
*
*/
class Layer : public EngineObject {
private:
protected:
public:
	//render objects for the layer
	Layer();
	bool m_Visible;
	unsigned int m_ZOrder;
	float m_PosX;
	float m_PosY;
	std::string m_Name;
	std::list<SceneObject*> m_SceneObjects;
	void update();
}; //end class Layer

//////////////////////////////////////////////////////////////////////////////////////////////



/**
* Scene Manager Singeton
*
*/
class SceneManager : public EngineObject {
private:
protected:
	/// Constructor
	SceneManager();
	/// Destructor
	~SceneManager(){}
	/// Singleton Static instance 
	static SceneManager sceneManager;
	/// Reads in a layer object and fetches elements
	void addLayerObjects(Layer* layer, tinyxml2::XMLElement* element);
	/// Checks for m_Expired flag in Timer
	void checkTimerExpired();
public:
	/// Singleton Accessor Function
	SQUADIO_API static SceneManager * GetSceneManager();
	/// list containing layer objects
	std::list<Layer*> m_Layers;
	/// list containing event timer objects
	std::list<Timer*> m_Timers;
	/// list containing event listeners
	std::list<SceneListener*> m_Listeners;

	/// Add layer to scene.
	Layer* addLayer(std::string Name);
	/// look up layer object by name
	Layer* findLayer(std::string Name);
	/// Delete layer by name
	void removeLayer(std::string Name);
	/// Sort Existing layers smallest to biggest.
	void sortLayers();
	/// loads up scene elements From XML file specified.
	/// pushe
	SQUADIO_API bool loadFromXMLFile(std::string Filename);
	/// creates a new timer and pushes to m_Timers list
	void addTimer(unsigned int id, DWORD interval);
	/// creates new SceneListner and pushes to m_Listners
	void addListener(SceneListener* object);
	/// 
	void update();
};//end class SceneManager

/////////////////////////////////////////////////////////////////////////////////////////////


/**
* overriden sceneListnerclass
*
*/
class TestListener : public SceneListener {
private:
protected:
public:
	TestListener() {
		m_ListenFor = SE_TIMER_EXPIRED;
	}

	void Event(SceneManager* Manager, void* customData) const {
		Layer* layer = Manager->findLayer("layer2");
		layer->m_Visible = !layer->m_Visible;
	}
}; //end class TestListener

/////////////////////////////////////////////////////////////////////////////////////////////

#endif //SCENEMANAGER_H_INCLUDED