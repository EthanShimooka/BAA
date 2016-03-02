#include "UIRenderComponent.h"



UIRenderComponent::UIRenderComponent(){
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SDLRenderObject *play = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 19, 0, 0, true);
	objRef = play;
	allObjs.push_back(play);
}

UIRenderComponent::~UIRenderComponent(){
}

void UIRenderComponent::Update(){
	RenderUIComponent::Update();
}
