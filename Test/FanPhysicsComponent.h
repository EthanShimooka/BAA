#pragma once
#ifndef FANPHYSICSCOMPONENT_H_INCLUDED
#define FANPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "FanComponentIncludes.h"
class FanPhysicsComponent :	public PhysicsComponent
{
public:
	FanPhysicsComponent(GameObject* player);
	~FanPhysicsComponent();
	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
	b2Vec2 forceVec;
	float forceStrength;
};


#endif