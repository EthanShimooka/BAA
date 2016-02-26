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
	InputComponent();
	~InputComponent();

	GameObject* gameObjectRef;

	/// update object Positions from Input
	void Update();
};

#endif