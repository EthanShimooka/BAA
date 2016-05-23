#include "BoomerangObjectFactory.h"


BoomerangObjectFactory::BoomerangObjectFactory(){
}


BoomerangObjectFactory::~BoomerangObjectFactory(){
}

GameObject* BoomerangObjectFactory::Spawn(GameObject* owner, uint64_t PID, float destX, float destY){
	GameObject* boomerang = new GameObject();
	boomerang->ID = PID;
	boomerang->isAlive = true;
	boomerang->setPos(owner->posX, owner->posY);
	boomerang->team = owner->team;
	boomerang->type = GAMEOBJECT_TYPE::OBJECT_BOOMERANG;

	BoomerangRenderComponent* rendComp = new BoomerangRenderComponent(boomerang);
	BoomerangPhysicsComponent* physicsComp = new BoomerangPhysicsComponent(boomerang, owner, (int)destX, (int)destY);
	BoomerangLogicComponent* logicComp = new BoomerangLogicComponent(boomerang);

	return boomerang;
}