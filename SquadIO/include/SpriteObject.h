#pragma once
#ifndef SPRITEOBJECT_H_INCLUDED
#define SPRITEOBJECT_H_INCLUDED

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

// TODO: page 135, add the first two includes: 2DRenderManager.h and ResourceManager.h they are made by us
#include "EngineObject.h"
#include "SDLRenderObject.h"
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
#include "SDLRenderObject.h"

// TODO: import the tinyxml library
//#include "TimyXML.h"




class SpriteObject : public SDLRenderObject{
private:
protected:
	DWORD timeLastFrame;

public:
	unsigned int totalFrames;
	unsigned int framesPerRow;
	unsigned int framesPerColumn;
	unsigned int currentFrame;
	unsigned int startFrame;
	float spriteSpeed;
	unsigned int frameWidth;
	unsigned int frameHeight;

	SQUADIO_API void update();
	SQUADIO_API void play();
	SQUADIO_API void stop();
	SQUADIO_API void setFrameRect(unsigned int frameNumber);
	SpriteObject();
};

#endif SPRITEOBJECT_H_INCLUDED