#pragma once
#ifndef FEATHEROBJECTFACTORY_H_INCLUDED
#define FEATHEROBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "FeatherComponentIncludes.h"




class FeatherObjectFactory : public GameObjectFactory
{
public:
	/// Constructor
	FeatherObjectFactory();
	/// Destructor
	~FeatherObjectFactory();

	/// Creates a new feather GameObject
	GameObject * Spawn(GameObject* owner, uint64_t PID, float posX, float posY, float dx, float dy, float chargeTime, float speed);
};

#endif