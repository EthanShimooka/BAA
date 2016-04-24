#include "FanRenderComponent.h"


FanRenderComponent::FanRenderComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 8000, 0, 0);
}


FanRenderComponent::~FanRenderComponent()
{
}

void FanRenderComponent::Update() {
	RenderComponent::Update();
}