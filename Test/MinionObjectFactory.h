#pragma once
#ifndef MINIONOBJECTFACTORY_H_INCLUDED
#define MINIONOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "MinionRenderComponent.h"
#include "MinionNetworkComponent.h"
#include "MinionLogicComponent.h"
#include "MinionPhysicsComponent.h"



class MinionObjectFactory : public GameObjectFactory
{
public:
	/// Constructor
	MinionObjectFactory();
	/// Destructor
	~MinionObjectFactory();

	/// Creates a new player GameObject
	GameObject * Spawn(uint64_t PID);

};

#endif