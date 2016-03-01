#pragma once
#ifndef FEATHERLOGICCOMPONENT_H_INCLUDED
#define FEATHERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "FeatherComponentIncludes.h"

class FeatherLogicComponent : public LogicComponent
{
public:
	/// Constructor
	FeatherLogicComponent(float posX, float posY, float dx, float dy);
	/// Destructor
	~FeatherLogicComponent();
	/// Update Function
	void Update();

	float x;
	float y;
};

#endif