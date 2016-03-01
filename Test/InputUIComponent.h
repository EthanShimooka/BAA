/**
*  InputUIComponent.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	InputUIComponent represents the abstreact base class from which all other UI
	input Components are derived.

	Only the local player GameObject should have this component.

*/


#pragma once
#ifndef INPUTUICOMPONENT_H_INCLUDED
#define INPUTUICOMPONENT_H_INCLUDED


#include "Component.h"
#include "include\InputManager.h"
#include "UIObject.h"

class InputUIComponent : public Component
{
public:
	/// Constructor
	InputUIComponent();
	/// Destructor
	~InputUIComponent();
	/// GameObject Container Refrence. (Assigned upon GameObject Creation) 

	/// UIObject Container Reference.
	UIObject* uiObjectRef;

	/// update object Positions from Input
	virtual void Update();
};

#endif