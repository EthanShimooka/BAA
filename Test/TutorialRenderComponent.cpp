#include "TutorialRenderComponent.h"


TutorialRenderComponent::TutorialRenderComponent(GameObject* tutorial, int _imageID, float scale)
{
	gameObjectRef = tutorial;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	sceneMan = SceneManager::GetSceneManager();
	layer = "layer1";
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer(layer), _imageID, gameObjectRef->posX, gameObjectRef->posY);
	objRef->setVisible(false);
	objRef->setScale(scale);
	imageID = _imageID;
	on = false;
}


TutorialRenderComponent::~TutorialRenderComponent()
{
	sceneMan->RemoveObject(objRef, sceneMan->findLayer(layer));
}

void TutorialRenderComponent::toggleImage(bool on){
	objRef->setVisible(on);
	this->on = on;
}

void TutorialRenderComponent::toggleImage(){
	on = !on;
	objRef->setVisible(on);
}