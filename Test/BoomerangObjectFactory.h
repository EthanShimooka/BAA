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
	GameObject* Spawn(GameObject* owner, uint64_t PID, float destX, float destY);

};

#endif