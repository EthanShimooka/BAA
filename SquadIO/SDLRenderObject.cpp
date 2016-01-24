#pragma once
#include "RenderManager.h"

using namespace std;

void SDLRenderObject::setResourceObject(RenderResource *resource){
	if (resource){
		renderResource = resource;
		renderRect.w = renderResource->mSurface->w;
		renderRect.h = renderResource->mSurface->h;
		if (colorKeyEnabled){
			Uint32 colorkey = SDL_MapRGB(renderResource->mSurface->format, colorKey.r, colorKey.g, colorKey.b);
			SDL_SetColorKey(renderResource->mSurface, SDL_TRUE, colorkey);
		}
	}
}