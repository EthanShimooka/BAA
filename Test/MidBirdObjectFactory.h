#pragma once
#include "GameObjectFactory.h"
#include "MidBirdRenderComponent.h"



#ifndef MIDBIRDOBJECTFACTORY_H_INCLUDED
#define MIDBIRDOBJECTFACTORY_H_INCLUDED


class MidBirdObjectFactory :
	public GameObjectFactory
{
public:
	MidBirdObjectFactory();
	~MidBirdObjectFactory();
	GameObject * Spawn(uint64_t PID, float posX, float posY);
};

#endif