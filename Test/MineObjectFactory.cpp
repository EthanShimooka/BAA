#include "MineObjectFactory.h"


MineObjectFactory::MineObjectFactory(){
}


MineObjectFactory::~MineObjectFactory(){
}

/// Creates a new mine GameObject
GameObject* MineObjectFactory::Spawn(uint64_t PID, GameObject* spawner, float targetX, float targetY){
	GameObject* mine = new GameObject();
	mine->ID = PID;
	mine->isAlive = true;
	mine->setPos(spawner->posX, spawner->posY);
	mine->team = spawner->team;
	mine->type = GAMEOBJECT_TYPE::OBJECT_MINE;
	if (spawner->isLocal) mine->isLocal = true;

	MineRenderComponent* rendComp = new MineRenderComponent(mine);

	MinePhysicsComponent* physicsComp = new MinePhysicsComponent(mine, targetX, targetY);

	MineLogicComponent* logicComp = new MineLogicComponent(mine);
	logicComp->owner = spawner;

	

	return mine;
}
