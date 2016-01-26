#pragma once
#include "include\RenderResource.h"


RenderResource::RenderResource(){}

RenderResource::~RenderResource(){}

/*RenderResource::RenderResource(const gameResource& source){
	this->m_Filename = source.m_Filename;
	this->mSurface = source.
}*/

void RenderResource::unload(){
	if (mSurface){
		SDL_FreeSurface(mSurface);
		mSurface = NULL;
	}
	//bLoaded=true;
}

void RenderResource::load(){
	//Can load BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV file formats

	//MUST PREPEND THE RESOURCE PATH FIRST
	char* path = "resources/";
	//strcat(path, m_Filename.c_str());
	SDL_Surface *tempSurface = IMG_Load(m_Filename.c_str());


	if (tempSurface){
		mSurface = tempSurface;
		//free old buffer
		//SDL_FreeSurface(tempSurface);
		if (mSurface){
			m_Bloaded = true;

		}
	}
	else{
		printf("Unable to load the image %s! SDL_image Error: %s\n", m_Filename.c_str(), IMG_GetError());
	}
}

