#pragma once
#ifndef SDL2DRENDERMANAGER_H_INCLUDED
#define SDL2DRENDERMANAGER_H_INCLUDED


#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include "EngineObject.h"
#include "gameResource.h"
#include "SDLRenderObject.h"
#include "Tinyxml2.h"
#include "sdl2\SDL.h"
#include "sdl2\SDL_image.h"
#include "include\SceneManager.h"

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include <list>


// TODO: import the tinyxml library
//#include "TimyXML.h"


class RenderManager : public EngineObject {
private:
protected:
	RenderManager();
	virtual ~RenderManager(){}
	static RenderManager renderManager;
	void renderScene();
public:
	SQUADIO_API static RenderManager* getRenderManager();
	SDL_Window* renderWindow;
	SDL_Surface* windowSurface;
	std::stringstream videoInfo;
	SQUADIO_API bool init(unsigned int width = 800, unsigned int height = 600, bool fullScreen = false, char* WindowTitle = 0);
	SQUADIO_API void free();
	SQUADIO_API bool update();
	SQUADIO_API void toggleFullScreen();
	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);
	SQUADIO_API void renderAllObjects();

	//NOTE: this list might need to be changed to be pointers
	std::list<SDLRenderObject*> renderObjects;

	SceneManager* sceneManager;
};

#endif SDL2DRENDERMANAGER_H_INCLUDED