/**
*  PlayerObjectFactory.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	GameObjectFactory is the abstract GameObject (entity) assembler for which
	diffrent "Object types" can be instatiated, based on  what types of components
	are used.

	In this particular instance, the player class is assembled. Notice, it is the ONLY
	assembler that will use the input component.
*/
#pragma once
#ifndef PLAYEROBJECTFACTORY_H_INCLUDED
#define PLAYEROBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "MovementComponent.h"
#include "PlayerComponentIncludes.h"
#include "ClassComponentIncludes.h"



class PlayerObjectFactory : public GameObjectFactory
{
public:
	PlayerObjectFactory();
	~PlayerObjectFactory();

	/// Creates a new player GameObject
	GameObject * Spawn(uint64_t PID, int classType, int team, bool local);
	
};

enum classType {
	CLASS_CHICKEN = 1,
	CLASS_PEACOCK = 2,
	CLASS_FLAMINGO = 3,
	CLASS_QUAIL = 4,
	CLASS_TURKEY = 5,
	CLASS_EAGLE = 7,
};

#endif
