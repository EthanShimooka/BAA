#include "PlayerLogicComponent.h"


PlayerLogicComponent::PlayerLogicComponent()
{
}


PlayerLogicComponent::~PlayerLogicComponent()
{
}


void PlayerLogicComponent::Update()
{


}


void PlayerLogicComponent::spawnFeather(int dx, int dy){
	GameObjects.AddObject(fFactory.Spawn(featherNum++, gameObjectRef->posX, gameObjectRef->posY, dx, dy));
}