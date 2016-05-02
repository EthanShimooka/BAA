
#include "WellRenderComponent.h"


WellRenderComponent::WellRenderComponent(GameObject * well, int team)
{
	gameObjectRef = well;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 8000, 0, 0);

}


WellRenderComponent::~WellRenderComponent()
{
}

void WellRenderComponent::Update() {
	RenderComponent::Update();
}

