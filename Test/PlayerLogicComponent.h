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
#include "MineObjectFactory.h"
#include "Invoke.h"

class PlayerLogicComponent :  public LogicComponent
{
private:
	static uint64_t childID;
public:
	/// Constructor
	PlayerLogicComponent(GameObject* player,int team);
	/// Destructor
	~PlayerLogicComponent();
	/// Update Function
	void Update();
	/// Spawn Feather Function
	uint64_t spawnFeather(float mouseX, float mouseY, float speed);
	/// Spawn Feather (networked)
	void spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY, float speed);
	float eggTimer;
	float lasttime;
	bool eggQueued;
	void queueEgg();
	/// When the player is hit by a feather, turn into an egg and roll back to base.
	/// This function reaches into each component and makes appropriate changes to
	/// turn the player into an egg
	void becomeEgg();
	/// Once the player has rolled back to base and enough time has elapsed,
	/// turn the player back into a bird and re-init stuff

	/// Triggers the appropriate death sfx
	void playDeathSFX(int playerClass, uint64_t deadPlayerID);
	/// Loops playing the footstep sfx
	void playFootstepSFX();
	/// Stops the footstep loop
	void stopFootstepSFX();
	/// triggered from physics componet to catapault player to middle of screen
	void launchPlayer();

	void hatchBird(bool respawn);
	/// Start charge and end charge are called to change the value charging
	/// in order to update charge bar appropriately
	void startCharge();
	void endCharge();
	/// Plays the sound to indicate feather cd not up or ability not ready
	void playFailSound();
	/// Returns the maximum birdseed for each individual class
	int getMaxBirdseedByClass(int playerClass);
	/// Shield Object Factory. Will need to be changed eventually
	/// And migrated to maybe class specific logic class?
	//PowerShieldObjectFactory sFactory;

	FeatherObjectFactory fFactory;

	// unique ID for any object that this player creates
	uint64_t child_id_counter;

	bool charging = false;
	bool launchable = false;
	bool launchableZone = false;
	bool isEgg = false;
	bool death = false;

	float currChargePercentage = 0;

};

#endif