#pragma once
#ifndef PLAYERNETWORKCOMPONENT_H_INCLUDED
#define PLAYERNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "PlayerComponentIncludes.h"
class PlayerNetworkComponent : public NetworkComponent
{
private:
	typedef enum {
		CM_INVALID,
		CM_MOVE,
		CM_ABILITY,
		CM_ATTACK,
		CM_DIE,
		CM_JUMP
	}COMMAND_TYPE;

public:
	/// Construcor 
	PlayerNetworkComponent();
	/// Destructor
	~PlayerNetworkComponent();
	/// Update
	void Update();
};

#endif