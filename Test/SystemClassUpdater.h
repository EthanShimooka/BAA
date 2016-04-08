#pragma once

#ifndef SYSTEMCLASSUPDATER_H_INCLUDED
#define SYSTEMCLASSUPDATER_H_INCLUDED

#include "GameObject.h"

class SystemClassUpdater
{
public:
	/// Constructor
	SystemClassUpdater();
	/// Destructor
	~SystemClassUpdater();
	/// Accepts a global vector of all GameObjects (entities) and cycles through them
	void ClassUpdate(std::vector<GameObject*> obj);
};
#endif
