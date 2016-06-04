#include "FanRenderComponent.h"


FanRenderComponent::FanRenderComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	buildAnimations();

	setAnimation("idle");


}


void FanRenderComponent::buildAnimations(){

	RenderComponent::RenderComponent();
	SceneManager* sceneMan = SceneManager::GetSceneManager();

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	
	SDLRenderObject * arm;

	if (japeUnlocked) arm = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2209, 0, 0);
	else arm = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2003, 0, 0);


	allObjs["base"] = objRef;
	allObjs["arm"] = arm;
	allObjs["arm"]->visible = true;
	allObjs["arm"]->setScale(.70f);
	arm->setParent(objRef);
	arm->setAnchor(0.5f, 0.5f);
	
	std::list<motion> motions;

	if (gameObjectRef->team == TEAM_PURPLE){
		motions.push_back(makeMotion(rotateTransform(allObjs["arm"], 0, 360), 0, 1));
	}
	else{
	
		motions.push_back(makeMotion(rotateTransform(allObjs["arm"], 0, -360), 0, 1));
	}
	animations["idle"] = new Animation(800, motions);
}



FanRenderComponent::~FanRenderComponent(){
	/*for (auto i : animations){
		delete i.second;
	}*/
}

void FanRenderComponent::Update() {
	RenderComponent::Update();
	RenderComponent::animate();
}