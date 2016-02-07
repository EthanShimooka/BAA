#pragma once
#ifndef AUDIORESOURCE_H_INCLUDED
#define AUDIORESOURCE_H_INCLUDED

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

#include "sdl2\SDL.h"
#include "sdl2\SDL_mixer.h"

#include <string.h>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <list>
#include "gameResource.h"

class AudioResource : public gameResource {
private:
protected:
public:
	// SDL_mixer uses 2 datatypes for storing audio
	// music is for background music (can only have 1 playing at once)
	// effect is for all other effects (can have multiple playing)
	// might need to use a flag to determine type of AudioResource
	Mix_Music* bgm;
	Mix_Chunk* effect;
	// -1 defaults none, 0 for bgm, 1 for effect
	int type;

	// constructor
	SQUADIO_API AudioResource();
	// destructor
	~AudioResource();
	// overloaded load/unload
	SQUADIO_API void load(int t);
	SQUADIO_API void unload();
};

#endif // AUDIORESOURCE_H_INCLUDED
