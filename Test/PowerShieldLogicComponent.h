/**
*  PowerShieldLogicComponent.h
*  Authors: Ethan Shimooka
*  Date 3/4/2016
*  Description :
	Logic Component for Class Object "Shield".

*/

#ifndef POWERSHIELDLOGICCOMPONENTCOMPONENT_H_INCLUDED
#define POWERSHIELDLOGICCOMPONENTCOMPONENT_H_INCLUDED

#pragma once
#include "LogicComponent.h"
#include "PowerShieldIncludes.h"
#include "GameObject.h"

class PowerShieldLogicComponent :
	public LogicComponent
{
public:
	/// Constructor
	PowerShieldLogicComponent(GameObject* shield);
	/// Destructor
	~PowerShieldLogicComponent();
	/// Update Function
	void Update();

	void spawnShield(int xpos, int ypos);

	void spawnShield(uint64_t ID, float initialX, float initialY, int destX, int destY);
	/// Plays the shield collision sfx
	void playShieldCollisionSFX();
	/// PowerShieldObjectFactory fFactory;
	/// uint64_t featherNum = 0;


};

#endif