#pragma once
#ifndef FANPHYSICSCOMPONENT_H_INCLUDED
#define FANPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "FanComponentIncludes.h"
#include <math.h>
class FanPhysicsComponent :	public PhysicsComponent
{
public:
	FanPhysicsComponent(GameObject* player, double rotation);
	~FanPhysicsComponent();
	/// Update
	void Update();
	void init(double rotation);
	void handleCollision(GameObject* otherObj);
	b2Vec2 forceVec;
	float forceStrength;
};


#endif