#pragma once
#ifndef MINIONNETWORKCOMPONENT_H_INCLUDED
#define MINIONNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "MinionComponentIncludes.h"

typedef enum {
	MIN_DIE = 1,
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

	///Send menion death
	void SendMenionDeath();
	///Handle menion death
	void HandleMenionDeath();

	MinionPhysicsComponent *physComp;
};

#endif