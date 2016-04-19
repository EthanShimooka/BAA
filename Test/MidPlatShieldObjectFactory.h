#pragma once

#ifndef MIDPLATSHIELDOBJECTFACTORY_H_INCLUDED
#define MIDPLATSHIELDOBJECTFACTORY_H_INCLUDED

#include "GameObjectFactory.h"
#include "MidPlatShieldComponentIncludes.h"


class MidPlatShieldObjectFactory :
	public GameObjectFactory
{
public:
	MidPlatShieldObjectFactory();
	~MidPlatShieldObjectFactory();

	GameObject * Spawn(uint64_t PID, float posX, float posY, float length);

};

#endif

