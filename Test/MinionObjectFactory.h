#pragma once
#ifndef MINIONOBJECTFACTORY_H_INCLUDED
#define MINIONOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "MinionComponentIncludes.h"



class MinionObjectFactory : public GameObjectFactory
{
public:
	/// Constructor
	MinionObjectFactory();
	/// Destructor
	~MinionObjectFactory();

	/// Creates a new minion GameObject
	GameObject * Spawn(uint64_t PID, float posX, float posY, int team);

};

#endif