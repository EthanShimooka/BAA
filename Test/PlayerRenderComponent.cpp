#include "PlayerRenderComponent.h"


PlayerRenderComponent::PlayerRenderComponent()
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2, 0, 0);

}


PlayerRenderComponent::~PlayerRenderComponent()
{
}

void PlayerRenderComponent::Update(){
	RenderComponent::Update();
}


