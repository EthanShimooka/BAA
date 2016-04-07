#include "ChickenClassComponent.h"


ChickenClassComponent::ChickenClassComponent(GameObject* player)
{	
	ClassComponent::ClassComponent();
	//speed = 10000;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_CLASS, this);
}


ChickenClassComponent::~ChickenClassComponent()
{
}

void ChickenClassComponent::Update()
{
}