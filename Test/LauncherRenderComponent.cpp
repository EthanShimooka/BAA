#include "LauncherRenderComponent.h"


LauncherRenderComponent::LauncherRenderComponent(GameObject * launcher, int team)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2026, 0, 0);
	objRef->isVisible = false;
	allObjs["launcher"] = objRef;
}


LauncherRenderComponent::~LauncherRenderComponent()
{
}



void LauncherRenderComponent::Update(){
	RenderComponent::Update();
}