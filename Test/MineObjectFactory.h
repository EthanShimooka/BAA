#pragma once
#include "GameObjectFactory.h"
#include "MineComponentIncludes.h"
#ifndef MINEOBJECTFACTORY_H_INCLUDED
#define MINEOBJECTFACTORY_H_INCLUDED
class MineObjectFactory :
	public GameObjectFactory
{
public:
	MineObjectFactory();
	~MineObjectFactory();
	/// Creates a new player GameObject
	GameObject * Spawn(uint64_t PID, int classType, bool local);
};
#endif
