#include "MinionRenderComponent.h"


MinionRenderComponent::MinionRenderComponent(GameObject* minion, int team){
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	if (team == 1){
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2010, 0, 0);
		allObjs["base"] = objRef;
	}
	else if (team == 2){
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2011, 0, 0);
		allObjs["base"] = objRef;
	}	else{
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2010, 0, 0);
		allObjs["base"] = objRef;
	}
	SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 10, 10);
	box->setIfRenderRect(true);
	allObjs["box"] = box;
}


MinionRenderComponent::~MinionRenderComponent()
{
}

void MinionRenderComponent::Update(){
	RenderComponent::Update();
	if(gameObjectRef->isAlive)RenderBoundingBox((allObjs["box"]));
	else{
		allObjs["box"]->visible = false;
	}
}