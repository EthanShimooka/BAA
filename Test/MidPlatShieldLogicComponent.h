/**
*  MidPlatShieldLogicComponent.h
*  Authors: Ethan Shimooka
*  Date 3/31/2016
*  Description :
Logic Component class for the midPlatform Shield

*/

#pragma once
#ifndef MIDPLATSHIELDLOGICCOMPONENT_H_INCLUDED
#define MIDPLATSHIELDLOGICCOMPONENT_H_INCLUDED

#include "PhysicsComponent.h"
#include "MidPlatShieldComponentIncludes.h"


#include "LogicComponent.h"
class MidPlatShieldLogicComponent :
	public LogicComponent
{
public:
	MidPlatShieldLogicComponent(GameObject * shield);
	~MidPlatShieldLogicComponent();

	GameObject* spawner;
	bool shieldtoggle = false;

	clock_t timeSinceToggle;


	/// called from MidPlatShieldPhysicsComponent
	void toggleShield();
	/// Resets Shield Button
	void resetShield();
	/// Update function
	void Update();


};

#endif