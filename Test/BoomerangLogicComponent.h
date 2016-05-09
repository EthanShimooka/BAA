#pragma once
#pragma once
#ifndef  BOOMERANGLOGICCOMPONENT_H_INCLUDED
#define  BOOMERANGLOGICCOMPONENT_H_INCLUDED
#include "LogicComponent.h"
class BoomerangLogicComponent :
	public LogicComponent
{
public:
	BoomerangLogicComponent(GameObject* boomerang);
	~BoomerangLogicComponent();
};

#endif