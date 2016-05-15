#include "ButtonRenderComponent.h"


ButtonRenderComponent::ButtonRenderComponent(GameObject* button, int imageID, float scale)
{
	gameObjectRef = button;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	layer = "layer1";
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer(layer), imageID, gameObjectRef->posX, gameObjectRef->posY);
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
	sceneMan->RemoveObject(objRef, sceneMan->findLayer(layer));
	AssignSprite(sceneMan->InstantiateObject(sceneMan->findLayer(layer), imageID, gameObjectRef->posX, gameObjectRef->posY));
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
		SceneManager* sceneMan = SceneManager::GetSceneManager();
		int image = (num == 1) ? defaultImage : currentImage;
		sceneMan->RemoveObject(objRef, sceneMan->findLayer(layer));
		AssignSprite(sceneMan->InstantiateObject(sceneMan->findLayer(layer), image, gameObjectRef->posX, gameObjectRef->posY));
	}
}

void ButtonRenderComponent::changeLayer(std::string _layer){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	sceneMan->RemoveObject(objRef, sceneMan->findLayer(layer));
	AssignSprite(sceneMan->InstantiateObject(sceneMan->findLayer(_layer), currentImage, gameObjectRef->posX, gameObjectRef->posY));
	layer = _layer;
}