#include "PlayerRenderComponent.h"


PlayerRenderComponent::PlayerRenderComponent()
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 0, 0, 0);
	base->unrender();
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 100103, 0, 0);
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 100105, 30, 300);
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 100101, 0, 0);
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 100104, 50, 300);
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 100102, 0, 0);
	//objRef->setAnchor(0.5, 0.5);
	
	armR->setAnchor(174 / double(armR->renderRect.w), 154 / double(armR->renderRect.h));
	armL->setAnchor(178 / double(armL->renderRect.w), 168 / double(armL->renderRect.h)); 
	legR->setAnchor(128 / double(legR->renderRect.w),  39 / double(legR->renderRect.h));
	legL->setAnchor(253 / double(legL->renderRect.w),  62 / double(legL->renderRect.h));

	body->setParent(base);
	armL->setParent(body);
	armR->setParent(body);
	legL->setParent(body);
	legR->setParent(body);
	body->setScale(0.1);
	objRef = base;
	allObjs.push_back(base);
	allObjs.push_back(body);
	allObjs.push_back(legL);
	allObjs.push_back(legR);
	allObjs.push_back(armL);
	allObjs.push_back(armR);
}


PlayerRenderComponent::~PlayerRenderComponent()
{
}

void PlayerRenderComponent::Update(){
	RenderComponent::Update();
}


