#pragma once
#ifndef MINIONLOGICCOMPONENT_H_INCLUDED
#define MINIONLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "MinionComponentIncludes.h"
class MinionLogicComponent : public LogicComponent
{
public:
	/// Constructor
	MinionLogicComponent(GameObject* minion);
	
	/// Destructor
	~MinionLogicComponent();
	/// Update Function
	void Update();
	/// Remove minion after being hit enemy with feather
	void DestroyMinion(uint64_t ID);

	/// indicates how far the minion should travel before going back
	float length;
	float initialX;
	float initialY;
	bool walkRight;
};

#endif