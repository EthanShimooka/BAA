/**
*  MovementComponet.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	MovementComponent represents the abstreact base class from which all other
	movement Components are derived.

	To be perfectly honest, this component might be replaced, as it does not do anything
	in its current state. I had a hell of a time getting this thing working correctly,
	in tandam with the imput manger and it was a nightmare without a messaging system,
	so I just used a refrence pointer and called it a day. May become useful in the future.
*/

#pragma once
#ifndef MOVEMENTCOMPONENT_H_INCLUDED
#define MOVEMENTCOMPONENT_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
class MovementComponent : public Component
{
public:
	/// Constructor
	MovementComponent();
	/// Destructor
	virtual ~MovementComponent();
	/// GameObject Container Refrence. (Assigned upon GameObject Creation) 
	GameObject* gameObjectRef;

	/// Update Function
	virtual void Update();
	/// Manual Position Accessor
	void SetPos(float x, float y);
};

#endif