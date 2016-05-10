#pragma once
#pragma once
#ifndef  BOOMERANGLOGICCOMPONENT_H_INCLUDED
#define  BOOMERANGLOGICCOMPONENT_H_INCLUDED
#include "LogicComponent.h"
#include "BoomerangComponentIncludes.h"
class BoomerangLogicComponent :
	public LogicComponent
{
public:
	BoomerangLogicComponent(GameObject* boomerang);
	~BoomerangLogicComponent();
	void Update();

	clock_t updateClock;
	clock_t flightClock;
	int updateInterval = 400;
	bool returning=false;
};

#endif