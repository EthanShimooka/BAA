#pragma once
#ifndef SDL2DRENDERMANAGER_H_INCLUDED
#define SDL2DRENDERMANAGER_H_INCLUDED


#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
//#include <Windows.h>
#include <math.h>
#include <list>

#include "EngineObject.h"
#include "gameResource.h"
#include "SDLRenderObject.h"
#include "Tinyxml2.h"
#include "sdl2\SDL.h"
#include "sdl2\SDL_image.h"
#include "sdl2\SDL_ttf.h"
#include "SceneManager.h"



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
	//A lot of the variables below should be private, and not be called directly
	//TODO: make get and set functions for the below variables
	/// renderWindow holds the pointer to the game's window
	SDL_Window* renderWindow;
	/// windowSurface is the image that appears in the window
	SDL_Surface* windowSurface;
	/// background holds an image that is repeated in the background of the window
	SDL_Texture* background;
	/// renderer allows image texture to be loaded from the graphics card
	SDL_Renderer* renderer;
	/// zoom alters how much of the scene is visible to the window
	float zoom;
	/// minZoom is the minimum value of zoom
	float minZoom;
	/// cameraPoint is a point somewhere in the scene that is the center of the window
	struct point{
		float x;
		float y;
		float z;
	} cameraPoint;
	bool flippedScreen;
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
	

	bool isObjOnScreen(SDLRenderObject * obj);
	bool isPointInBounds(int x, int y, int l, int r, int t, int b);
	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);
	// not implemented, but may be useful later if you want the camera to ignore anything out of bounds
	SQUADIO_API void setWorldSize(unsigned int width, unsigned int height);
	// not implemented, but useful if filenames are likely to change often and may be useful for dynamically created textures
	SQUADIO_API void setBackground(SDL_Texture* texture);
	// loads an image given a specific filename.
	SQUADIO_API void setBackground(std::string filename);
	/// turn a world point into a window point
	SQUADIO_API void worldCoordToWindowCoord(int &winx, int &winy, float worx, float wory, float worz = 0.0);
	/// turn a window point into a world point
	SQUADIO_API void windowCoordToWorldCoord(float &worx, float &wory, int winx, int winy, float worz = 0.0);
	void renderObjectAsImage(SDLRenderObject * obj);
	void renderObjectAsRect(SDLRenderObject * obj);
	// given a specific point in the game world, compare the distance of an object from the center
	// and the min distance it needs to be visible, returning the ratio that can be used to zoom out or in
	SQUADIO_API float zoomRatio(float x1, float y1, float minSize = 1, float scaling = 1);
	/// function renders the background image, tiling starting from the origin, and cut along the edges of the window
	SQUADIO_API void renderBackground();
	/// change the point where the camera renders from
	SQUADIO_API void setCameraZ(float z);
	SQUADIO_API void setCameraPoint(float x, float y);
	SQUADIO_API void setCameraPoint(float x, float y, float z);
	/// Function that takes the list of render	able objects (renderObjects) and 
	/// draws them on screen. 
	/// Objects are rendered in order of the list from first to last.	
	SQUADIO_API void renderAllObjects();

	SQUADIO_API void getWindowSize(int *w, int *h);

	/// Render Objects is the list of pointers to SDLRenderObjects.
	std::list<SDLRenderObject*> renderObjects;

	/// Changes the mouse cursor to crosshair
	//SQUADIO_API void cursorToCrosshair();

	std::list<SDLRenderObject*> windowObjects;

	/// Changes the mouse cursor to crosshair
	SQUADIO_API SDL_Cursor* cursorToCrosshair();
	/// Creates crosshair cursor and returns it as SDL_Cursor*
	static SDL_Cursor* initCursorCrosshair(const char *image[]);

	SQUADIO_API void freeCursor(SDL_Cursor* cursor);

};

#endif SDL2DRENDERMANAGER_H_INCLUDED