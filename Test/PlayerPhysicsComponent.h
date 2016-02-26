#pragma once
#include "PhysicsComponent.h"
class PlayerPhysicsComponent :
	public PhysicsComponent
{
public:
	PlayerPhysicsComponent();
	~PlayerPhysicsComponent();

	void Update();

};

