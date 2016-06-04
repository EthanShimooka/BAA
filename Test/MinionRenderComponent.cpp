#include "MinionRenderComponent.h"


MinionRenderComponent::MinionRenderComponent(GameObject* minion, int team){
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"),-1, 0, 0);
	allObjs["base"] = objRef;
	allObjs["leftArm"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2011, -90, 114);
	allObjs["leftArm"]->setAnchor(0.727, 0.8378);
	allObjs["leftArm"]->setRotation(-20);
	allObjs["leftArm"]->setScale(0.6f);
	allObjs["rightArm"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2012, 90, 114);
	allObjs["rightArm"]->setAnchor(0.272, 0.8378);
	allObjs["rightArm"]->setRotation(20);
	allObjs["rightArm"]->setScale(0.6f);
	if (team == TEAM_YELLOW){
		if (konamiUnlocked)allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2030, 0, 0);
		else allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2010, 0, 0);
	}
	else{
		if (konamiUnlocked)allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2031, 0, 0);
		else allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2009, 0, 0);
	}
	allObjs["body"]->setParent(allObjs["base"]);

	allObjs["leftArm"]->setParent(allObjs["body"]);
	allObjs["rightArm"]->setParent(allObjs["body"]);
	allObjs["body"]->setScale(allObjs["body"]->calcXScale(30));
	
	
}


MinionRenderComponent::~MinionRenderComponent()
{
}

void MinionRenderComponent::Update(){
	RenderComponent::Update();
	//if(gameObjectRef->isAlive)RenderBoundingBox((allObjs["box"]));
	///else{
	//	allObjs["box"]->visible = false;
	//}
	if (RenderManager::getRenderManager()->flippedScreen)allObjs["base"]->rotation = 180;
}