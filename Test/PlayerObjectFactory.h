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
#include "PlayerRenderComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerNetworkComponent.h"
#include "PlayerLogicComponent.h"
#include "PlayerPhysicsComponent.h"



class PlayerObjectFactory : public GameObjectFactory
{
public:
	PlayerObjectFactory();
	~PlayerObjectFactory();

	/// Creates a new player GameObject
	GameObject * Spawn(int PID);
	/// Set postion of gameObject
	void setPos(GameObject*);


};

#endif
