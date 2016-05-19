#pragma once
#ifndef MINEPHYSICSCOMPONENT_H_INCLUDED
#define MINEPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"
#include "MineComponentIncludes.h"
class MinePhysicsComponent :
	public PhysicsComponent
{
public:
	MinePhysicsComponent(GameObject* player);
	MinePhysicsComponent(GameObject* player, float height, float width);
	~MinePhysicsComponent();
	/// Update
	void Update();
	void init();
	void handleCollision(GameObject* otherObj);
	b2Vec2 targetPos;
};


#endif