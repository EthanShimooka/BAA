#pragma once
#ifndef FANOBJECTFACTORY_H_INCLUDED
#define FANOBJECTFACTORY_H_INCLUDED

// Component Includes
#include "FanComponentIncludes.h"

#include "Component.h"
#include "GameObject.h"
#include "GameObjectFactory.h"



class FanObjectFactory : public GameObjectFactory
{

private:
protected:
public:
	/// Constructor
	FanObjectFactory();
	/// Destructor
	~FanObjectFactory();
	/// Spawn Function
	GameObject* Spawn(uint64_t PID, float posX, float posY, float forceX, float forceY, double rotation);

};

#endif