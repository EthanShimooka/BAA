#include "PlayerLogicComponent.h"


PlayerLogicComponent::PlayerLogicComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


PlayerLogicComponent::~PlayerLogicComponent()
{
}


void PlayerLogicComponent::Update()
{
}


uint64_t PlayerLogicComponent::spawnFeather(int dx, int dy){
	GameObjects.AddObject(fFactory.Spawn(featherNum++, gameObjectRef->posX, gameObjectRef->posY, dx, dy));
	return featherNum - 1;
}

void PlayerLogicComponent::spawnFeather(uint64_t ID, float initialX, float initialY, int destX, int destY){
	GameObjects.AddObject(fFactory.Spawn(ID, initialX, initialY, destX, destY));
}