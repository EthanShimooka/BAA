#pragma once

#ifndef BUTTONOBJECTFACTORY_H_INCLUDED
#define BUTTONOBJECTFACTORY_H_INCLUDED

#include "GameObjectFactory.h"
#include "ButtonComponentIncludes.h"

typedef enum{
	BUTTON_NONE = -1,
	BUTTON_PLAY = 0,
	BUTTON_READY = 1,
	BUTTON_BACK = 2,
	BUTTON_MENU = 3,
	BUTTON_QUIT = 4,
	BUTTON_ICON = 5
}BUTTONS;

class ButtonObjectFactory :
	public GameObjectFactory
{
public:
	ButtonObjectFactory();
	~ButtonObjectFactory();

	//GameObject* Spawn(uint64_t PID, float posX, float posY, int imageID, float width = 100.0f, float height = 50.0f, float scale = 1.0f);
	GameObject* Spawn(uint64_t PID, float posX, float posY, int imageID, float width = 100.0f, float height = 50.0f, float scale = 1.0f, int type=-1);
};

#endif