
#include "PlatformRenderComponent.h"


PlatformRenderComponent::PlatformRenderComponent(GameObject* platform, int team){
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	SceneManager* sceneMan = SceneManager::GetSceneManager();

	//objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 9991, 0, 0);
	if (team == 1){
		objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2013, 0, 0);
	} else{
	 objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2014, 0, 0);

	}
	
	allObjs["base"] = objRef;
}


PlatformRenderComponent::~PlatformRenderComponent()
{
}

void PlatformRenderComponent::Update(){
	RenderComponent::Update();
}