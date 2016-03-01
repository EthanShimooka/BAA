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
#include "SDLAudioObject.h"
#include "Tinyxml2.h"
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

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

class AudioManager : public EngineObject {
public:
	// returns this instance of AudioManager
	SQUADIO_API static AudioManager* getAudioInstance();

	// not sure what this does exactly
	SQUADIO_API gameResource* loadResourceFromXML(tinyxml2::XMLElement* element);

	// needed functions:
	// play bgm, pause bgm, stop bgm
	// play effect, pause effect, stop effect
	// clear and free all
	SQUADIO_API void loadAllAudio();

	// the ID passed in is found at SDLAudioObject->audioResource->m_ResourceID
	// maybe m_ResourceID for audio will just match the position in the list it's stored
	SQUADIO_API void playByName(std::string name);
	SQUADIO_API void pauseByName(std::string name);
	SQUADIO_API void stopByName(std::string name);

	// need to store all SDLAudioObjects here which can be accessed through the functions above
	// e.g. AudioManager.play(AudioFileID) where the play function finds and plays the file
	std::list<SDLAudioObject*> audioObjects;

	// no need for update function I think if all audio is loaded during init??

protected:
	// constructor only called by getAudioInstance()
	AudioManager();
	~AudioManager();
	AudioManager(AudioManager const&) {};
	void operator=(AudioManager const&) {};

	// single instance of AudioManager
	static AudioManager* audioInstance;

private:
	// init (called by constructor which should call Mix_Init(int flags)
	bool InitAudio();

	// quit called at end when cleaning up memory
	void QuitAudio();
};

#endif // AUDIOMANAGER_H_INCLUDED
