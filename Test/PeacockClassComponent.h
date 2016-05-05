#pragma once
#include "ClassComponent.h"
#include "PlayerObjectFactory.h"
#include "FanObjectFactory.h"
class PeacockClassComponent :
	public ClassComponent
{
public:
	PeacockClassComponent(GameObject* player);
	~PeacockClassComponent();
	void Update();
	int useAbility();
	void writeNetAbility(uint64_t PID, float posX, float posY, float rotation);
	void readNetAbility(InputMemoryBitStream& aPacket);
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();

};