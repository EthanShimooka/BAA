#pragma once
#include "NetworkComponent.h"
class PlayerNetworkComponent : public NetworkComponent
{
public:
	PlayerNetworkComponent();
	~PlayerNetworkComponent();

	void Update();
};

