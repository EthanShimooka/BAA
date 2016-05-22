#include "LauncherRenderComponent.h"


LauncherRenderComponent::LauncherRenderComponent(GameObject * launcher, int team)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	buildAnimation();
	setAnimation("throw");

}

void LauncherRenderComponent::buildAnimation(){

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	//base->toggleIfRenderImage();
	SDLRenderObject * launcher1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2026, 0, 0);
	SDLRenderObject * launcher2 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2027, 0, 0);


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


	if (gameObjectRef->team == TEAM_PURPLE){
		motions.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 0 , 0), 0, 1));
	}
	else{

		motions.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 0, -10), 0, 1));
	}
	animations["windback"] = new Animation(400, motions);

	std::list<motion> motions2;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 0, 0), 0, 1));
	}
	else{

		motions.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -10, 10), 0, 1));
	}
	animations["throw"] = new Animation(400, motions2);
	

	std::list<motion> motions3;
	if (gameObjectRef->team == TEAM_PURPLE){
		motions.push_back(makeMotion(rotateTransform(allObjs["launcher1"], 0, 0), 0, 1));
	}
	else{

		motions.push_back(makeMotion(rotateTransform(allObjs["launcher1"], -10, 10), 0, 1));
	}


	animations["show"] = new Animation(400, motions3);





	animations["hide"] = new Animation(400, motions);

}

void LauncherRenderComponent::showLauncher(){
	setAnimation("show");
}

void LauncherRenderComponent::hideLauncher(){
	setAnimation("hide");

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