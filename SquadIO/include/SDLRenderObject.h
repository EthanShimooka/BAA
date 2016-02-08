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
	//NOTE: when we make position, rotation, etc. private members we either need to call
	//the appropriate getter setter functions in RenderManager->renderAllObjects (doable) or use c++ friend feature (doable just different)
private:
protected:
public:
	/// anchor = center of rotation and center of render
	/// the origin is the top left corner of the object,
	/// and {1,1} represents the bottom right corner
	struct point {
		float x;
		float y;
	} anchor;
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
	double rotation;
	bool flipH;
	bool flipV;
	bool visible;
	int layer;
	SQUADIO_API bool operator<(const SDLRenderObject& rhs);
	/// SDL color key paramater, usually should not be tampared with
	SDL_Color colorKey;
	/// A key to enable color filtering 
	bool colorKeyEnabled;
	///  Constructor?
	SQUADIO_API SDLRenderObject();
	/// Set a resource object from a Render Resource onto a SDL surface 
	SQUADIO_API void setResourceObject(RenderResource *source);
	/*SQUADIO_API SDL_Rect* getRenderRect();
	SQUADIO_API void setRenderRect(SDL_Rect rect);
	SQUADIO_API void resetRenderRect();
	SQUADIO_API SDL_Point getPosition();
	SQUADIO_API void setPosition(SDL_Point point);
	SQUADIO_API float getRotation();
	SQUADIO_API void setRotation(float degrees);
	SQUADIO_API bool getVisibility();
	SQUADIO_API void setVisibility(bool flag);*/
	/// Abstract update function to be overriden.
	SQUADIO_API void setColorKey(unsigned int r, unsigned int g, unsigned int b);
	SQUADIO_API virtual void update(){};
};

#endif SDLRENDEROBJECT_H_INCLUDED