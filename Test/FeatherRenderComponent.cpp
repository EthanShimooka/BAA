#include "FeatherRenderComponent.h"

FeatherRenderComponent::FeatherRenderComponent(GameObject* feather){
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 20, 0, 0);
	objRef->setAnchor(1.0, 0.54);
}


FeatherRenderComponent::~FeatherRenderComponent()
{
}

void FeatherRenderComponent::Update(){
	RenderComponent::Update();
}