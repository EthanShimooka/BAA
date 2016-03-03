#include "FeatherPhysicsComponent.h"


FeatherPhysicsComponent::FeatherPhysicsComponent(GameObject* feather)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}

FeatherPhysicsComponent::~FeatherPhysicsComponent(){}

void FeatherPhysicsComponent::handleCollision(GameObject* otherObj){
	cout << "feather handling collision with object ID: " << otherObj->ID << endl;
	//probably destroy itself, maybe trigger a sound?
	switch (otherObj->type){
		case GAMEOBJECT_TYPE::OBJECT_MINION:
			//destroy self or return to object pool
			break;
		case GAMEOBJECT_TYPE::OBJECT_PLAYER:
			//destroy self or return to object pool
			break;
		default:
			break;
	}
}

void FeatherPhysicsComponent::Update() {

}