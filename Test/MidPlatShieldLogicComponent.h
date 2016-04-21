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
	MidPlatShieldLogicComponent();
	~MidPlatShieldLogicComponent();
	void ToggleShield();

};

#endif