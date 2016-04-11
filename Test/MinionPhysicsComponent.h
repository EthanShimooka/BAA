#pragma once
#ifndef MINIONPHYSICSCOMPONENT_H_INCLUDED
#define MINIONPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "MinionComponentIncludes.h"
#include "MidBaseLogicComponent.h"

class MinionPhysicsComponent :
	public PhysicsComponent
{
public:
	/// Constructor
	MinionPhysicsComponent(GameObject* minion, float _initialX, float _initialY, float _length, bool _walkRight);
	/// Destructor
	~MinionPhysicsComponent();
	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
};

#endif