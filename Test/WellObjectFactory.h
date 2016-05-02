#pragma once

#ifndef WELLOBJECTFACTORY_H_INCLUDED
#define WELLOBJECTFACTORY_H_INCLUDED

#include "WellComponentIncludes.h"
#include "GameObjectFactory.h"

class WellObjectFactory :
	public GameObjectFactory
{
public:
	WellObjectFactory();
	~WellObjectFactory();
	GameObject * WellObjectFactory::Spawn(uint64_t PID, float posX, float posY, float length, int team);
};

#endif