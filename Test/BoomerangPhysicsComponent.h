#pragma once
#ifndef  BOOMERANGPHYSICSCOMPONENT_H_INCLUDED
#define  BOOMERANGPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "PlayerPhysicsComponent.h"

class BoomerangPhysicsComponent :
	public PhysicsComponent
{
public:
	BoomerangPhysicsComponent(GameObject* boomerang, GameObject* owner, int destX, int destY);
	~BoomerangPhysicsComponent();
	void handleCollision(GameObject* otherObj);
	void Update();
	void init();
	
	GameObject* owner;
	PlayerPhysicsComponent* ownerPhysics;
	b2Vec2 targetDest;
	bool returning = false;
};

#endif