#pragma once

#include "GameObject.h"
#include "InputComponent.h"

class SystemInputUpdater
{
public:
	SystemInputUpdater();
	~SystemInputUpdater();


	void InputUpdate(std::vector<GameObject*> obj);


};

