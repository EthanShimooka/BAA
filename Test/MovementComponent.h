#pragma once
#ifndef MOVEMENTCOMPONENT_H_INCLUDED
#define MOVEMENTCOMPONENT_H_INCLUDED

#include "Component.h"
class MovementComponent : public Component
{
public:
	MovementComponent();
	~MovementComponent();

	/// World Realtive X position
	float posX;
	/// World Realtive Y position
	float posY;
	/// World Rotation
	float rotation;

	/// Update Function
	void Update();
	/// Manual Position Accessor
	void SetPos(float x, float y);
};

#endif