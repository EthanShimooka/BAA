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
	/// Activates chicken ability
	int useAbility();
	/// Destroys shield object and removes it from ID list
	void destroyShield();
	void writeNetAbility(uint64_t PID, float posX, float posY, bool direction, int team);
	void readNetAbility(InputMemoryBitStream& aPacket);
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();
	/// List of object IDs of active chicken shields
	list<uint64_t> shieldIDs;

	/// Length chicken shield lasts in seconds
	float shieldLength = 5.5;
	/// Timer and helper variables to support up to 8 chickenss
	Invoke* timer;
	bool invokeHelper = false;
	/// Number of chicken shields currently active
	int activeShields = 0;
};

#endif