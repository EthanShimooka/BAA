#include "MinionPhysicsComponent.h"


MinionPhysicsComponent::MinionPhysicsComponent(GameObject* minion)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}


MinionPhysicsComponent::~MinionPhysicsComponent()
{
}

void MinionPhysicsComponent::Update(){

}