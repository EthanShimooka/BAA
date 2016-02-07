// SDL must be initialized with SDL_INIT_AUDIO before call (probably in render manager?? wherever SDL_Init(params) is called)

// possibly useful functions for later:
// Mix_PlayChannel with -1 as param to play in first unreserved channel
// there's some other useful functions like Mix_FadeInChannel
// can write wrappers for different play function types for easy access
// Mix_Volume(int channel, int volume) can set the volume of different channels
// Mix_Pause(int channel) -1 for all channels
// Mix_Resume(int channel) -1 for all channels
// Mix_Playing(int channel) -1 returns number of channels playing, pass specific channel > 0 returns 1 for playing

// use i=Mix_GetNumMusicDecoders(); and Mix_GetMusicDecoder(i) to see which decoders are valid

#pragma once
#ifndef AUDIOMANAGER_H_INCLUDED
#define AUDIOMANAGER_H_INCLUDED

#include "EngineObject.h"
#include "gameResource.h"
#include "Tinyxml2.h"
#include "sdl2\SDL.h"
#include "sdl2\SDL_mixer.h"

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

class AudioManager : public EngineObject {
public:
	// returns this instance of AudioManager
	SQUADIO_API static AudioManager* getInstance();

	// not sure what this does exactly
	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);

	// needed functions:
	// play bgm, pause bgm, stop bgm
	// play effect, pause effect, stop effect
	// clear and free all

	// no need for update function I think if all audio is loaded during init??

protected:
	// constructor only called by getInstance()
	AudioManager();
	~AudioManager();
	AudioManager(AudioManager const&) {};
	void operator=(AudioManager const&) {};

	// single instance of AudioManager
	static AudioManager* audioInstance;

private:
	// init (called by constructor which should call Mix_Init(int flags)
	bool InitAudio();

	void QuitAudio();

	// need to store all AudioResources here which can be accessed through the functions above
	// e.g. AudioManager.play(AudioFileID) where the play function finds and plays the file
	AudioResource* bgm;
	unordered_map<AudioResource>
};

#endif // AUDIOMANAGER_H_INCLUDED
