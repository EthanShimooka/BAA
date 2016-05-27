#include "MineRenderComponent.h"

MineRenderComponent::MineRenderComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	//TODO: change the coordinates to be relative to the player
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	SDLRenderObject * mine1;

		mine1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4000, 0, -0);

	allObjs["base"] = objRef;
	allObjs["mine1"] = mine1;

	allObjs["mine1"]->setScale(0.5f);
	mine1->setParent(objRef);


}

MineRenderComponent::~MineRenderComponent(){
	/*for (auto i = animations.begin(); i != animations.end(); i++){
		delete i->second;
	}*/
}

void MineRenderComponent::Update(){
	RenderComponent::Update();
	if (RenderManager::getRenderManager()->flippedScreen)objRef->rotation = 180;
}