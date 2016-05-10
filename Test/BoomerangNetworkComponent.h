#pragma once
#ifndef BOOMERANGNETWORKCOMPONENT_H_INCLUDED
#define BOOMERANGNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "BoomerangPhysicsComponent.h"
class BoomerangNetworkComponent :
	public NetworkComponent
{
public:
	BoomerangNetworkComponent(GameObject* player);
	~BoomerangNetworkComponent();
	void sendTargetPacket();
	void handleTargetPacket(InputMemoryBitStream& fPacket);
	void Update();
	
};

#endif