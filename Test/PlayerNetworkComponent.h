#pragma once
#ifndef PLAYERNETWORKCOMPONENT_H_INCLUDED
#define PLAYERNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
class PlayerNetworkComponent : public NetworkComponent
{
private:
	enum playerCommand
	{
		CM_INVALID,
		CM_MOVE,
		CM_ABILITY,
		CM_ATTACK,
		CM_DIE,
		CM_JUMP
	};

public:
	PlayerNetworkComponent();
	~PlayerNetworkComponent();

	void Update();
};

#endif