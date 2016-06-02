#pragma once
#include "NetworkComponent.h"
#include "Stats.h"
class MidBaseNetworkComponent :
	public NetworkComponent
{
public:
	MidBaseNetworkComponent(GameObject* base);
	~MidBaseNetworkComponent();
	/// Update
	void Update();
	///Send base hit
	void SendBaseHealth();
	///Handle base hit
	void HandleBaseHealth(InputMemoryBitStream& packet);

private:
	enum BASE_NET {
		BASE_INVALID = 0,
		BASE_HEALTH = 1,
	};
};

