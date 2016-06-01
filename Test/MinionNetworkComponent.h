#pragma once
#ifndef MINIONNETWORKCOMPONENT_H_INCLUDED
#define MINIONNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "Stats.h"
#include "MinionComponentIncludes.h"

typedef enum {
	MIN_POS = 1,
	MIN_DIE = 2,
	MIN_HIT = 3,
}COMMAND;

class MinionPhysicsComponent;

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
	///Send base hit
	void SendBaseHit(int teamHit, uint64_t minionID, uint64_t baseID);
	///Handle base hit
	void HandleBaseHit(InputMemoryBitStream& packet);
	///Send minion death
	void SendMinionDeath();
	///Handle minion death
	void HandleMinionDeath();
	///Send minion position
	void SendMinionPos();
	///Handle minion position
	void HandleMinionPos(InputMemoryBitStream& packet);
	///issues minion spawning
	void SendSpawnMinion(uint64_t ID, uint8_t team);

	MinionPhysicsComponent *physComp;
};

#endif