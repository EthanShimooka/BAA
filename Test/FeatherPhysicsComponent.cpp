#include "FeatherPhysicsComponent.h"


FeatherPhysicsComponent::FeatherPhysicsComponent(GameObject* feather)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}


FeatherPhysicsComponent::~FeatherPhysicsComponent()
{
}

void FeatherPhysicsComponent::Update() {

}