/**
*  PowerShieldPhysicsComponent.h
*  Authors: Ethan Shimooka
*  Date 3/4/2016
*  Description :
    Physics Component for Class Object "Shield".

*/

#ifndef POWERSHIELDPHYSICSCOMPONENTCOMPONENT_H_INCLUDED
#define POWERSHIELDPHYSICSCOMPONENTCOMPONENT_H_INCLUDED

#pragma once
#include "LogicComponent.h"
#include "PowerShieldIncludes.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

class PowerShieldPhysicsComponent : public PhysicsComponent
{
public:
	/// Constructor
	PowerShieldPhysicsComponent(GameObject* shield);
	/// Deconstructor
	~PowerShieldPhysicsComponent();
	/// update function
	void Update();

	void init();

	void handleCollision(GameObject* otherObj);
};

#endif