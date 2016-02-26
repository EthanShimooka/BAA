/**
*  SystemInputUpdater.h
*  Author: Ethan Shimooka
*  Date 2/25/2016
*  Description :
System class for updating all known Input Components.

*/

#pragma once

#ifndef SYSTEMINPUTUPDATER_H_INCLUDED
#define SYSTEMINPUTUPDATER_H_INCLUDED


#include "GameObject.h"
#include "InputComponent.h"



class SystemInputUpdater
{
public:

	/// Constructor
	SystemInputUpdater();
	/// Destructor
	~SystemInputUpdater();

	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void InputUpdate(std::vector<GameObject*> obj);


};

#endif
