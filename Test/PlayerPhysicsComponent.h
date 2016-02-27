#pragma once
#ifndef PLAYERPHYSICSCOMPONENT_H_INCLUDED
#define PLAYERPPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	PlayerPhysicsComponent();
	~PlayerPhysicsComponent();

	void Update();

};

#endif