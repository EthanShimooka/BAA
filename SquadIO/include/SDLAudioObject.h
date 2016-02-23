#pragma once
#ifndef SDLAUDIOOBJECT_H_INCLUDED
#define SDLAUDIOOBJECT_H_INCLUDED

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

#include "EngineObject.h"
#include "AudioResource.h"
#include "sdl2\SDL.h"
#include "sdl2\SDL_mixer.h"

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include <list>

/*
* SDLAudioObject is the "renderable" object that take a pointer to an audioResource (gameResource).
*/
class SDLAudioObject : public EngineObject{
private:
protected:
public:
	AudioResource* audioResource;

	// true for bgm, false for effect
	bool isBgm;

	// constructor
	SQUADIO_API SDLAudioObject();
	/// Set a resource object from a Audio Resource onto a SDL surface 
	SQUADIO_API void setResourceObject(gameResource* source);
};

#endif // SDLAUDIOOBJECT_H_INCLUDED