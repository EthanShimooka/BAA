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

class RenderResource : public gameResource {
private:
protected:
public:
	SDL_Surface *mSurface;

	~RenderResource();
	SQUADIO_API void load();
	SQUADIO_API void unload();
	SQUADIO_API RenderResource();
};

#endif RENDERRESOURCE_H_INCLUDED