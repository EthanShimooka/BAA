#pragma once
#include "ClassComponent.h"
#include "PlayerObjectFactory.h"
class TurkeyClassComponent :
	public ClassComponent
{
public:
	TurkeyClassComponent(GameObject* player);
	~TurkeyClassComponent();
	void Update();
	int useAbility(uint64_t PID, int x, int y);
	void writeNetAbility(uint64_t PID, float posX, float posY, int team);
	void readNetAbility(InputMemoryBitStream& aPacket);
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();

	b2Vec2 turkeyArmsPos;
	int armsMovementState=0;
};