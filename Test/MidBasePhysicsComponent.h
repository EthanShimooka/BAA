#pragma once

#ifndef MIDBASEPHYSICSCOMPONENT_H_INCLUDED
#define MIDBASEPHYSICSCOMPONENT_H_INCLUDED


#include "PhysicsComponent.h"


class MidBasePhysicsComponent :
	public PhysicsComponent
{
public:
	MidBasePhysicsComponent(GameObject * base);
	~MidBasePhysicsComponent();

	void Init();
	void Update();

	
};

#endif