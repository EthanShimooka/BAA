#pragma once
#ifndef FEATHERPHYSICSCOMPONENT_H_INCLUDED
#define FEATHERPHYSICSCOMPONENT_H_INCLUDED
#include "PhysicsComponent.h"


class FeatherPhysicsComponent : public PhysicsComponent
{
public:
	/// Constructor
	FeatherPhysicsComponent();
	/// Destructor
	~FeatherPhysicsComponent();
	/// Update
	void Update();

};

#endif