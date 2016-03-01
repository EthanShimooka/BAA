/**
*  UIInputUpdater.h
*  Author: Ethan Shimooka, Vincent Moudy
*  Date 2/25/2016
*  Description :
System class for updating all known UI Components.

*/

#pragma once

#ifndef SYSTEMINPUTUPDATER_H_INCLUDED
#define SYSTEMINPUTUPDATER_H_INCLUDED


#include "GameObject.h"
#include "InputComponent.h"



class SystemUIUpdater
{
public:

	/// Constructor
	SystemUIUpdater();
	/// Destructor
	~SystemUIUpdater();

	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void UIUpdate(std::vector<UIObject*> obj);


};

#endif
