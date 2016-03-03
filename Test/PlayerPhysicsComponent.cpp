#include "PlayerPhysicsComponent.h"


PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}


PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}



void PlayerPhysicsComponent::Update()
{
}