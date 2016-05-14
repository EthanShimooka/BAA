#include "ButtonRenderComponent.h"


ButtonRenderComponent::ButtonRenderComponent(GameObject* button, int imageID)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), imageID, gameObjectRef->posX, gameObjectRef->posY);
	defaultImage = imageID;
	currentImage = imageID;
}


ButtonRenderComponent::~ButtonRenderComponent()
{
}

void ButtonRenderComponent::Update(){

}

void ButtonRenderComponent::changeSprite(int imageID){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	sceneMan->RemoveObject(objRef, sceneMan->findLayer("layer1"));
	AssignSprite(sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), imageID, gameObjectRef->posX, gameObjectRef->posY));
	currentImage = imageID;
}

void ButtonRenderComponent::setToDefault(){
	changeSprite(defaultImage);
}