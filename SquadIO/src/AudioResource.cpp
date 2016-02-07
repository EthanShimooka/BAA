#pragma once
#include "include\AudioResource.h"
#include "include\AudioManager.h" // what goes in here?

AudioResource::AudioResource() : bgm(NULL), effect(NULL), isBgm(false) {}

AudioResource::~AudioResource(){}

// call before load() every time for no memory leaks
// clears either bgm or effect depending on type of sound
void AudioResource::unload() {
	if (bgm) {
		Mix_FreeMusic(bgm);
		bgm = NULL;
	}
	if (effect) {
		Mix_FreeChunk(effect);
		effect = NULL;
		isBgm = false;
	}
}

void AudioResource::load() {
	// can only call Mix_LoadWAV and Mix_LoadMUS after Mix_OpenAudio
	// SDL must be initialized with SDL_INIT_AUDIO before call
	// int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
	// MIX_DEFAULT_FREQUENCY is 22050 instead of 44100
	// MIX_DEFAULT_FORMAT = AUDIOS16SYS in SDL
	// channels: 2=stereo 1=mono
	// chunksize = 4096 for music, maybe 1024 or 2048 for effects?
	// Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	std::string filename = "resources/" + m_Filename;
	/*
	if (audioType == 0) {
		bgm = Mix_LoadMUS(filename.c_str());
	}
	*/
	//if (audioType == 1) {
		effect = Mix_LoadWAV(filename.c_str());
	//}

	// check for load success
	if (bgm || effect) {
		// pass
	} else {
		printf("Unable to load the audio file %s! SDL_mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}
}
