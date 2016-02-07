#pragma once
#include "include\AudioManager.h"
// #include "include\LogManager.h"

using namespace std;

AudioManager* AudioManager::audioInstance = nullptr;

bool InitAudio() {
	// load support for ogg, mp3, and flac filetypes
	int flags = MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC;
	int init = Mix_Init(flags);
	if (init&flags != flags) {
		printf("Error in InitAudio-Mix_Init: %s", Mix_GetError());
		return false;
	}
	// open 22050Hz, signed 16bit, system byte order, stereo, using 4096 byte chunks
	// tune size based on bgm or effect
	// can use SDL_mixer functions now
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		printf("Error in InitAudio-Mix_OpenAudio: %s", Mix_GetError());
		return false;
	}
	return true;
}

void QuitAudio() {
	// may need Mix_QuerySpec to determine number of times Mix_CloseAudio() needs to be called
	// should only be once if InitAudio() is only called once
	// calls this once all audio is stopped
	Mix_CloseAudio();
	Mix_Quit();
}

// constructor
AudioManager::AudioManager() {
	InitAudio();
}

// destructor
AudioManager::~AudioManager() {
	QuitAudio();
}

// get or create single instance
AudioManager* AudioManager::getInstance() {
	if (!audioInstance) {
		audioInstance = new AudioManager();
	}
	return audioInstance;
}

