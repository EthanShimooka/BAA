#pragma once
#include "RenderManager.h"

void RenderResource::unload(){
	if (mSurface){
		SDL_FreeSurface(mSurface);
		mSurface = NULL;
	}
	//bLoaded=true;
}

void RenderResource::load(){
	//TODO: variable 'filename' is inherited from the cResource class yet to be implemented
	SDL_Surface *tempSurface = NULL;// = IMG_Load(filemane.c_str());
	if (tempSurface){
		mSurface = tempSurface;
		//free old buffer
		SDL_FreeSurface(tempSurface);
		if (mSurface){
			//TODO: again, implement cResource class
			//bLoaded = true;
		}
	}
}

