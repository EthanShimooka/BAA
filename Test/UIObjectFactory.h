/**
*  PlayerObjectFactory.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
UIObjectFactory is the abstract UIObject (entity) assembler for which
diffrent "Object types" can be instatiated, based on  what types of components
are used.

In this particular instance, the player class is assembled. Notice, it is the ONLY
assembler that will use the input component.
*/
#pragma once
#ifndef UIOBJECTFACTORY_H_INCLUDED
#define UIOBJECTFACTORY_H_INCLUDED

#include "UIObject.h"
#include "WorldObjectFactory.h"


// Component Includes
#include "Component.h"
#include "UITypeComponent.h"
#include "UIInputComponent.h"
#include "UIComponent.h"


class UIObjectFactory : public WorldObjectFactory
{
public:
	UIObjectFactory();
	~UIObjectFactory();

	uint64_t player = 0;
	/// Creates a new UI Object
	UIObject* Spawn(UIType PID, int x, int y);
};

#endif
