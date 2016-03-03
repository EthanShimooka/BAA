#include "FeatherNetworkComponent.h"


FeatherNetworkComponent::FeatherNetworkComponent(GameObject* feather)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
}


FeatherNetworkComponent::~FeatherNetworkComponent()
{
}

void FeatherNetworkComponent::Update() {

}