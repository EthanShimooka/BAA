#pragma once
#ifndef MINIONNETWORKCOMPONENT_H_INCLUDED
#define MINIONNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "MinionComponentIncludes.h"

typedef enum {
	CM_DIE = 1,
}COMMAND_TYPE;

class MinionNetworkComponent : public NetworkComponent
{
private:
public:
	/// Construcor 
	MinionNetworkComponent(GameObject* minion);
	/// Destructor
	~MinionNetworkComponent();
	/// Update
	void Update();

	///Send menion death
	void SendMenionDeath(uint64_t ID);
	///Handle menion death
	void HandleMenionDeath(InputMemoryBitStream& inPacket);

	MinionLogicComponent* logic;
};

#endif