#include "MineObjectFactory.h"


MineObjectFactory::MineObjectFactory(){
}


MineObjectFactory::~MineObjectFactory(){
}

/// Creates a new mine GameObject
GameObject* MineObjectFactory::Spawn(uint64_t PID, GameObject* spawner, int targetX, int targetY){
	GameObject* mine = new GameObject();
	mine->ID = PID;
	mine->isAlive = true;
	mine->setPos(spawner->posX, spawner->posY);
	mine->team = spawner->team;
	mine->type = GAMEOBJECT_TYPE::OBJECT_MINE;

	MineRenderComponent* rendComp = new MineRenderComponent(mine);

	MinePhysicsComponent* physicsComp = new MinePhysicsComponent(mine, targetX, targetY);

	MineLogicComponent* logicComp = new MineLogicComponent(mine);
	logicComp->spawner = spawner;

	

	return mine;
}
