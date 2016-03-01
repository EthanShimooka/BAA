#pragma once
#ifndef MINIONNETWORKCOMPONENT_H_INCLUDED
#define MINIONNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "MinionComponentIncludes.h"
class MinionNetworkComponent : public NetworkComponent
{
private:
public:
	/// Construcor 
	MinionNetworkComponent();
	/// Destructor
	~MinionNetworkComponent();
	/// Update
	void Update();
};

#endif