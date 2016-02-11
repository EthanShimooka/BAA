// MULTIPLE WAYS TO HAVE ISBGM FLAG. can be done in gameResource?

#pragma once
#include "include\AudioManager.h"
// #include "include\LogManager.h"

using namespace std;

AudioManager* AudioManager::audioInstance = nullptr;

bool AudioManager::InitAudio() {
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

	// load all audio resources, this is assuming we don't need dynamically loading music
	// everything is loaded at the start and can be accessed until AudioManager is freed
	for (auto iter = audioObjects.cbegin(); iter != audioObjects.cend(); ++iter) {
		(*iter)->audioResource->load();
	}

	return true;
}

void AudioManager::QuitAudio() {
	// unload all audio resources
	for (auto iter = audioObjects.cbegin(); iter != audioObjects.cend(); ++iter) {
		/*
		if ((*iter)->isBgm){
			Mix_FreeMusic((*iter)->audioResource->bgm);
		}
		else {
			Mix_FreeChunk((*iter)->audioResource->effect);
		}
		*/
		(*iter)->audioResource->unload();
	}
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
AudioManager* AudioManager::getAudioInstance() {
	if (!audioInstance) {
		audioInstance = new AudioManager();
	}
	return audioInstance;
}

gameResource* AudioManager::loadResourceFromXML(tinyxml2::XMLElement *element){
	if (element){
		gameResource* resource = new AudioResource();

		for (const tinyxml2::XMLAttribute* elementAttrib = element->FirstAttribute(); elementAttrib; elementAttrib = elementAttrib->Next()){
			std::string AttribName = elementAttrib->Name();
			std::string AttribValue = elementAttrib->Value();
			if (AttribName == "UID"){
				resource->m_ResourceID = atoi(AttribValue.c_str());
			}
			if (AttribName == "filename"){
				resource->m_Filename = AttribValue;
			}
			if (AttribName == "scenescope"){
				resource->m_Scope = atoi(AttribValue.c_str());
			}
		}

		// create an SDLAudioObject and push that to the global list in AudioManager
		// ideally, the m_ResourceID for audio should start from 0 and increase
		// Then audio can easily be played 
		SDLAudioObject* obj = new SDLAudioObject();
		obj->setResourceObject(resource);
		audioObjects.push_back(obj);

		return resource;
	}
	return NULL;
}

void AudioManager::playByID(int id) {
	SDLAudioObject* playThis = audioObjects[id];
	if (playThis->isBgm) {
		// check that no background music is already playing
		if (Mix_PlayingMusic() == 0) {
			// first arg is what we play, second arg is how many loops
			Mix_PlayMusic(playThis->audioResource->bgm, -1);
		}
	} else {
		// first arg is what channel to play in (-1 = first free channel)
		// second arg is what effect we play
		// third arg is how many times to loop the effect
		Mix_PlayChannel(-1, playThis->audioResource->effect, 0);
	}
}

// should never really be needed since effects are played once and automatically stop
// and music should just be stopped when it's not used
void AudioManager::pauseByID(int id) {

}

// should only need this for bgm since effects are played once on first available channel and then stopped
void AudioManager::stopByID(int id) {
	SDLAudioObject* stopThis = audioObjects[id];
	if (stopThis->isBgm) {
		// check that bgm is playing
		if (Mix_PlayingMusic != 0) {
			Mix_HaltMusic();
		}
	}
}