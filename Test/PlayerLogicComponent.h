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


class PlayerLogicComponent :  public LogicComponent
{
public:
	/// Constructor
	PlayerLogicComponent(GameObject* player);
	/// Destructor
	~PlayerLogicComponent();
	/// Update Function
	void Update();

	uint64_t spawnFeather(int mouseX, int mouseY);
	void spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY);

	
	FeatherObjectFactory fFactory;
	uint64_t featherNum = 0;

	bool isChargingAttack = false;
	
	bool playerAlive = true; // set to false when player disabled
	int birdseed = 0; // counter for birdseed, max is 6
	int health = 5; // hardcoded value, needs to be initialized based on class later
	int skillReady = 3; // hardcoded value, initialize later based on class
	
	// 
	void takeDamage(int damage);
};

#endif