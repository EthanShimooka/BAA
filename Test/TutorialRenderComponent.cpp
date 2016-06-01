#include "TutorialRenderComponent.h"


TutorialRenderComponent::TutorialRenderComponent(GameObject* tutorial, int _imageID, float scale)
{
	gameObjectRef = tutorial;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	sceneMan = SceneManager::GetSceneManager();
	layer = "layer1";
	//board = sceneMan->InstantiateObject(sceneMan->findLayer(layer), 9300, gameObjectRef->posX, gameObjectRef->posY);

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);

	SDLRenderObject * board = sceneMan->InstantiateObject(sceneMan->findLayer(layer), 9300, gameObjectRef->posX, gameObjectRef->posY);
	SDLRenderObject *  info  = sceneMan->InstantiateObject(sceneMan->findLayer(layer), _imageID, gameObjectRef->posX, gameObjectRef->posY);


	allObjs["base"] = objRef;

	allObjs["board"] = board;
	allObjs["board"]->visible = false;
	allObjs["board"]->setScale(0.25f);
	allObjs["info"] = info;
	allObjs["info"]->visible = false;
	allObjs["info"]->setScale(0.2f);

	allObjs["board"]->setParent(objRef);
	allObjs["info"]->setParent(objRef);


	objRef->setVisible(false);
	objRef->setScale(scale);
	imageID = _imageID;
	on = false;
}


TutorialRenderComponent::~TutorialRenderComponent()
{
	sceneMan->RemoveObject(objRef);
}

void TutorialRenderComponent::toggleImage(bool on){
	objRef->setVisible(on);
	allObjs["board"]->visible = on;
	allObjs["info"]->visible = on;

	this->on = on;
}

void TutorialRenderComponent::toggleImage(){
	on = !on;
	allObjs["board"]->visible = on;
	allObjs["info"]->visible = on;
	objRef->setVisible(on);
}