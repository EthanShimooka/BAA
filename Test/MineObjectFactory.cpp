#include "MineObjectFactory.h"


MineObjectFactory::MineObjectFactory(){
}


MineObjectFactory::~MineObjectFactory(){
}

/// Creates a new player GameObject
GameObject * Spawn(uint64_t PID, int classType, bool local){
	GameObject* player = new GameObject();
	player->ID = PID;
	player->isAlive = true;
	player->type = GAMEOBJECT_TYPE::OBJECT_FEATHER;

	MineRenderComponent* rendComp = nullptr;


	//PlayerRenderComponent* rend = new PlayerRenderComponent(player);

	if (local){
		MinePhysicsComponent* physicsComp = new MinePhysicsComponent(player);
	}


	MineLogicComponent* logicComp = new MineLogicComponent(player);

	player->setPos(player->posX, 200);

	return player;
}
