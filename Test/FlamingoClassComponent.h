#pragma once
#ifndef FLAMINGOCLASSCOMPONENT_H_INCLUDED
#define FLAMINGOCLASSCOMPONENT_H_INCLUDED

#include "ClassComponent.h"
#include "MineObjectFactory.h"
#include "PlayerObjectFactory.h"

class FlamingoClassComponent :
	public ClassComponent
{
public:
	FlamingoClassComponent(GameObject* player);
	~FlamingoClassComponent();
	void Update();
	int useAbility();
	void readNetAbility(InputMemoryBitStream& aPacket);
	void writeNetAbility(uint64_t PID, float posX, float posY, int team);
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();

	int maxMinesAllowed = 3;
	int numMinesThrown = 0;
};

#endif