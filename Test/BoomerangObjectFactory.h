#pragma once
#ifndef BOOMERANGOBJECTFACTORY_H_INCLUDED
#define BOOMERANGBJECTFACTORY_H_INCLUDED

// Component Includes
#include "BoomerangComponentIncludes.h"

#include "Component.h"
#include "GameObject.h"
#include "GameObjectFactory.h"



class BoomerangObjectFactory : public GameObjectFactory
{

private:
protected:
public:
	/// Constructor
	BoomerangObjectFactory();
	/// Destructor
	~BoomerangObjectFactory();
	/// Spawn Function
	GameObject* Spawn(uint64_t PID, float posX, float posY, float destX, float destY, int _team);

};

#endif