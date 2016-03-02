/**
*  SystemRenderUpdater.h
*  Author: Ethan Shimooka
*  Date 2/25/2016
*  Description :
System class for updating all known Render Components.

*/
#pragma once

#ifndef SYSTEMRENDERUPDATER_H_INCLUDED
#define SYSTEMRENDERUPDATER_H_INCLUDED

#include <vector>
#include "GameObject.h"
#include "UIObject.h"

class SystemRenderUpdater
{
public:
	///Constructor
	SystemRenderUpdater();
	///Deconstructor
	~SystemRenderUpdater();
	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void RenderUpdate(std::vector<GameObject*> rend);
	/// Accepts a global vector of all UIObjects (entities) and cycles through them
	void RenderUpdate(std::vector<UIObject*> rend);
};

#endif