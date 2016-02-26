#pragma once
#ifndef MOVEMENTCOMPONENT_H_INCLUDED
#define MOVEMENTCOMPONENT_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
class MovementComponent : public Component
{
public:
	MovementComponent();
	~MovementComponent();

	GameObject* gameObjectRef;

	/// Update Function
	void Update();
	/// Manual Position Accessor
	void SetPos(float x, float y);
};

#endif