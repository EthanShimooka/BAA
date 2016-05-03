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
	MinionPhysicsComponent(GameObject* minion, float _initialX, float _initialY, int team);
	/// Destructor
	~MinionPhysicsComponent();

	/// Remove minion after being hit enemy with feather
	void DestroyMinion();

	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
	void endCollision(GameObject* otherObj);
	bool isGettingBlown = false;
	b2Vec2 blownForce;

	bool uhh = false; //get rid of this
	float savedYForce;
};

#endif