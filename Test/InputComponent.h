#pragma once
#ifndef INPUTCOMPONENT_H_INCLUDED
#define INPUTCOMPONENT_H_INCLUDED


#include "Component.h"
#include "MovementComponent.h"
#include "include\InputManager.h"

class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent();

	/// update object Positions from Input
	void Update(MovementComponent move);
};

#endif