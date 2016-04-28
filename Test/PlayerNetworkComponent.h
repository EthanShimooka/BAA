#pragma once
#ifndef PLAYERNETWORKCOMPONENT_H_INCLUDED
#define PLAYERNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "PlayerComponentIncludes.h"
#include  "GameSession.h"

typedef enum {
	CM_INVALID = 0,
	CM_MOVE    = 1,
	CM_ATTACK  = 2,
	CM_ABILITY = 3,
	CM_DIE     = 4,
	CM_JUMP    = 5,
}COMMAND_TYPE;


class PlayerLogicComponent;
class PlayerRenderComponent;

class PlayerNetworkComponent : public NetworkComponent
{
public:
	/// Construcor 
	PlayerNetworkComponent(GameObject* player);
	/// Destructor
	~PlayerNetworkComponent();
	/// Update
	void Update();


	/// creating packets
	void createFeatherPacket(uint64_t ID, int finalX, int finalY, float speed);
	void createMovementPacket();
	void createAbilityPacket(uint64_t ID, int finalX, int finalY, float speed);
	void createDeathPacket(uint64_t shooter);

	/// handling packets
	void handleMovementPacket(InputMemoryBitStream& mPacket);
	void handleFeatherPacket(InputMemoryBitStream& fPacket);
	void handleAbilityPacket(InputMemoryBitStream& aPacket);
	void handleDeathPacket(InputMemoryBitStream& dPacket);
	

	/// Pointer to the player logic component
	PlayerLogicComponent *logic;
	/// Pointer to the player render component
	PlayerRenderComponent *render;
};

#endif