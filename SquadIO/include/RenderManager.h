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

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include <list>

/**
* RenderManager d

*/

class RenderManager : public EngineObject {
private:
protected:
	RenderManager();
	/// why is the destructor virtual?
	virtual ~RenderManager(){} //why is the destructor virtual?
	/// Static instance of RenderManager class
	static RenderManager renderManager;
public:
	/// Singlelton accessor fuinction for RenderManager class.
	SQUADIO_API static RenderManager* getRenderManager();
	/// 
	SDL_Window* renderWindow;
	/// 
	SDL_Surface* windowSurface;
	///
	std::stringstream videoInfo;
	/// Initializes SDL window enviroment. Returns true
	/// if successful, returns false if not.
	/// TODO: Create a CFG file that will have game 
	/// height settings.
	SQUADIO_API bool init(unsigned int width = 800,
		unsigned int height = 600, bool fullScreen = false,
		char* WindowTitle = 0);
	/// Clears, free's, and destroys SDL window *INCOMPLETE*
	SQUADIO_API void free();
	/// Rendermanager update loop.a
	SQUADIO_API bool update();
	/// Swaps from full screen SDL window.
	SQUADIO_API void toggleFullScreen();
	/// loadResourceFromXML() is called from ResourceManager's
	/// loadFromXMLFile(std::string Filename). It creates a
	/// renderResource, which is derived from gameResource.

	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);
	/// Function that takes the list of renderable objects (renderObjects) and 
	/// draws them on screen. 
	/// Objects are rendered in order of the list from first to last.

	SQUADIO_API void renderAllObjects();
	/// Render Objects is the list of pointers to SDLRenderObjects.
	std::list<SDLRenderObject*> renderObjects;
};

#endif SDL2DRENDERMANAGER_H_INCLUDED