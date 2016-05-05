#include "BoomerangRenderComponent.h"


BoomerangRenderComponent::BoomerangRenderComponent(GameObject* boomerang){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	//TODO: change the coordinates to be relative to the player
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3502, 0, 0);
	objRef->setScale(0.3);
	//other arm image: objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3503, 0, 0);
}


BoomerangRenderComponent::~BoomerangRenderComponent(){
}

void BoomerangRenderComponent::Update(){

}