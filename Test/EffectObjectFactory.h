#pragma once
#ifndef EFFECTOBJECTFACTORY_H_INCLUDED
#define EFFECTOBJECTFACTORY_H_INCLUDED

#include "GameObject.h"
#include "GameObjectFactory.h"


// Component Includes
#include "Component.h"
#include "EffectRenderComponent.h"

class EffectObjectFactory : public GameObjectFactory
{
public:
	/// Constructor
	EffectObjectFactory();
	/// Destructor
	~EffectObjectFactory();

	/// Creates a new effect GameObject
	GameObject * Spawn(float posX, float posY, int effectType);

};

#endif