#pragma once
#include "include\AudioManager.h"

SDLAudioObject::SDLAudioObject(){}

// 
void SDLAudioObject::setResourceObject(gameResource* source) {
	if (source) {
		audioResource = (AudioResource*)source;
		// need to set isBgm somewhere here
		isBgm = false;
	}
}