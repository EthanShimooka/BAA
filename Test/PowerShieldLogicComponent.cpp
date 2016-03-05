#include "PowerShieldLogicComponent.h"


PowerShieldLogicComponent::PowerShieldLogicComponent(GameObject* shield)
{
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);


}


PowerShieldLogicComponent::~PowerShieldLogicComponent()
{
}


void PowerShieldLogicComponent::Update(){


}

void PowerShieldLogicComponent::spawnShield(int xpos, int ypos){



}

void PowerShieldLogicComponent::spawnShield(uint64_t ID, float initialX, float initialY, int destX, int destY){



}

