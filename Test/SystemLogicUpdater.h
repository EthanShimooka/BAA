/**  SystemLogicUpdater.h
*  Author: Ethan Shimooka
*  Date 2 / 26 / 2016
* Description :
System class for updating all known Logic Components.

*/
#pragma once

#ifndef SYSTEMLOGICUPDATER_H_INCLUDED
#define SYSTEMLOGICUPDATER_H_INCLUDED

#include "GameObject.h"
#include <vector>

class SystemLogicUpdater
{
public:
	///Constructor
	SystemLogicUpdater();
	///Deconstructor
	~SystemLogicUpdater();
	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void LogicUpdate(std::vector<GameObject*> obj);
};

#endif