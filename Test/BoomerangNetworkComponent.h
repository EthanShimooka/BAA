#pragma once
#ifndef BOOMERANGNETWORKCOMPONENT_H_INCLUDED
#define BOOMERANGNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
class BoomerangNetworkComponent :
	public NetworkComponent
{
public:
	BoomerangNetworkComponent(GameObject* player);
	~BoomerangNetworkComponent();
	void Update();
	clock_t prevClock;
};

#endif