#include "MineRenderComponent.h"

MineRenderComponent::MineRenderComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	//TODO: change the coordinates to be relative to the player
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4000, 0, 0);
}

MineRenderComponent::~MineRenderComponent(){
	for (auto i = animations.begin(); i != animations.end(); i++){
		delete i->second;
	}
}

void MineRenderComponent::Update(){
	RenderComponent::Update();
}