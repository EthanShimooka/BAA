#pragma once

#ifndef PLATFORMOBJECTFACTORY_H_INCLUDED
#define PLATFORMOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"

#include "Component.h"
#include "MidPlatComponentIncludes.h"


class MidPlatObjectFactory :
	public GameObjectFactory
{
public:
	MidPlatObjectFactory();
	~MidPlatObjectFactory();

	GameObject * Spawn(uint64_t PID, float posX, float posY, float length);
};

#endif