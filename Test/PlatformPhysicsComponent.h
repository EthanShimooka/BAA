#pragma once
#ifndef PLATFORMPHYSICSCOMPONENT_H_INCLUDED
#define PLATFORMPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "PlatformComponentIncludes.h"


class PlatformPhysicsComponent : public PhysicsComponent
{
public:
	/// Constructor
	PlatformPhysicsComponent(GameObject* platform);
	/// Destructor
	~PlatformPhysicsComponent();
	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
};

#endif