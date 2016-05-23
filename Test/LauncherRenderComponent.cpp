#include "LauncherRenderComponent.h"


LauncherRenderComponent::LauncherRenderComponent(GameObject * launcher, int team)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	buildAnimation();
	setAnimation("idle");

}

void LauncherRenderComponent::buildAnimation(){

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	//base->toggleIfRenderImage();
	SDLRenderObject * launcher1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2026, 0, 600);
	SDLRenderObject * launcher2 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2027, 0, 600);


	allObjs["base"] = objRef;
	allObjs["launcher1"] = launcher1;
	allObjs["launcher1"]->visible = true;

	allObjs["launcher2"] = launcher2;
	allObjs["launcher2"]->visible = false;


	launcher1->setParent(objRef);
	launcher2->setParent(objRef);
	launcher1->setAnchor(0.5f, 1.0f);
	launcher2->setAnchor(0.5f, 1.0f);


	std::list<motion> motions;
	animations["idle"] = new Animation(100, motions);


	std::list<motion> motions2;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions2.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -10, 10), 0, 1));
	}
	else{

		motions2.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -10, 10), 0, 1));
	}
	animations["throw"] = new Animation(400, motions2);
	

	std::list<motion> motions3;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions3.push_back(makeMotion(moveLinearY(allObjs["launcher1"], 450, 0), 0, 1));

	}
	else{

		motions3.push_back(makeMotion(moveLinearY(allObjs["launcher1"], 450, 0), 0, 1));
	}


	animations["show"] = new Animation(800, motions3);

	std::list<motion> motions4;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions4.push_back(makeMotion(moveLinearY(allObjs["launcher1"], 0, 450), 0, 1));
	}
	else{

		motions4.push_back(makeMotion(moveLinearY(allObjs["launcher1"], 0, 450), 0, 1));
	}

	animations["hide"] = new Animation(400, motions4);

	std::list<motion> motions5;
	animations["idle"] = new Animation(100, motions5);


	if (gameObjectRef->team == TEAM_PURPLE){
		motions5.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 0, 0), 0, 1));
	}
	else{

		motions5.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 0, -10), 0, 1));
	}
	animations["windback"] = new Animation(400, motions5);




}

void LauncherRenderComponent::showLauncher(){
	setAnimation("show");
	setNextAnimation("idle");
}

void LauncherRenderComponent::hideLauncher(){
	setAnimation("hide");
	setNextAnimation("idle");


}

void LauncherRenderComponent::throwLauncher(){
	setAnimation("throw");
	setNextAnimation("hide");
	setNextAnimation("idle");
	std::cout << "SHIGGLE BUZZ BUZZ" << std::endl;

}

LauncherRenderComponent::~LauncherRenderComponent(){
	for (auto i : animations){
		delete i.second;
	}
}


void LauncherRenderComponent::Update(){
	RenderComponent::Update();
	RenderComponent::animate();
}