#pragma once
#ifndef  TURKEYCLASSCCOMPONENT_H_INCLUDED
#define  TURKEYCLASSCOMPONENT_H_INCLUDED
#include "ClassComponent.h"
#include "PlayerObjectFactory.h"
#include "BoomerangObjectFactory.h"
class TurkeyClassComponent :
	public ClassComponent
{
public:
	TurkeyClassComponent(GameObject* player);
	~TurkeyClassComponent();
	void Update();
	int useAbility();
	void writeNetAbility(uint64_t PID, float posX, float posY);
	void readNetAbility(InputMemoryBitStream& aPacket);
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();

	b2Vec2 turkeyArmsPos;
	int armsMovementState=0;
};

#endif