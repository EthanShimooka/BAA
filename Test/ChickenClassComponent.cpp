#include "ChickenClassComponent.h"


ChickenClassComponent::ChickenClassComponent(GameObject* player)
{	
	ClassComponent::ClassComponent();
	speed = 10000;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
}


ChickenClassComponent::~ChickenClassComponent()
{
}

void ChickenClassComponent::Update()
{
}