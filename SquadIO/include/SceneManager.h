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

class SceneListener : public EngineObject {
public:	
	SCENE_EVENT_TYPE m_ListenFor;

	virtual void Event(SceneManager* Manager, void* customData) const = 0;

};

///////////////////////////////////////////////////////////////////////////////////////////////

class Timer : public EngineObject {
private:
protected:
public:
	unsigned int m_ID;
	DWORD m_StartTime;
	DWORD m_Interval;
	bool m_Expired;

	Timer() {
		m_ID = 0;
		m_StartTime = 0;
		m_Interval = 0;
		m_Expired = false;
	}

	void start() {
		m_StartTime = timeGetTime();
		m_Expired = false;
	}

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

class SceneObject : public SDLRenderObject {
private:
protected:
public:
}; //end class SceneObject


/////////////////////////////////////////////////////////////////////////////////////////////

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

class SceneManager : public EngineObject {
private:
	SQUADIO_API static SceneManager * GetSceneManager();
protected:
	SceneManager();
	~SceneManager(){}
	static SceneManager sceneManager;
	void addLayerObjects(Layer* layer, tinyxml2::XMLElement* element);
	void checkTimerExpired();
public:
	std::list<Layer*> m_Layers;
	std::list<Timer*> m_Timers;
	std::list<SceneListener*> m_Listeners;

	Layer* addLayer(std::string Name);
	Layer* findLayer(std::string Name);
	void removeLayer(std::string Name);
	void sortLayers();

	bool loadFromXMLFile(std::string Filename);
	
	void addTimer(unsigned int id, DWORD interval);
	void addListener(SceneListener* object);

	void update();
};//end class SceneManager

/////////////////////////////////////////////////////////////////////////////////////////////

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