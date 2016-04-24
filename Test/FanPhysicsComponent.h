#pragma once
#include "PhysicsComponent.h"
class FanPhysicsComponent :
	public PhysicsComponent
{
public:
	FanPhysicsComponent();
	~FanPhysicsComponent();
};

#pragma once
#ifndef FANPHYSICSCOMPONENT_H_INCLUDED
#define FANPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "FanIncludes.h"
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
};


#endif