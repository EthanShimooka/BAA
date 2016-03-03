#include "FeatherPhysicsComponent.h"


FeatherPhysicsComponent::FeatherPhysicsComponent(GameObject* feather)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}

FeatherPhysicsComponent::~FeatherPhysicsComponent(){}

void FeatherPhysicsComponent::handleCollision(GameObject* otherObj){
	//probably destroy itself, maybe trigger a sound?
}

void FeatherPhysicsComponent::Update() {

}