/**
*  GameObjectFactory.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	GameObjectFactory is the abstract GameObject (entity) assembler for which 
	diffrent "Object types" can be instatiated, based on  what types of components
	are used.

*/

#pragma once

#ifndef GAMEOBJECTFACTORY_H_INCLUDED
#define GAMEOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"

#include "SystemGameObjectQueue.h"

// Component Includes
#include "Component.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "RenderComponent.h"

class GameObjectFactory
{
public:
	/// Constructor
	GameObjectFactory();
	/// Destructor
	~GameObjectFactory();

	/// Creates a new GameObject Component bag
	virtual GameObject * Spawn();

};

enum EFFECT_TYPE{
	EFFECT_EXPLOSION = 0,
	EFFECT_PLACEHOLDER = 1
};

#endif






///////////////////////////////////////////////////////////////////////
///IGNORE PLZ
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