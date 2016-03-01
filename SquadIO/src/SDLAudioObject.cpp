#pragma once
#include "include\AudioManager.h"

SDLAudioObject::SDLAudioObject(){}

// 
void SDLAudioObject::setResourceObject(gameResource* source, bool flag) {
	if (source) {
		audioResource = (AudioResource*)source;
		// need to set isBgm somewhere here
		isBgm = flag;
	}
}