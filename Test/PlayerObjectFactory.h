#pragma once
#ifndef PLAYEROBJECTFACTORY_H_INCLUDED
#define PLAYEROBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "InputComponent.h"
#include "MovementComponent.h"
#include "RenderComponent.h"
#include "PlayerRenderComponent.h"


class PlayerObjectFactory : public GameObjectFactory
{
public:
	PlayerObjectFactory();
	~PlayerObjectFactory();

	/// Creates a new player GameObject
	GameObject * Spawn(int PID);
	void setPos(GameObject*);


};

#endif
