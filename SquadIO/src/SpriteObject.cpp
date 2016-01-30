#pragma once
#include "include\SpriteObject.h"

void SpriteObject::setFrameRect(unsigned int frameNum){
	unsigned int rowNum = (unsigned int)floor(frameNum / framesPerRow);
	unsigned int colNum = frameNum;

	if (rowNum > 0){
		colNum = frameNum - (rowNum*framesPerRow);
		renderRect.x = colNum*frameWidth;
		renderRect.y = rowNum*frameHeight;
		renderRect.w = frameWidth;
		renderRect.h = frameHeight;
	}

}
void SpriteObject::update(){
	//changes: linked winmm.lib, in same spot as SDL2.lib and SDL2main.lib ;
	//		   timeGetTime() returns DWORD, not float;
	//DWORD is an unsigned integer, it can hold enough milliseconds to fill up a month and a half
	//but +1 to the max value = 0, which we don't really have to worry about
	DWORD timeSinceLastFrame = timeGetTime() - timeLastFrame;
	if (timeSinceLastFrame >= spriteSpeed){
		currentFrame++;
		if (currentFrame >= totalFrames){
			currentFrame = startFrame;
		}
		//it can't find this function, so added empty function above
		setFrameRect(currentFrame);
		timeLastFrame = timeGetTime();
	}
}

void SpriteObject::play(){
	SDL_Surface *tempSurface = renderResource->mSurface;
	frameWidth = tempSurface->w / framesPerRow;
	frameHeight = tempSurface->h / framesPerColumn;
	currentFrame = startFrame;
	setFrameRect(currentFrame);
	timeLastFrame = timeGetTime();
}