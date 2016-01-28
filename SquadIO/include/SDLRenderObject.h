#pragma once
#ifndef SDLRENDEROBJECT_H_INCLUDED
#define SDLRENDEROBJECT_H_INCLUDED

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include "EngineObject.h"
#include "RenderResource.h"
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
* SDLRender Object is the renderable object that take a pointer to a renderResource (gameResource).
* SDLRenderObject also contains the renderable options that are fed into the renderManager.
*/

class SDLRenderObject : public EngineObject{
private:
protected:
public:

	/// pointer to renderResource, which is derived from the RenderManager
	/// function loadfromXML()
	RenderResource *renderResource;
	/// SDL Rect object. contains the definition of a rectangle, 
	/// with the origin at the upper left.
	SDL_Rect renderRect;
	/// Object position on the x axis
	float posX;
	/// Object position on the y axis
	float posY;
	/// bool visible; //uninitialized
	bool visible=true; ////////////////////////////IT IS INITIALIZED YO
	/// SDL color key paramater, usually should not be tampared with
	SDL_Color colorKey;
	/// A key to enable color filtering 
	bool colorKeyEnabled;
	///  Constructor?
	SQUADIO_API SDLRenderObject();
	/// Set a resource object from a Render Resource onto a SDL surface 
	SQUADIO_API void setResourceObject(RenderResource *source);
	/// Abstract update function to be overriden.
	SQUADIO_API virtual void update(){};
};

#endif SDLRENDEROBJECT_H_INCLUDED