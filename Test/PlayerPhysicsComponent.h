#pragma once
#ifndef PLAYERPHYSICSCOMPONENT_H_INCLUDED
#define PLAYERPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "PlayerComponentIncludes.h"
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	/// Constructor
	PlayerPhysicsComponent();
	/// Destructor
	~PlayerPhysicsComponent();
	/// Update
	void Update();

};

#endif