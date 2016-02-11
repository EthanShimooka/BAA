#pragma once
#include "include\RenderManager.h"


SDLRenderObject::SDLRenderObject(){
	//initialize values
	posX = 0.0;
	posY = 0.0;
	rotation = 0.0;
	//anchor point 0,0 = top left corner,1,1 = bottom right corner 
	anchor = { 0.5, 0.5 };
	flipH = false;
	flipV = false;
	visible = true;
}
//SDLRenderObject::~SDLRenderObject(){}


void SDLRenderObject::setResourceObject(RenderResource *source){
	if (source){
		renderResource = source;
		//by default, the texture sizes are stored 1:1 scale
		//stores the width and height of the texture 1:1 scale in the render rect
		SDL_QueryTexture(renderResource->mTexture, NULL, NULL, &renderRect.w, &renderRect.h);
		//initialize values
		posX = 0.0;
		posY = 0.0;
		rotation = 0.0;
		//anchor point 0,0 = top left corner,1,1 = bottom right corner 
		anchor = { 0.5,0.5 };
		flipH = false;
		flipV = false;
		visible = true;
		layer = 1;
		if (colorKeyEnabled){
			//generate the color key
			//TODO: commented out colorkey stuff. We're using PNG's with transparency, so no need for colorkey at the moment

			/*Uint32 colorkey = SDL_MapRGB(renderResource->mTexture->format, colorKey.r, colorKey.g, colorKey.b);
			SDL_SetColorKey(renderResource->mTexture, SDL_TRUE, colorkey);

			SDL_SetColorKey(renderResource->mTexture, SDL_TRUE, colorkey);*/
		}
	}
}

bool operator<(const SDLRenderObject& lhs, const SDLRenderObject& rhs){
	std::cout << "hi" << std::endl;
	return lhs.layer < rhs.layer;
}
void SDLRenderObject::setColorKey(unsigned int r, unsigned int g, unsigned int b){
	colorKey.r = r;
	colorKey.g = g;
	colorKey.b = b;
	//Uint32 color = SDL_MapRGB(renderResource->mSurface->format, colorKey.r, colorKey.g, colorKey.b);
	//SDL_SetColorKey(renderResource->mSurface, SDL_TRUE, color); //SDL_TRUE might need to be SDL_SRCCOLORKEY
}

//TODO: These are for when we make position, rotation, etc. private attibutes and need to change them
/*SDL_Rect* SDLRenderObject::getRenderRect(){return &renderRect;}
void SDLRenderObject::setRenderRect(SDL_Rect rect){renderRect = rect;}
void SDLRenderObject::resetRenderRect(){
	SDL_QueryTexture(renderResource->mTexture, NULL, NULL, &renderRect.w, &renderRect.h);
}
SDL_Point SDLRenderObject::getPosition(){
	SDL_Point pos;
	//conversion floors numbers, but it shouldn't really matter for what we're doing
	pos.x = int(posX);
	pos.y = int(posY);
	return pos;
}
void SDLRenderObject::setPosition(SDL_Point point){
	posX = point.x;
	posY = point.y;
}
float SDLRenderObject::getRotation(){ return rotation;}
void SDLRenderObject::setRotation(float degrees){
	rotation = degrees;
}
bool SDLRenderObject::getVisibility(){ return visible; }
void SDLRenderObject::setVisibility(bool flag){ visible = flag; }/**/