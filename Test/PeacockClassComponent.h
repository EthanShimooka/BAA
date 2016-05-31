#pragma once
#include "ClassComponent.h"
#include "PlayerObjectFactory.h"
#include "FanObjectFactory.h"
#include "Invoke.h"
class PeacockClassComponent :
	public ClassComponent
{
public:
	PeacockClassComponent(GameObject* player);
	~PeacockClassComponent();
	void Update();
	/// Activates peacock ability
	int useAbility();
	/// Destroys fan object and removes it from ID list
	void destroyFan();
	void writeNetAbility(uint64_t PID, float posX, float posY, float rotation);
	void readNetAbility(InputMemoryBitStream& aPacket);
	/// Peacock animation
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();
	/// List of object IDs of active peacock fans
	list<uint64_t> fanIDs;

	/// Length peacock fan lasts in seconds
	float fanLength = 10;
	/// Timer and helper variables to support up to 8 peacocks
	Invoke* timer;
	Invoke* timer2;
	Invoke* timer3;
	Invoke* timer4;
	Invoke* timer5;
	Invoke* timer6;
	Invoke* timer7;
	Invoke* timer8;
	bool invokeHelper = false;
	bool invokeHelper2 = false;
	bool invokeHelper3 = false;
	bool invokeHelper4 = false;
	bool invokeHelper5 = false;
	bool invokeHelper6 = false;
	bool invokeHelper7 = false;
	bool invokeHelper8 = false;
	/// Number of peacock fans currently active
	int activeFans = 0;

	//number of fans spawned before reseting birdseed meter
	int currFansSpawned = 0;

	std::unordered_map<std::string, SDLRenderObject*> m_allObjs;

};