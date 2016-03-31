#pragma once
#include "LogicComponent.h"
class MidPlatLogicComponent :
	public LogicComponent
{
public:
	MidPlatLogicComponent(GameObject* platform);
	~MidPlatLogicComponent();
};

