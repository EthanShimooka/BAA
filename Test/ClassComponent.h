/**
*  ClassComponent.h
*  Authors: Ethan Shimooka
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
///#include "include\network\MemoryBitStream.h"
#include "GameObject.h"

class ClassComponent :
	public Component
{
public:
	/// Constructor
	ClassComponent();
	/// Destructor
	~ClassComponent();

	/// GameObject Container Refrence. (Assigned upon GameObject Creation) 
	GameObject* gameObjectRef;

	/// update object Positions from Input
	virtual void Update();
	/// returns true if the ability was used, else returns false
	//virtual bool UseAbility();

	float speed;
	float width, height;
	int   seedAmount;
	float featherSpeed;
	float featherWidth, featherHeight;
	float abilityCooldown;
};

#endif