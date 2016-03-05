/**
*  PowerShieldObjectFactory.h
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
#ifndef POWERSHIELDOBJECTFACTORY_H_INCLUDED
#define POWERSHIELDOBJECTFACTORY_H_INCLUDED

// Component Includes
#include "PowerShieldIncludes.h"

#include "Component.h"
#include "GameObject.h"
#include "GameObjectFactory.h"



class PowerShieldObjectFactory :  public GameObjectFactory
{

private:
protected:
public:
	/// Constructor
	PowerShieldObjectFactory();
	/// Destructor
	~PowerShieldObjectFactory();
	/// Spawn Function
	// Probably going to be changed **
	GameObject * Spawn(uint64_t PID, float posX, float posY, float length, bool direction);

};

#endif