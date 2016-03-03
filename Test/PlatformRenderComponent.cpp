#include "PlatformRenderComponent.h"


PlatformRenderComponent::PlatformRenderComponent(GameObject* platform){
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 0, 0, 0);
}


PlatformRenderComponent::~PlatformRenderComponent()
{
}

void PlatformRenderComponent::Update(){
	RenderComponent::Update();
}