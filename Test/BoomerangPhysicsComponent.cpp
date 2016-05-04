#include "BoomerangPhysicsComponent.h"


BoomerangPhysicsComponent::BoomerangPhysicsComponent(GameObject* boomerang, int destX, int destY){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}


BoomerangPhysicsComponent::~BoomerangPhysicsComponent(){
}
