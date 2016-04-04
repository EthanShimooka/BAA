/**
*  WorldObjectFactory.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
WorldObjectFactory is the abstract UIObject (entity) assembler for which
diffrent "Object types" can be instatiated, based on  what types of components
are used.

*/

#pragma once

#ifndef WORLDOBJECTFACTORY_H_INCLUDED
#define WORLDOBJECTFACTORY_H_INCLUDED

#include "UIObject.h"



// Component Includes
#include "Component.h"
#include "InputComponent.h"
#include "RenderComponent.h"

class WorldObjectFactory
{
public:
	/// Constructor
	WorldObjectFactory();
	/// Destructor
	~WorldObjectFactory();

	/// Creates a new GameObject Component bag
	virtual UIObject * Spawn();

};

#endif

