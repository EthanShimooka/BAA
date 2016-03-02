#pragma once
#ifndef PLAYERNETWORKCOMPONENT_H_INCLUDED
#define PLAYERNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "PlayerComponentIncludes.h"

typedef enum {
	CM_INVALID = 0,
	CM_MOVE    = 1,
	CM_ATTACK  = 2,
	CM_ABILITY = 3,
	CM_DIE     = 4,
	CM_JUMP    = 5,
}COMMAND_TYPE;

class PlayerNetworkComponent : public NetworkComponent
{
public:
	/// Construcor 
	PlayerNetworkComponent();
	/// Destructor
	~PlayerNetworkComponent();
	/// Update
	void Update();
};

#endif