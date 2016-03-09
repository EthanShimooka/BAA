#include "PowerShieldNetworkComponent.h"


PowerShieldNetworkComponent::PowerShieldNetworkComponent(GameObject* shield)
{
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);

}


PowerShieldNetworkComponent::~PowerShieldNetworkComponent()
{
}

void PowerShieldNetworkComponent::Update()
{
}