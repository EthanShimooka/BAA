#pragma once
#ifndef RENDERRESOURCE_H_INCLUDED
#define RENDERRESOURCE_H_INCLUDED

//throw macro to throw exceptions

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us

#include "sdl2\SDL.h"
#include "sdl2\SDL_image.h"

#include <string.h>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>

#include <math.h>
#include <list>
#include "gameResource.h"



/**
* RenderResource is the interface for interacting with the resourceManager. The a RenderResouce contains 
 overriden fucntions inherrited from the GameResource class. The RenderResource als contains a
 SDL surface/

*/
class RenderResource : public gameResource {
private:
protected:
public:
	SDL_Texture *mTexture;
	SDL_Texture *baseImage;
	/// Destructor 
	~RenderResource();
	/// Load gets called in resourceManager.setSceneScope() 
	SQUADIO_API void load();
	/// UnLoad gets called in resourceManager.setSceneScope(). 
	/// Be sure to unload before you call Load. Every. Time.
	SQUADIO_API void unload();
	SQUADIO_API void setBlendMode(SDL_BlendMode blendMode);
	SQUADIO_API void setColor(Uint8 red, Uint8 green, Uint8 blue);
	SQUADIO_API void setAlpha(Uint8 alpha);
	/// Cosntructor
	SQUADIO_API RenderResource();
	SQUADIO_API RenderResource(RenderResource * resource);

};

#endif RENDERRESOURCE_H_INCLUDED