#include "MinionRenderComponent.h"


MinionRenderComponent::MinionRenderComponent(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 12, 100, 0);
}


MinionRenderComponent::~MinionRenderComponent()
{
}

void MinionRenderComponent::Update(){

}