#pragma once
#ifndef PLAYERNETWORKCOMPONENT_H_INCLUDED
#define PLAYERNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
class PlayerNetworkComponent : public NetworkComponent
{
public:
	PlayerNetworkComponent();
	~PlayerNetworkComponent();

	void Update();
};

#endif