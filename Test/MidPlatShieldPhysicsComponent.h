/**
*  MidPlatShieldPhysicsComponent.h
*  Authors: Ethan Shimooka
*  Date 3/31/2016
*  Description :
Render Component class for the midPlatform

*/

#pragma once
#ifndef MIDPLATSHIELDPHYSICSCOMPONENT_H_INCLUDED
#define MIDPLATSHIELDPHYSICSCOMPONENT_H_INCLUDED

#include "PhysicsComponent.h"
#include "MidPlatShieldComponentIncludes.h"

class MidPlatShieldPhysicsComponent :
	public PhysicsComponent
{
public:
	/// Constructor
	MidPlatShieldPhysicsComponent(GameObject* platform);
	/// Destructor
	~MidPlatShieldPhysicsComponent();
	/// setup function
	void init();
	/// collision handling
	void handleCollision(GameObject* otherObj);
	/// Update
	void Update();

	void ShieldToggle();

};

#endif