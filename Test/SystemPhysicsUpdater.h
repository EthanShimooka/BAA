/**  SystemPhysicsUpdater.h
*  Author: Ethan Shimooka
*  Date 2 / 26 / 2016
* Description :
System class for updating all known Physics Components.

*/
#pragma once



#ifndef SYSTEMPHYSICSUPDATER_H_INCLUDED
#define SYSTEMPHYSICSUPDATER_H_INCLUDED

#include "GameObject.h"
#include <vector>

class SystemPhysicsUpdater
{
public:
	/// Constructor
	SystemPhysicsUpdater();
	/// Destructor
	~SystemPhysicsUpdater();
	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void PhysicsUpdate(std::vector<GameObject*> obj);

};

#endif