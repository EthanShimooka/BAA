#include "PowerShieldRenderComponent.h"


PowerShieldRenderComponent::PowerShieldRenderComponent(GameObject* shield)
{
	/// Set GameObject to "shield" argument
	gameObjectRef = shield;
	
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	/// 998 refers to a temporary power shield 
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 4003, 0, 0);

	objRef->setAnchor(1.0, 0.54);

}


PowerShieldRenderComponent::~PowerShieldRenderComponent()
{
}

void PowerShieldRenderComponent::Update()
{
	RenderComponent::Update();

}