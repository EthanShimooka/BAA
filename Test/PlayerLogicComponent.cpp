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


void PlayerLogicComponent::spawnFeather(){
	GameObjects.AddObject(fFactory.Spawn(featherNum++))->setPos(gameObjectRef->posX, gameObjectRef->posY);
}