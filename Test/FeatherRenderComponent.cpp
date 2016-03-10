#include "FeatherRenderComponent.h"

FeatherRenderComponent::FeatherRenderComponent(GameObject* feather){
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 20, 0, 0);
	objRef->setAnchor(1.0, 0.54);
	allObjs["base"] = objRef;

	SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 10, 10);
	box->setIfRenderRect(true);
	box->setParent(objRef);
	allObjs["box"] = box;

}


FeatherRenderComponent::~FeatherRenderComponent()
{
}

void FeatherRenderComponent::Update(){
	RenderComponent::Update();
	RenderBoundingBox((allObjs["box"]));
}