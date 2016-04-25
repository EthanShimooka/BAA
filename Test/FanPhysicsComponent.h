#pragma once
#ifndef FANPHYSICSCOMPONENT_H_INCLUDED
#define FANPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "FanComponentIncludes.h"
class FanPhysicsComponent :	public PhysicsComponent
{
public:
	FanPhysicsComponent(GameObject* player, float forceX, float forceY);
	~FanPhysicsComponent();
	/// Update
	void Update();
	void init(float forceX, float forceY);
	void handleCollision(GameObject* otherObj);
	b2Vec2 forceVec;
	float forceStrength;
};


#endif