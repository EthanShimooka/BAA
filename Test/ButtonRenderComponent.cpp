#include "ButtonRenderComponent.h"


ButtonRenderComponent::ButtonRenderComponent(GameObject* button, int imageID, float scale)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), imageID, gameObjectRef->posX, gameObjectRef->posY);
	defaultImage = imageID;
	currentImage = imageID;
	objRef->setScale(scale);
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

void swap(int& onSprite, int& offSprite){
	int tempSprite = onSprite;
	onSprite = offSprite;
	offSprite = tempSprite;
}

void ButtonRenderComponent::addSecondSprite(int imageID) {
	currentImage = imageID;
}

void ButtonRenderComponent::toggleSprites(){
	// if we have two different sprites
	if (defaultImage != currentImage){
		swap(defaultImage, currentImage);
		changeSprite(defaultImage);
	}
}

void ButtonRenderComponent::toggleSprites(int num){
	// if we have two different sprites
	if (defaultImage != currentImage){
		changeSprite((num == 1) ? defaultImage : currentImage);
	}
}