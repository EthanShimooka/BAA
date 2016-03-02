/**
*  PlayerLogicComponent.h
*  Authors: Ethan Shimooka
*  Date 2/26/2016
*  Description :
InputComponent represents the abstreact base class from which all other
imput Components are derived.

Only the local player GameObject should have this component.

*/
#pragma once
#ifndef PLAYERLOGICCOMPONENT_H_INCLUDED
#define PLAYERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "SystemGameObjectQueue.h"
#include "FeatherObjectFactory.h"
#include "PlayerComponentIncludes.h"


class PlayerLogicComponent :  public LogicComponent
{
public:
	/// Constructor
	PlayerLogicComponent();
	/// Destructor
	~PlayerLogicComponent();
	/// Update Function
	void Update();

	void spawnFeather(int mouseX, int mouseY);
	void spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY);

	FeatherObjectFactory fFactory;
	int featherNum = 0;
};

#endif