#pragma once
#ifndef FEATHERLOGICCOMPONENT_H_INCLUDED
#define FEATHERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"

class FeatherLogicComponent : public LogicComponent
{
public:
	/// Constructor
	FeatherLogicComponent();
	/// Destructor
	~FeatherLogicComponent();
	/// Update Function
	void Update();
};

#endif