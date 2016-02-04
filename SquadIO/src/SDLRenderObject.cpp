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