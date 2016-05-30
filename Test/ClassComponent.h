/**
*  ClassComponent.h
*  Authors: Pourya Sohbati
*  Date 2/25/2016
*  Description :
Class Component represents the abstreact base class from which all other
Class Components are derived.


*/

#pragma once
#ifndef CLASSCOMPONENT_H_INCLUDED
#define CLASSCOMPONENT_H_INCLUDED


#include "Component.h"
///#include "MovementComponent.h"
///#include "include\InputManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "include\network\MemoryBitStream.h"
//#include "PlayerNetworkComponent.h"

//class PlayerNetworkComponent;

class ClassComponent :
	public Component
{
public:
	/// Constructor
	ClassComponent();
	/// Destructor
	virtual ~ClassComponent();

	/// GameObject Container Refrence. (Assigned upon GameObject Creation) 
	GameObject* gameObjectRef = nullptr;

	/// update object Positions from Input
	virtual void Update();

	
	//virtual void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	/// returns true if the ability was used, else returns false
	virtual int useAbility();
	virtual void writeNetAbility();
	virtual void readNetAbility(InputMemoryBitStream& aPacket);
	void setTimer();
	bool endTimer();

	virtual int getClass();
	/// Plays successful ability use sound
	void playAbilityUseSound();
	/// Plays the sound for when the birdseed meter first fills up
	void birdseedFullSFXPlayed();

	float speed = 16;
	float jumpSpeed = 16;
	float width = 1.33f;
	float height = 1.35f;
	int   seedRequired = 8;
	float featherSpeed = 70.0f;
	float featherWidth = 1;
	float featherHeight = 1;
	float abilityCooldown = 15;

	int currBirdseed = 0;
	int maxsBirdseed = 8;
	uint64_t *powerNum = 0;
	bool birdseedFullPlayed = false;

protected :
	float timer = 0;
	int timerLength = 0;
};

#endif