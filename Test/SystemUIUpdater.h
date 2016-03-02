/**
*  UIInputUpdater.h
*  Author: Ethan Shimooka, Vincent Moudy
*  Date 2/25/2016
*  Description :
System class for updating all known UI Components.

*/

#pragma once

#ifndef SYSTEMUIUPDATER_H_INCLUDED
#define SYSTEMUIUPDATER_H_INCLUDED


#include "UIObject.h"
#include "UIComponent.h"



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
