#include "PowerShieldPhysicsComponent.h"


PowerShieldPhysicsComponent::PowerShieldPhysicsComponent(GameObject* shield)
{
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	init();
}


PowerShieldPhysicsComponent::~PowerShieldPhysicsComponent()
{
}


void PowerShieldPhysicsComponent::Update()
{
}

void PowerShieldPhysicsComponent::init()
{

}


void PowerShieldPhysicsComponent::handleCollision(GameObject* otherObj){


}