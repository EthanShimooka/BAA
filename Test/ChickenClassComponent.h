#pragma once
#ifndef CHICKENCLASSCOMPONENT_H_INCLUDED
#define CHICKENCLASSCOMPONENT_H_INCLUDED

#include "ClassComponent.h"
#include "PowerShieldObjectFactory.h"
#include "PlayerObjectFactory.h"
class ChickenClassComponent :
	public ClassComponent
{
public:
	ChickenClassComponent(GameObject* player);
	~ChickenClassComponent();
	void Update();
	int useAbility();
	void writeNetAbility(uint64_t PID, float posX, float posY, bool direction);
	void readNetAbility(InputMemoryBitStream& aPacket);
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();
};

#endif