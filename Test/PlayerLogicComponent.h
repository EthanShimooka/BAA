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
	uint64_t spawnFeather(int mouseX, int mouseY, float chargeTime, float speed);
	/// Spawn Feather (networked)
	void spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY, float speed);
	/// Spawn Hero Class Power
	void spawnShield();
	/// When the player is hit by a feather, turn into an egg and roll back to base.
	/// This function reaches into each component and makes appropriate changes to
	/// turn the player into an egg
	void becomeEgg();
	/// Once the player has rolled back to base and enough time has elapsed,
	/// turn the player back into a bird and re-init stuff
	void hatchBird();
	/// Start charge and end charge are called to change the value charging
	/// in order to update charge bar appropriately
	void startCharge();
	void endCharge();
	/// Shield Object Factory. Will need to be changed eventually
	/// And migrated to maybe class specific logic class?
	PowerShieldObjectFactory sFactory;

	FeatherObjectFactory fFactory;
	uint64_t featherNum = 0;

	int currBirdseed=0;
	int maxsBirdseed=5;

	bool charging = false;
	float currChargePercentage = 0;

	SDLRenderObject* birdseedHUD;
	SDLRenderObject* chargeHUD;
	SDL_Rect defaultRect;
	SDL_Rect chargeRect;

	SDLRenderObject* timerHUD;

	/// Boolean used to restrict input during gameplay. Only perform actions
	/// (i.e. jumping, shooting, moving) in game if true.
	bool isEgg = false;
};

#endif