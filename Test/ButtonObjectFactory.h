#pragma once

#ifndef BUTTONOBJECTFACTORY_H_INCLUDED
#define BUTTONOBJECTFACTORY_H_INCLUDED

#include "GameObjectFactory.h"
#include "ButtonComponentIncludes.h"


class ButtonObjectFactory :
	public GameObjectFactory
{
public:
	ButtonObjectFactory();
	~ButtonObjectFactory();

	GameObject* Spawn(uint64_t PID, float posX, float posY, int imageID, float width = 100.0f, float height = 50.0f);
};

typedef enum {
	_PLAY_BUTTON = 1,
	_CANCEL_BUTTON = 2,
	_BACK_BUTTON = 3,
	_JOIN_BUTTON = 4,
	_INVITE_BUTTON = 5,
	_TIMER = 6,
	_MENU_NAME = 7,
	_OPTIONS_BUTTON = 8,
	_READY_BUTTON = 9,
	_PLAYER_SLOT = 10,
	_CHICKEN = 3000,
	_PEACOCK = 3100,
	_FLAMINGO = 3200,
	_QUAIL = 3300,
	_TURKEY = 3500,
	_EAGLE = 0,
	_BIRDSEED_SHELL = 12,
	_BIRDSEED_BAR = 13,
	_CROSSHAIR = 14,
	_CHARGE_SHELL = 15,
	_CHARGE_BAR = 16,
	_LOBBY_TIMER = 17,
	_KILL_NOTIFICATION = 18,
}BUTTON_TYPE;

#endif