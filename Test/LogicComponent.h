/**
*  LogicComponent.h
*  Authors: Ethan Shimooka
*  Date 2/26/2016
*  Description :
	Logic Component is the abstract component class that contains all of the game logic.
	To be overriden with each type of objects unique logic  class.

*/

#pragma once

#ifndef LOGICCOMPONENT_H_INCLUDED
#define LOGICCOMPONENT_H_INCLUDED

#include "Component.h"
#include "GameObject.h"
class LogicComponent : public Component
{
public:
	/// Constructor
	LogicComponent();
	/// Destructor
	virtual ~LogicComponent();
	/// GameObject Container Reference
	GameObject* gameObjectRef;

	/// Virtual Update function
	virtual void Update();

};

#endif