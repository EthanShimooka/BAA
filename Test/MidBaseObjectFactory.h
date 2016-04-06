#pragma once

#ifndef MIDBASEOBJECTFACTORY_H_INCLUDED
#define MIDBASEOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"

#include "Component.h"
#include "MidBaseComponentIncludes.h"


class MidBaseObjectFactory :
	public GameObjectFactory
{
public:
	MidBaseObjectFactory();
	~MidBaseObjectFactory();

	GameObject * Spawn(uint64_t PID, float posX, float posY, float length);
};

#endif