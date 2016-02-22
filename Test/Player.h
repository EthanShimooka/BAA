#pragma once
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "include\box2D\Box2D.h"
#include "include\network\NetIncludes.h"
#include "include\SDLRenderObject.h"
#include "GameObject.h"


class Player: public GameObject{
public:
	int ID;
	float posX;
	float posY;
	float rotation;
	bool flipH;
	bool flipV;
	bool visible;
	bool isNetworkControlled;
	SDLRenderObject* objRef;
	b2Body* body;
	void updateRef();
	void updatePlayerFromNetwork();
	void updatePlayerFromInput();
	void sendPlayerDataToNetwork();
	void updatePhysics();

	Player();
	Player(int playerID, int x, int y);
	Player(SDLRenderObject* obj);
	void update();
};

#endif