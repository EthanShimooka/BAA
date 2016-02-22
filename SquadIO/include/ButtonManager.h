#pragma once
#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#ifdef SQUADIO_EXPORTS
#define SQUADIO_API __declspec(dllexport) 
#else
#define SQUADIO_API __declspec(dllimport) 
#endif

#include <string>
#include "sdl2\SDL.h"
#include "sdl2\SDL_image.h"
#include "include\SceneManager.h"

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 1;

enum LButtonSprite{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 1
};

class LButton{
public:
	SQUADIO_API LButton();
	SQUADIO_API void setPosition(float x, float y);
	SQUADIO_API void handleEvent(SDL_Event* e);
	SQUADIO_API float getXPosition();
	SQUADIO_API float getYPosition();
	SDLRenderObject* obj;

private:
	float mPositionX;
	float mPositionY;
	LButtonSprite mCurrentSprite;
};

#endif