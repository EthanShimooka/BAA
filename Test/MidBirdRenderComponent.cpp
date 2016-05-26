#include "MidBirdRenderComponent.h"


MidBirdRenderComponent::MidBirdRenderComponent(GameObject * bird)
{
	gameObjectRef = bird;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	//buildAnimation();
	//setAnimation("idle");

}


MidBirdRenderComponent::~MidBirdRenderComponent()
{






}






void MidBirdRenderComponent::Update(){



}