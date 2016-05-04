#pragma once
#ifndef  BOOMERANGPHYSICSCOMPONENT_H_INCLUDED
#define  BOOMERANGPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
class BoomerangPhysicsComponent :
	public PhysicsComponent
{
public:
	BoomerangPhysicsComponent(GameObject* boomerang, int destX, int destY);
	~BoomerangPhysicsComponent();
};

#endif