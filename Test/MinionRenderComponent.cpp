#include "MinionRenderComponent.h"


MinionRenderComponent::MinionRenderComponent(GameObject* minion, int team){
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"),-1, 0, 0);
	allObjs["base"] = objRef;
	if (team == 1){
		allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2010, 0, 0);
		allObjs["body"]->setParent(allObjs["base"]);
	}
	else{
		allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2009, 0, 0);
		allObjs["body"]->setParent(allObjs["base"]);
	}
	allObjs["leftArm"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2011, -90, 0);
	allObjs["leftArm"]->setParent(allObjs["body"]);
	//allObjs["leftArm"]->setAnchor(21 / double(armR->renderRect.w), 12 / double(armR->renderRect.h));
	allObjs["rightArm"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2012, 90, 0);
	allObjs["rightArm"]->setParent(allObjs["body"]);
	allObjs["body"]->setScale(allObjs["body"]->calcXScale(40));
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