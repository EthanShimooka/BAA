#pragma once
#ifndef MINIONLOGICCOMPONENT_H_INCLUDED
#define MINIONLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"

class MinionLogicComponent : public LogicComponent
{
public:
	/// Constructor
	MinionLogicComponent();
	/// Destructor
	~MinionLogicComponent();
	/// Update Function
	void Update();
};

#endif