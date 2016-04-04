/**
*  PhysicsComponent.h
*  Authors: Ethan Shimooka
*  Date 2/26/2016
*  Description :
	ThePhysicsComponent class is the abstract class for GameObjects who posess rigidbodies and 
	react with world gravity. The gravity might need to go into a seperate component. Be sure
	to use the refrence to the GameObject, as that is where the Xpos and Ypos coordinates are.

*/

#pragma once
#ifndef PHYSICSCOMPONENT_H_INCLUDED
#define PHYSICSCOMPONENT_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
#include "include\box2D\Box2D.h"
#include "GameWorld.h"
#include <vector>

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	/// GameObject Container Reference
	GameObject* gameObjectRef;
	b2Body* mBody;
	b2Fixture* mFixture;
	b2FixtureDef boxFixtureDef;

	/// Virtual Update function
	virtual void Update();
	virtual void handleCollision(GameObject* otherObj);
	void setCollisionFilter(uint16 categoryBits, uint16 mask);
};

enum CollisionMasks {
	COLLISION_PLAYER = 0x0001,
	COLLISION_MINION = 0x0002,
	COLLISION_PLATFORM = 0x0004,
	COLLISION_SWTICH = 0x0008,
	COLLISION_FEATHER = 0x0010,
	COLLISION_ALL = 0xFFFF
	//we can keep on adding more as needed
};

#endif