#pragma once
#include "PhysicsComponent.h"
#ifndef MINEPHYSICSCOMPONENT_H_INCLUDED
#define MINEPHYSICSCOMPONENT_H_INCLUDED
class MinePhysicsComponent :
	public PhysicsComponent
{
public:
	MinePhysicsComponent(GameObject* player);
	MinePhysicsComponent(GameObject* player, float height, float width);
	~MinePhysicsComponent();
	/// Update
	void Update();
	void init(float height, float width);
	void handleCollision(GameObject* otherObj);
};


#endif