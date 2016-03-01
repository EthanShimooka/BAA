#pragma once
#ifndef MINIONLOGICCOMPONENT_H_INCLUDED
#define MINIONLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "MinionComponentIncludes.h"
class MinionLogicComponent : public LogicComponent
{
public:
	/// Constructor
	MinionLogicComponent();
	/// Constructor
	MinionLogicComponent(GameObject* minion, float _initialX, float _initialY, float _length, bool _walkRight)
		: initialX(_initialX), initialY(_initialY), length(_length), walkRight(true)
	{
		gameObjectRef = minion;
	}
	/// Destructor
	~MinionLogicComponent();
	/// Update Function
	void Update();

	/// indicates how far the minion should travel before going back
	float length;
	float initialX;
	float initialY;
	bool walkRight;
};

#endif