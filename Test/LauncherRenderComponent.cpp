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
	SDLRenderObject * launcher1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2026, -300, -600);
	SDLRenderObject * launcher2 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2027, -300, -600);
	SDLRenderObject * launcher3 = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2029, 30, -25);


	allObjs["base"] = objRef;
	allObjs["launcher1"] = launcher1;
	allObjs["launcher1"]->visible = true;
	allObjs["launcher1"]->setScale(0.8f);
	
	allObjs["launcher2"] = launcher2;
	allObjs["launcher2"]->setScale(0.8f);
	allObjs["launcher2"]->visible = false;
	
	allObjs["launcher3"] = launcher3;
	allObjs["launcher3"]->setScale(0.25f);
	allObjs["launcher3"]->visible = true;

	launcher1->setParent(objRef);
	launcher2->setParent(objRef);
	launcher3->setParent(objRef);
	launcher1->setAnchor(0.5f, 1.0f);
	launcher2->setAnchor(0.5f, 1.0f);
	////////////////////////////////////////////


	std::list<motion> motions;
	animations["idle"] = new Animation(100, motions);

	////////////////////////////////////////////


	std::list<motion> motions2;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions2.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -10, 10), 0, 1));
	}
	else{

		motions2.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -10, 10), 0, 1));
	}
	animations["throw"] = new Animation(400, motions2);
	
	////////////////////////////////////////////

	std::list<motion> motions3;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions3.push_back(makeMotion(moveLinearY(allObjs["launcher1"], 450, 0), 0, 1));

	}
	else{
		motions3.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 20, -20), 0, 1));
		motions3.push_back(makeMotion(moveLinearXY(allObjs["launcher1"], -450, -450, -250 , 100), 0, 1));
		motions3.push_back(makeMotion(rotateTransform(allObjs["launcher2"], 20, -20), 0, 1));
		motions3.push_back(makeMotion(moveLinearXY(allObjs["launcher2"], -450, -450, -250, 100), 0, 1));
	}
	animations["show"] = new Animation(200, motions3);

	///////////

	std::list<motion> motions4;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions4.push_back(makeMotion(moveLinearY(allObjs["launcher1"], 0, -450), 0, 1));
	}
	else{
		motions4.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -20, 20), 0, 1));
		motions4.push_back(makeMotion(moveLinearXY(allObjs["launcher1"], -250, 100, -450, -450), 0, 1));
		motions4.push_back(makeMotion(rotateTransform(allObjs["launcher2"], -20, 20), 0, 1));
		motions4.push_back(makeMotion(moveLinearXY(allObjs["launcher2"], -250, 100, -450, -450), 0, 1));
	}

	animations["hide"] = new Animation(200, motions4);

	///////////
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
	//std::cout << "SHIGGLE BUZZ BUZZ" << std::endl;

	//allObjs["launcher1"]->visible = false;
	//allObjs["launcher2"]->visible = true;

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