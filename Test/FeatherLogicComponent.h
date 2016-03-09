#pragma once
#ifndef FEATHERLOGICCOMPONENT_H_INCLUDED
#define FEATHERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "FeatherComponentIncludes.h"

class FeatherLogicComponent : public LogicComponent
{
public:
	/// Constructor
	FeatherLogicComponent(GameObject* feather);
	/// Destructor
	~FeatherLogicComponent();
	/// Update Function
	void Update();
	/// init Function
	void init();
};

#endif