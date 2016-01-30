#pragma once
#include "include\RenderResource.h"
#include "include\RenderManager.h"


RenderResource::RenderResource(){}

RenderResource::~RenderResource(){}

/*RenderResource::RenderResource(const gameResource& source){
	this->m_Filename = source.m_Filename;
	this->mSurface = source.
}*/

void RenderResource::unload(){
	if (mTexture){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	//bLoaded=true;
}

void RenderResource::load(){
	//Can load BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV file formats

	//MUST PREPEND THE RESOURCE PATH FIRST
<<<<<<< HEAD
	char path[64] = "resources/";
	strcat_s(path,  m_Filename.c_str());
	SDL_Surface *tempSurface = IMG_Load(path);
	mTexture = SDL_CreateTextureFromSurface(RenderManager::getRenderManagerRenderer(), tempSurface);
=======
	std::string path = "resources/" + m_Filename;
	SDL_Surface *tempSurface = IMG_Load(path.c_str());
>>>>>>> refs/remotes/origin/nu-master

	if (tempSurface){
		//free old buffer
<<<<<<< HEAD
		SDL_FreeSurface(tempSurface);
		if (mTexture){
=======
		//SDL_FreeSurface(tempSurface);//deletes both temp and mSurface
		if (mSurface){
>>>>>>> refs/remotes/origin/nu-master
			m_Bloaded = true;
		}
	}
	else{
		printf("Unable to load the image %s! SDL_image Error: %s\n", m_Filename.c_str(), IMG_GetError());
	}
}

