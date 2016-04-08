#pragma once
#include "include\RenderManager.h"


SDLRenderObject::SDLRenderObject(){
	//initialize values
	posX = 0.0f;
	posY = 0.0f;
	width = 1.0f;
	height = 1.0f;
	rotation = 0.0;
	//anchor point 0,0 = top left corner,1,1 = bottom right corner 
	anchor = { 0.5, 0.5 };
	flipH = false;
	flipV = false;
	visible = true;
	ifRenderImage = false;
	ifRenderRect = false;
	parent = NULL;
}
//SDLRenderObject::~SDLRenderObject(){}


void SDLRenderObject::setResourceObject(RenderResource *source){
	if (source){
		renderResource = source;
		frameWidth = source->width;
		frameHeight = source->height;
		frameTotal = (frameTotal > frameWidth*frameHeight || frameTotal >= 0) ? frameWidth*frameHeight : source->max;
		ifRenderImage = true;
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

bool operator<(const SDLRenderObject& lhs, const SDLRenderObject& rhs){
	return lhs.posZ < rhs.posZ;

}

void SDLRenderObject::setParent(SDLRenderObject * par){
	if (par != this){
		parent = par;
	}
}

float SDLRenderObject::getPosX(){ 
	if (parent){
		float flipH = (parent->isFlippedH()) ? -1.0f : 1.0f;
		float flipV = (parent->isFlippedV()) ? -1.0f : 1.0f;
		float x = posX;
		float y = posY;
		float r = parent->getRotation()*flipH*flipV * (float)(M_PI / 180);
		float sx = parent->getScaleX();
		float sy = parent->getScaleY();
		return parent->getPosX() + (sx*cos(r)*x - sy*sin(r)*y)*flipH;
	}
	return posX; 
}
float SDLRenderObject::getPosY(){
	if (parent){
		float flipH = (parent->isFlippedH()) ? -1.0f : 1.0f;
		float flipV = (parent->isFlippedV()) ? -1.0f : 1.0f;
		float x =  posX;
		float y =  posY;
		float r = parent->getRotation()*flipH*flipV * (float)(M_PI / 180);
		float sx = parent->getScaleX();
		float sy = parent->getScaleY();
		return parent->getPosY() + (sx*sin(r)*x + sy*cos(r)*y)*flipV;
	}
	return posY;
}
float SDLRenderObject::getPosZ(){
	return posZ;
}
void SDLRenderObject::getPos(float &x, float &y){x = getPosX(); y = getPosY(); }
void SDLRenderObject::setPosZ(float z){ posZ = z; }
void SDLRenderObject::setPos(float x, float y){ posX = x; posY = y; }
void SDLRenderObject::setPos(float x, float y, float z){ posX = x; posY = y; posZ = z; }


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
float SDLRenderObject::calcXScale(float w){
	return w * frameWidth / renderRect.w;
}
float SDLRenderObject::calcYScale(float h){
	return h * frameHeight / renderRect.h;
}
void SDLRenderObject::calcScale(float w, float h){
	setScale(calcXScale(w), calcYScale(h));
}
int SDLRenderObject::getWidth(){
	return (frameWidth>0) ? (int)(renderRect.w*getScaleX() / frameWidth) :(int) (renderRect.w*getScaleX());
}
int SDLRenderObject::getHeight(){
	return (frameHeight>0) ? (int) (renderRect.h*getScaleY() / frameHeight) : (int) (renderRect.h*getScaleY());
}
void SDLRenderObject::getSize(int &w, int &h){w = getWidth(); h = getHeight();}

void SDLRenderObject::setRenderRect(SDL_Rect rect){ renderRect = rect; }

void SDLRenderObject::setRenderRect(int width,int height){ 
	renderRect = { 0, 0, width, height };
}

bool SDLRenderObject::isVisible(){ 
	if (parent){
		return (parent->isVisible() && visible);
	}
	return visible;
}
void SDLRenderObject::setVisible(bool flag){ visible = flag; }
void SDLRenderObject::toggleVisible(){ visible = !visible; }
void SDLRenderObject::setIfRenderRect(bool flag){ ifRenderRect = flag; }
void SDLRenderObject::toggleIfRenderRect(){ ifRenderRect = !ifRenderRect; }
void SDLRenderObject::setIfRenderImage(bool flag){ ifRenderImage = flag; }
void SDLRenderObject::toggleIfRenderImage(){ ifRenderImage = !ifRenderImage; }
void SDLRenderObject::setIfRenderText(bool flag){ ifRenderText = flag; }
void SDLRenderObject::setIfRenderText(bool flag, char* tex){ ifRenderText = flag; text = tex; }
void SDLRenderObject::toggleIfRenderText(){ ifRenderText = !ifRenderText; }
void SDLRenderObject::setText(char* tex) { text = tex; }

float SDLRenderObject::getRotation(){
	if (parent){
		bool h = isFlippedH(), v = isFlippedV();
		float flip = ((h || v) && !(h && v)) ? -1.0f : 1.0f;
		return (float) (rotation * flip + parent->getRotation());
	}
	return (float) rotation; 
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
void SDLRenderObject::toggleFlippedH(){ flipH = !flipH; }
void SDLRenderObject::toggleFlippedV(){ flipV = !flipV; }

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
void SDLRenderObject::setAnchor(double a, double b){ anchor.x = (float) a; anchor.y = (float) b; }
/*void SDLRenderObject::setAnchor(int x, int y){ 
	anchor.x = anchor.x + (x-posX)/renderRect.w; 
	anchor.y = anchor.y + (y-posY)/renderRect.h; 
}*/
void SDLRenderObject::unrender(){
	renderResource->mTexture = nullptr;
}

unsigned int SDLRenderObject::getCurrentFrame(){
	return frameCurrent;
}
void SDLRenderObject::setCurrentFrame(unsigned int f){
	frameCurrent = (f>=frameTotal) ? 0 : f;
}
SDL_Rect SDLRenderObject::getRenderRect(){
	SDL_Rect rect;
	rect.w =  renderRect.w / frameWidth;
	rect.h =  renderRect.h / frameHeight;
	rect.x = renderRect.x + (frameCurrent%frameWidth)*rect.w;
	rect.y = renderRect.y + (float)(roundf(frameCurrent / frameWidth)*rect.h);
	return rect;
}


void SDLRenderObject::setFrames(unsigned int w, unsigned int h, unsigned int totalFrames){
	frameWidth = w;
	frameHeight = h;
	frameTotal = (frameTotal > frameWidth*frameHeight || frameTotal >= 0) ? frameWidth*frameHeight : totalFrames;
}