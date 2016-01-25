#pragma once
#ifndef RENDERRESOURCE_H_INCLUDED
#define RENDERRESOURCE_H_INCLUDED

//throw macro to throw exceptions
#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(errorNum, errorDesc) throw cException(errorNum, errorDesc, __FILE__, __LINE__);
#endif

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include "EngineObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include <list>
#include "gameResource.h"
#include "Inc/Tinyxml2.h"  //XML library

// TODO: import the tinyxml library
//#include "TimyXML.h"

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