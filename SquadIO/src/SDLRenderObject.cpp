#pragma once
#include "include\RenderManager.h"


SDLRenderObject::SDLRenderObject(){}
//SDLRenderObject::~SDLRenderObject(){}


void SDLRenderObject::setResourceObject(RenderResource *source){
	if (source){
		renderResource = source;
		renderRect.w = renderResource->mSurface->w;
		renderRect.h = renderResource->mSurface->h;
		if (colorKeyEnabled){
			Uint32 colorkey = SDL_MapRGB(renderResource->mSurface->format, colorKey.r, colorKey.g, colorKey.b);
			SDL_SetColorKey(renderResource->mSurface, SDL_TRUE, colorkey);
		}
	}
}

void SDLRenderObject::setColorKey(unsigned int r, unsigned int g, unsigned int b){
	colorKey.r = r;
	colorKey.g = g;
	colorKey.b = b;
	Uint32 color = SDL_MapRGB(renderResource->mSurface->format, colorKey.r, colorKey.g, colorKey.b);
	SDL_SetColorKey(renderResource->mSurface, SDL_TRUE, color); //SDL_TRUE might need to be SDL_SRCCOLORKEY
}