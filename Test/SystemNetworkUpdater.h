/**  SystemNetworkUpdater.h
*  Author: Ethan Shimooka
*  Date 2 / 26 / 2016
* Description :
System class for updating all known Network Components.

*/
#pragma once

#ifndef SYSTEMNETWORKUPDATER_H_INCLUDED
#define SYSTEMNETWORKUPDATER_H_INCLUDED

#include "GameObject.h"
#include <vector>
class SystemNetworkUpdater
{
public:
	///Constructor
	SystemNetworkUpdater();
	///Deconstructor
	~SystemNetworkUpdater();
	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void NetworkUpdate(std::vector<GameObject*> obj);
};

#endif