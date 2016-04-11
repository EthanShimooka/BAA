#pragma once
#include "PhysicsComponent.h"
class MidPlatPhysicsComponent :
	public PhysicsComponent
{
public:
	MidPlatPhysicsComponent(GameObject* platform);
	~MidPlatPhysicsComponent();

	void init();
	void Update();
};

