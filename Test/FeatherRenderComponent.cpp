#include "FeatherRenderComponent.h"

FeatherRenderComponent::FeatherRenderComponent(GameObject* feather){
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	if (feather->team == 1){
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 8000, 0, 0);
	}
	else{
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 8001, 0, 0);

	}
	objRef->setScale(0.25f);

	objRef->setAnchor(1.0, 0.54);
	allObjs["base"] = objRef;

	SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 10, 10);
	//box->setIfRenderRect(true);
	allObjs["box"] = box;

}


FeatherRenderComponent::~FeatherRenderComponent()
{
}

void FeatherRenderComponent::Update(){
	RenderComponent::Update();
	if(gameObjectRef->isAlive)RenderBoundingBox((allObjs["box"]));
	else{
		allObjs["box"]->visible = false;
	}
}