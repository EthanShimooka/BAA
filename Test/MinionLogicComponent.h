#pragma once
#ifndef MINIONLOGICCOMPONENT_H_INCLUDED
#define MINIONLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "MinionComponentIncludes.h"
#include "EffectObjectFactory.h"
class MinionLogicComponent : public LogicComponent
{
public:
	/// Constructor
	MinionLogicComponent(GameObject* minion);
	
	/// Destructor
	~MinionLogicComponent();
	/// Update Function
	void Update();
	/// Visual cues for minion death
	void MinionDeath();
	/// indicates how far the minion should travel before going back
	float length;
	float initialX;
	float initialY;
	bool walkRight;
};

#endif