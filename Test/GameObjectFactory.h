#pragma once

#ifndef GAMEOBJECTFACTORY_H_INCLUDED
#define GAMEOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"



// Component Includes
#include "Component.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "RenderComponent.h"

class GameObjectFactory
{
public:
	GameObjectFactory();
	~GameObjectFactory();

	/// Creates a new GameObject Component bag
	virtual GameObject * Spawn();

};

#endif

///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
/*
#pragma once
#ifndef MINIONOBJECTFACTORY_H_INCLUDED
#define MINIONOBJECTFACTORY_H_INCLUDED


class MinionObjectFactory : public GameObjectFactory
{
public:
	MinionObjectFactory();
	~MinionObjectFactory();

	/// Creates a new
	GameObject * Spawn();
	void setPos(GameObject*);


};



#endif
*/