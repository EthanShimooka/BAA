#pragma once

#ifndef LAUNCHEROBJECTFACTORY_H_INCLUDED
#define LAUNCHEROBJECTFACTORY_H_INCLUDED

#include "LauncherComponentIncludes.h"
#include "GameObject.h"
#include "GameObjectFactory.h"


class LauncherObjectFactory :
	public GameObjectFactory
{
public:
	LauncherObjectFactory();
	~LauncherObjectFactory();
	GameObject * Spawn(uint64_t PID, float posX, float posY, float length, int team);
};

#endif 