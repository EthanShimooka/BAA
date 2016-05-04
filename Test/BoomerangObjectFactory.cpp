#include "BoomerangObjectFactory.h"


BoomerangObjectFactory::BoomerangObjectFactory(){
}


BoomerangObjectFactory::~BoomerangObjectFactory(){
}

GameObject* BoomerangObjectFactory::Spawn(uint64_t PID, float posX, float posY, float destX, float destY, int _team){
	GameObject* boomerang = new GameObject();
	boomerang->ID = PID;
	boomerang->isAlive = true;
	boomerang->setPos(posX, posY);
	boomerang->team = _team;
	boomerang->type = GAMEOBJECT_TYPE::OBJECT_BOOMERANG;

	BoomerangRenderComponent* rendComp = new BoomerangRenderComponent(boomerang);
	BoomerangPhysicsComponent* physicsComp = new BoomerangPhysicsComponent(boomerang, destX, destY);
	BoomerangLogicComponent* logicComp = new BoomerangLogicComponent(boomerang);

	return boomerang;
}