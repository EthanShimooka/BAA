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
#include <queue>

/**
* RenderManager d

*/

class RenderManager : public EngineObject {
private:
protected:
	/// Constructor.
	RenderManager();
	/// why is the destructor virtual?
	virtual ~RenderManager(){} //why is the destructor virtual?
	/// Static instance of RenderManager class
	static RenderManager renderManager;
	void renderScene();
public:
	/// Singlelton accessor fuinction for RenderManager class.
	SQUADIO_API static RenderManager* getRenderManager();
	SQUADIO_API static SDL_Renderer* getRenderManagerRenderer();
	/// 
	//A lot of the variables below should be private, and not be called directly
	//TODO: make get and set functions for the below variables
	SDL_Window* renderWindow;
	SDL_Surface* windowSurface;
	SDL_Texture* background;
	SDL_Renderer* renderer;
	float zoom;
	float minZoom;
	struct point{
		float x;
		float y;
	} cameraPoint;
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
	SQUADIO_API void update();
	/// Swaps from full screen SDL window.
	SQUADIO_API void toggleFullScreen();
	/// loadResourceFromXML() is called from ResourceManager's
	/// loadFromXMLFile(std::string Filename). It creates a
	/// renderResource, which is derived from gameResource.

	SQUADIO_API bool isReadyToQuit();

	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);
	// not implemented, but may be useful later if you want the camera to ignore anything out of bounds
	SQUADIO_API void setWorldSize(unsigned int width, unsigned int height);
	// not implemented, but useful if filenames are likely to change often and may be useful for dynamically created textures
	SQUADIO_API void setBackground(SDL_Texture* bg);
	// loads an image given a specific filename.
	SQUADIO_API void setBackground(std::string filename);
	// given a specific point in the game world, compare the distance of an object from the center
	// and the min distance it needs to be visible, returning the ratio that can be used to zoom out or in
	SQUADIO_API float zoomRatio(float x1, float y1,float minSize = 1,float scaling = 1);
	SQUADIO_API void renderBackground();
	/// Function that takes the list of renderable objects (renderObjects) and 
	/// draws them on screen. 
	/// Objects are rendered in order of the list from first to last.	
	SQUADIO_API void renderAllObjects();
	/// Render Objects is the list of pointers to SDLRenderObjects.
	std::list<SDLRenderObject*> renderObjects;
	SQUADIO_API static bool compObj(const SDLRenderObject* left, const SDLRenderObject* right);
	SQUADIO_API void sortObjects();
	//std::priority_queue<SDLRenderObject*> renderObjects;
	SceneManager* sceneManager;
};

#endif SDL2DRENDERMANAGER_H_INCLUDED