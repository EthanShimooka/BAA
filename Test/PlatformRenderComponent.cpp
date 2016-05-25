
#include "PlatformRenderComponent.h"


PlatformRenderComponent::PlatformRenderComponent(GameObject* platform, int team){
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	SDLRenderObject * plat;

	//objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 9991, 0, 0);
	if (team == 1){
	//	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2013, 0, 0);
		plat = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2013, 0, 0);

	} else{
	// objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2014, 0, 0);
	    plat = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2014, 0, 0);
	}
	
	allObjs["base"] = objRef;
	allObjs["plat"] = plat;

	allObjs["plat"]->setScale(0.25f);
	plat->setParent(objRef);

}


PlatformRenderComponent::~PlatformRenderComponent()
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef->setVisible(false);
	sceneMan->RemoveObject(objRef, sceneMan->findLayer("layer2"));
}

void PlatformRenderComponent::Update(){
	RenderComponent::Update();
}