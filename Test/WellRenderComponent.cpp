
#include "WellRenderComponent.h"


WellRenderComponent::WellRenderComponent(GameObject * well, int team)
{
	gameObjectRef = well;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	auto wellObj = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2110, 0, 0);
	wellObj->setParent(objRef);
	if (team == TEAM_PURPLE){
		wellObj->setRotation(180);
	}

}


WellRenderComponent::~WellRenderComponent()
{
}

void WellRenderComponent::Update() {
	RenderComponent::Update();
}

