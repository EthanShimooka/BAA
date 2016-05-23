#pragma once
#ifndef PLATFORMOBJECTFACTORY_H_INCLUDED
#define PLATFORMOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "PlatformComponentIncludes.h"


class PlatformObjectFactory : public GameObjectFactory
{
public:
	/// Constructor
	PlatformObjectFactory();
	/// Destructor
	~PlatformObjectFactory();

	/// Creates a new minion GameObject
	GameObject * Spawn(uint64_t PID, float posX, float posY, int length);

};

#endif