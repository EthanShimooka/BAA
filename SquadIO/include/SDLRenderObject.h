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


class SDLRenderObject : public EngineObject{
private:
protected:
public:
	RenderResource *renderResource;
	SDL_Rect renderRect;
	float posX;
	float posY;
	bool visible=true;
	SDL_Color colorKey;
	bool colorKeyEnabled;
	SQUADIO_API SDLRenderObject();
	SQUADIO_API void setResourceObject(RenderResource *source);
	SQUADIO_API virtual void update(){};
};

#endif SDLRENDEROBJECT_H_INCLUDED