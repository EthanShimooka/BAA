#pragma once
#include "LogicComponent.h"
class MidBaseLogicComponent :
	public LogicComponent
{
public:
	MidBaseLogicComponent(GameObject * base);
	~MidBaseLogicComponent();
};

