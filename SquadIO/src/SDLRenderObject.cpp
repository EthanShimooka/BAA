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
	if (par != this){
		parent = par;
	}
}

float SDLRenderObject::getPosX(){ 
	if (parent){
		float flipH = (parent->isFlippedH()) ? -1 : 1;
		float flipV = (parent->isFlippedV()) ? -1 : 1;
		float x = posX;
		float y = posY;
		float r = parent->getRotation()*flipH*flipV * (M_PI / 180);
		float sx = parent->getScaleX();
		float sy = parent->getScaleY();
		return parent->getPosX() + (sx*cos(r)*x - sy*sin(r)*y)*flipH;
	}
	return posX; 
}
float SDLRenderObject::getPosY(){
	if (parent){
		float flipH = (parent->isFlippedH()) ? -1 : 1;
		float flipV = (parent->isFlippedV()) ? -1 : 1;
		float x =  posX;
		float y =  posY;
		float r = parent->getRotation()*flipH*flipV * (M_PI / 180);
		float sx = parent->getScaleX();
		float sy = parent->getScaleY();
		return parent->getPosY() + (sx*sin(r)*x + sy*cos(r)*y)*flipV;
	}
	return posY;
}
void SDLRenderObject::getPos(float &x, float &y){x = getPosX(); y = getPosY(); }
void SDLRenderObject::setPos(float x, float y){ posX = x; posY = y; }


float SDLRenderObject::getScaleX(){
	if (parent){
		//cout << parent->getScaleX() <<":"<< width << endl;
		return parent->getScaleX()*width;
	}
	return width;
}
float SDLRenderObject::getScaleY(){
	if (parent){
		return parent->getScaleY()*height;
	}
	return height;
}
void SDLRenderObject::setScaleX(float sx){
	width = sx;
}
void SDLRenderObject::setScaleY(float sy){
	height= sy;
}
void SDLRenderObject::setScale(float s){
	height = width = s;
}
void SDLRenderObject::setScale(float sx,float sy){
	height = sx;
	width = sy;
}
int SDLRenderObject::getWidth(){
	return renderRect.w*getScaleX();
}
int SDLRenderObject::getHeight(){
	return renderRect.h*getScaleY();
}
void SDLRenderObject::getSize(int &w, int &h){w = getWidth(); h = getHeight();}

void SDLRenderObject::setRenderRect(SDL_Rect rect){ renderRect = rect; }

bool SDLRenderObject::isVisible(){ 
	if (parent){
		return (parent->isVisible() && visible);
	}
	return visible;
}
void SDLRenderObject::setVisible(bool flag){ visible = flag; }

float SDLRenderObject::getRotation(){
	if (parent){
		bool h = isFlippedH(), v = isFlippedV();
		float flip = ((h || v) && !(h && v)) ? -1 : 1;
		return  rotation * flip + parent->getRotation();
	}
	return rotation; 
}
void SDLRenderObject::setRotation(float degrees){ rotation = degrees; }

bool SDLRenderObject::isFlippedH(){ 
	if (parent){
		return ((flipH || parent->isFlippedH()) && !(flipH && parent->isFlippedH()));
	}
	return flipH; 
}
bool SDLRenderObject::isFlippedV(){
	if (parent){
		return ((flipV || parent->isFlippedV()) && !(flipV && parent->isFlippedV()));
	}
	return flipV;
}
void SDLRenderObject::setFlippedH(bool flag){ flipH = flag; }
void SDLRenderObject::setFlippedV(bool flag){ flipV = flag; }

float SDLRenderObject::getAnchorX(){
	if (parent){
		return (isFlippedH()) ? (1 - anchor.x) : anchor.x;
	}
	return anchor.x;
}
float SDLRenderObject::getAnchorY(){
	if (parent){
		return (isFlippedV()) ? (1 - anchor.y) : anchor.y;
	}
	return anchor.y; 
}

void SDLRenderObject::getAnchor(float &a, float &b){ a = getAnchorX(); b = getAnchorY(); }
void SDLRenderObject::setAnchor(double a, double b){ anchor.x = a; anchor.y = b; }
void SDLRenderObject::setAnchor(int x, int y){ 
	anchor.x = anchor.x + (x-posX)/renderRect.w; 
	anchor.y = anchor.y + (y-posY)/renderRect.h; 
}
void SDLRenderObject::unrender(){
	renderResource->mTexture = nullptr;
}