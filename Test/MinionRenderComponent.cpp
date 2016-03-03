#include "MinionRenderComponent.h"


MinionRenderComponent::MinionRenderComponent(GameObject* minion){
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, 0, 0);
}


MinionRenderComponent::~MinionRenderComponent()
{
}

void MinionRenderComponent::Update(){
	RenderComponent::Update();
}