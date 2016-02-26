/**
*  InputComponet.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	InputComponent represents the abstreact base class from which all other
	imput Components are derived. 

	Only the local player GameObject should have this component.

*/


#pragma once
#ifndef INPUTCOMPONENT_H_INCLUDED
#define INPUTCOMPONENT_H_INCLUDED


#include "Component.h"
#include "MovementComponent.h"
#include "include\InputManager.h"
#include "GameObject.h"

class InputComponent : public Component
{
public:
	/// Constructor
	InputComponent();
	/// Destructor
	~InputComponent();
	/// GameObject Container Refrence. (Assigned upon GameObject Creation) 
	GameObject* gameObjectRef;

	/// update object Positions from Input
	void Update();
};

#endif