#include "LauncherRenderComponent.h"


LauncherRenderComponent::LauncherRenderComponent(GameObject * launcher, int team)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 12, 0, 0);

}


LauncherRenderComponent::~LauncherRenderComponent()
{
}


void LauncherRenderComponent::Update(){
	RenderComponent::Update();
}