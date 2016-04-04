#pragma once

#ifndef FEATHERPHYSICSCOMPONENT_H_INCLUDED
#define FEATHERPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "FeatherComponentIncludes.h"

class FeatherPhysicsComponent : public PhysicsComponent
{
public:
	/// Constructor
	FeatherPhysicsComponent(GameObject* feather, float initX, float initY, float dx, float dy, float chargeTime);
	/// Destructor
	~FeatherPhysicsComponent();
	/// Update
	void Update();
	void handleCollision(GameObject* otherObj);
	void init(float initX, float initY, float dx, float dy, float chargeTime);

};

#endif