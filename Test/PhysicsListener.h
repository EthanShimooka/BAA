#pragma once
#ifndef PHYSICSLISTENER_H_INCLUDED
#define PHYSICSLISTENER_H_INCLUDED

#include "include\Box2D\Box2D.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include <iostream>

class PhysicsListener: public b2ContactListener{
public:
	PhysicsListener();
	~PhysicsListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	void PreSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif