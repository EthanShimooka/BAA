#include "PlayerObjectFactory.h"

PlayerObjectFactory::PlayerObjectFactory()
{
}


PlayerObjectFactory::~PlayerObjectFactory()
{

}


/// Spawn() assembles nessasary Components and throws them into
/// a "GameObject" Container.

GameObject* PlayerObjectFactory::Spawn(uint64_t PID, int classType, bool local)
{

	GameObject* player = new GameObject();
	player->ID = PID;
	player->isAlive = true;
	player->type = GAMEOBJECT_TYPE::OBJECT_PLAYER;
//	player->isNetworkControlled = !local;

	if (local){
		PlayerInputComponent* input = new PlayerInputComponent(player);
		PlayerPhysicsComponent* physics = new PlayerPhysicsComponent(player);
	}

	PlayerRenderComponent* rend = new PlayerRenderComponent(player);

	PlayerLogicComponent* logic = new PlayerLogicComponent(player);

	

	PlayerNetworkComponent* net = new PlayerNetworkComponent(player);
	player->setPos(player->posX, 200);
	
	return player;
}