#pragma once
#include "include\RenderManager.h"


SDLRenderObject::SDLRenderObject(){
	//initialize values
	posX = 0.0;
	posY = 0.0;
	width = 1.0;
	height = 1.0;
	rotation = 0.0;
	//anchor point 0,0 = top left corner,1,1 = bottom right corner 
	anchor = { 0.5, 0.5 };
	flipH = false;
	flipV = false;
	visible = true;
	parent = NULL;
}
//SDLRenderObject::~SDLRenderObject(){}


void SDLRenderObject::setResourceObject(RenderResource *source){
	if (source){
		renderResource = source;
		//by default, the texture sizes are stored 1:1 scale
		//stores the width and height of the texture 1:1 scale in the render rect
		SDL_QueryTexture(renderResource->mTexture, NULL, NULL, &renderRect.w, &renderRect.h);
		height = renderRect.h;
		width = renderRect.w;
		if (colorKeyEnabled){
			//generate the color key
			//TODO: commented out colorkey stuff. We're using PNG's with transparency, so no need for colorkey at the moment
			/*Uint32 colorkey = SDL_MapRGB(renderResource->mTexture->format, colorKey.r, colorKey.g, colorKey.b);
			SDL_SetColorKey(renderResource->mTexture, SDL_TRUE, colorkey);
			SDL_SetColorKey(renderResource->mTexture, SDL_TRUE, colorkey);*/
		}
	}
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
*/


void SDLRenderObject::setParent(SDLRenderObject * par){
	parent = par;
}

float SDLRenderObject::getPosX(){ 
	if (parent){
		return parent->getPosX() + posX;
	}
	return posX; 
}
float SDLRenderObject::getPosY(){ 
	if (parent){
		return parent->getPosY() + posY;
	}
	return posY;
}
void SDLRenderObject::getPos(float &x, float &y){x = getPosX(); y = getPosY(); }
void SDLRenderObject::setPos(float x, float y){ posX = x; posY = y; }


int SDLRenderObject::getWidth(){
	return renderRect.w;
}
int SDLRenderObject::getHeight(){
	return renderRect.h;
}
void SDLRenderObject::getSize(int &w, int &h){w = getWidth(); h = getHeight();}
void SDLRenderObject::setSize(int w, int h){ width = w, height = h; }

void SDLRenderObject::setRenderRect(SDL_Rect rect){ renderRect = rect; }

bool SDLRenderObject::isVisible(){ 
	if (parent){
		return (parent->isVisible() && visible);
	}
	return visible;
}
void SDLRenderObject::setVisible(bool flag){ visible = flag; }

float SDLRenderObject::getRotation(){ return rotation; }
void SDLRenderObject::setRotation(float degrees){ rotation = degrees; }

bool SDLRenderObject::isFlippedH(){ return flipH; }
bool SDLRenderObject::isFlippedV(){ return flipV; }
void SDLRenderObject::setFlippedH(bool flag){ flipH = flag; }
void SDLRenderObject::setFlippedV(bool flag){ flipV = flag; }

float SDLRenderObject::getAnchorX(){ return anchor.x; }
float SDLRenderObject::getAnchorY(){ return anchor.y; }

void SDLRenderObject::getAnchor(float &a, float &b){ a = getAnchorX(); b = getAnchorY(); }
void SDLRenderObject::setAnchor(float a, float b){ anchor.x = a; anchor.y = b; }
void SDLRenderObject::setAnchor(int x, int y){ 
	anchor.x = anchor.x + (x-posX)/renderRect.w; 
	anchor.y = anchor.y + (y-posY)/renderRect.h; 
}
