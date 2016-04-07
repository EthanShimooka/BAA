#pragma once

#ifndef PLAYERPHYSICSCOMPONENT_H_INCLUDED
#define PLAYERPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "PlayerComponentIncludes.h"

class PlayerPhysicsComponent : public PhysicsComponent {
public:
	/// Constructor
	PlayerPhysicsComponent(GameObject* player, float height, float width);
	/// Destructor
	~PlayerPhysicsComponent();
	/// Update
	void Update();
	void init(float height, float width);
	void handleCollision(GameObject* otherObj);
};

#endif