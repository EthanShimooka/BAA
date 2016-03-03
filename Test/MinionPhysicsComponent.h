#pragma once
#ifndef MINIONPHYSICSCOMPONENT_H_INCLUDED
#define MINIONPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "MinionComponentIncludes.h"

class MinionPhysicsComponent :
	public PhysicsComponent
{
public:
	/// Constructor
	MinionPhysicsComponent(GameObject* minion);
	/// Destructor
	~MinionPhysicsComponent();
	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
};

#endif