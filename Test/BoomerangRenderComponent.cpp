#include "BoomerangRenderComponent.h"


BoomerangRenderComponent::BoomerangRenderComponent(GameObject* boomerang){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
}


BoomerangRenderComponent::~BoomerangRenderComponent()
{
}
