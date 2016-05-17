#pragma once
#include "include\RenderResource.h"
#include "include\RenderManager.h"

RenderResource::RenderResource(){}
RenderResource::RenderResource(RenderResource * resource){
	mTexture = resource->mTexture;
}

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
	std::string path = "resources/" + m_Filename;
	SDL_Surface *tempSurface = IMG_Load(path.c_str());

	//SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(RenderManager::getRenderManagerRenderer(), tempSurface);
	mTexture = SDL_CreateTextureFromSurface(RenderManager::getRenderManagerRenderer(), tempSurface);

	if (tempSurface){
		//free old buffer

		SDL_FreeSurface(tempSurface);
		if (mTexture){
			//delete previous texture
			//SDL_DestroyTexture(mTexture);
			//replace with new texture
			//mTexture = tempTexture;
			//SDL_FreeSurface(tempSurface);//deletes both temp and mSurface
		}
	}
	else{
		printf("Unable to load the image %s! SDL_image Error: %s\n", m_Filename.c_str(), IMG_GetError());
	}
}


void RenderResource::setBlendMode(SDL_BlendMode blendMode){
	SDL_SetTextureBlendMode(mTexture, blendMode);
}
void RenderResource::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void RenderResource::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(mTexture, alpha);
}