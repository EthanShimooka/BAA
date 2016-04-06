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
#include "include\InputManager.h"

#include "PowerShieldObjectFactory.h"

class PlayerLogicComponent :  public LogicComponent
{
public:
	/// Constructor
	PlayerLogicComponent(GameObject* player);
	/// Destructor
	~PlayerLogicComponent();
	/// Update Function
	void Update();
	/// Spawn Feather Function
	uint64_t spawnFeather(int mouseX, int mouseY, float chargeTime);
	/// Spawn Feather (networked)
	void spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY, float chargeTime);
	/// Spawn Hero Class Power
	void spawnShield();

	/// Shield Object Factory. Will need to be changed eventually
	/// And migrated to maybe class specific logic class?
	PowerShieldObjectFactory sFactory;

	FeatherObjectFactory fFactory;
	uint64_t featherNum = 0;

	int currBirdseed=1;
	int maxsBirdseed=5;
	SDLRenderObject* birdseedHUD;
	SDL_Rect defaultRect;
};

#endif