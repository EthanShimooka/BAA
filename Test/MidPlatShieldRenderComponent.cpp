#include "MidPlatShieldRenderComponent.h"


MidPlatShieldRenderComponent::MidPlatShieldRenderComponent(GameObject* platform)
{
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	SceneManager* sceneMan = SceneManager::GetSceneManager();

	//objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 9991, 0, 0);

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2005, 0, 0);
	allObjs["button"] = objRef;

	SDLRenderObject * shield = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2006, 0, 0);

	allObjs["shield"] = shield;
	allObjs["shield"]->setPos(gameObjectRef->posX, gameObjectRef->posY);
	allObjs["shield"]->visible = false;

	//SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 10, 10);
	//box->setIfRenderRect(true);
	//allObjs["box"] = box;

}

MidPlatShieldRenderComponent::~MidPlatShieldRenderComponent()
{
}

void MidPlatShieldRenderComponent::Update(){
	RenderComponent::Update();
}