#pragma once
#ifndef MINIONPHYSICSCOMPONENT_H_INCLUDED
#define MINIONPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"


class MinionPhysicsComponent :
	public PhysicsComponent
{
public:
	/// Constructor
	MinionPhysicsComponent();
	/// Destructor
	~MinionPhysicsComponent();
	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
};

#endif