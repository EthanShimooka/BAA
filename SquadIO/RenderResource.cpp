#pragma once
#include "RenderManager.h"


RenderResource::RenderResource(){}

RenderResource::~RenderResource(){}

void RenderResource::unload(){
	if (mSurface){
		SDL_FreeSurface(mSurface);
		mSurface = NULL;
	}
	//bLoaded=true;
}

void RenderResource::load(){
	//Can load BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV file formats

	//TODO: variable 'filename' is inherited from the cResource class yet to be implemented
	SDL_Surface *tempSurface = IMG_Load(m_Filename.c_str());

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

