#include "ButtonRenderComponent.h"


ButtonRenderComponent::ButtonRenderComponent(GameObject* button, int imageID)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), imageID, gameObjectRef->posX, gameObjectRef->posY);
}


ButtonRenderComponent::~ButtonRenderComponent()
{
}

void ButtonRenderComponent::Update(){

}