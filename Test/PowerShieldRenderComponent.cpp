#include "PowerShieldRenderComponent.h"


PowerShieldRenderComponent::PowerShieldRenderComponent(GameObject* shield)
{
	/// Set GameObject to "shield" argument
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderComponent::RenderComponent();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	//base->toggleIfRenderImage();
	SDLRenderObject * shield1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4003, 0 , 0);

	allObjs["base"] = objRef;
	allObjs["shield"] = shield1;
	allObjs["shield"]->visible = true;
	allObjs["shield"]->setScale(0.4f);

	shield1->setParent(objRef);

    shield1->setAnchor(0.5f, 1.0f);

}


PowerShieldRenderComponent::~PowerShieldRenderComponent()
{
}

void PowerShieldRenderComponent::Update()
{
	RenderComponent::Update();

}