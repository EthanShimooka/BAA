#pragma once
#ifndef FANLOGICCOMPONENT_H_INCLUDED
#define FANLOGICCOMPONENT_H_INCLUDED
#include "LogicComponent.h"
#include "FanComponentIncludes.h"
class FanLogicComponent : public LogicComponent
{
public:
	/// Constructor
	FanLogicComponent(GameObject* player);
	/// Destructor
	~FanLogicComponent();
	/// Update Function
	void Update();
};
#endif
