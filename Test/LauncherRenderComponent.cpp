#include "LauncherRenderComponent.h"


LauncherRenderComponent::LauncherRenderComponent(GameObject * launcher, int team)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	
	
	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"),0, 0, 0);
	base->toggleIfRenderImage();
	SDLRenderObject * launcher1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2026, -3000, 0,false);
	SDLRenderObject * launcher2 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2027,-3000, 0,false);


	//May need to set a point on the hand to "swing it"

	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 
	//objRef->setAnchor(0.5, 0.5);
	//body->setAnchor(bodyAX / double(body->renderRect.w), bodyAY / double(body->renderRect.h));
	//armR->setAnchor(9 / double(armR->renderRect.w), 7 / double(armR->renderRect.h));

	//armR->setCurrentFrame(1);
	//armR->toggleFlippedH();
	//body->setParent(base);
	//armL->setParent(body);
	//armR->setParent(body);
	//legL->setParent(body);
	//legR->setParent(body);

	//body->setScale(0.1);
	//body->calcScale(50,50);


	//launcher1->setScale(launcher1->calcYScale(50));
	//launcher1->setScale(launcher1->calcXScale(90));

	//launcher2->setScale(launcher2->calcYScale(50));
//	launcher2->setScale(launcher2->calcXScale(90));

	objRef = base;

	allObjs["base"] = base;
	allObjs["launcher1"] = launcher1;
	allObjs["launcher2"] = launcher2;
	allObjs["launcher2"] ->visible = false;
	//allObjs["launcher2"]->visible = false;
	//allObjs["launcher1"]->setVisible(false);
//	allObjs["launcher2"]->setVisible(false);

}


LauncherRenderComponent::~LauncherRenderComponent()
{
}



void LauncherRenderComponent::Update(){
	RenderComponent::Update();
}