#include "MidBirdRenderComponent.h"


MidBirdRenderComponent::MidBirdRenderComponent(GameObject * bird)
{
	gameObjectRef = bird;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);

	buildAnimation();
	setAnimation("idle");

}


MidBirdRenderComponent::~MidBirdRenderComponent()
{
	for (auto i : animations){
		delete i.second;
	}
}

void MidBirdRenderComponent::buildAnimation(){

	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	
	allObjs["base"] = objRef;


	allObjs["rightArm"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2203, 250, 0);
	allObjs["rightArm"]->setAnchor(0.272, 0.8378);
	allObjs["rightArm"]->setRotation(20);
	//allObjs["rightArm"]->setScale(0.6f);

	allObjs["leftArm"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2206, 130, -20);
	allObjs["leftArm"]->setAnchor(0.727, 0.8378);
	allObjs["leftArm"]->setRotation(-20);
	allObjs["leftArm"]->setScale(0.9f);

	allObjs["body"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2200, 0, 0);
	allObjs["body"]->setScale(0.2f);
	allObjs["body"]->setParent(allObjs["base"]);




	allObjs["yellowFlag"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2204, 250, -290);
	allObjs["yellowFlag"]->setAnchor(0.727, 0.8378);
	allObjs["yellowFlag"]->setRotation(-20);
	allObjs["yellowFlag"]->visible = true;


	allObjs["purpleFlag"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2205, 250, -290);
	allObjs["purpleFlag"]->setAnchor(0.727, 0.8378);
	allObjs["purpleFlag"]->setRotation(-20);
	allObjs["purpleFlag"]->visible = false;

	allObjs["mlg"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2201, 200, -290);
	allObjs["mlg"]->setAnchor(0.727, 0.8378);
	allObjs["mlg"]->setRotation(-20);

	allObjs["leftArm"]->setParent(allObjs["body"]);
	allObjs["rightArm"]->setParent(allObjs["body"]);
	allObjs["yellowFlag"]->setParent(allObjs["rightArm"]);
	allObjs["purpleFlag"]->setParent(allObjs["rightArm"]);
	allObjs["mlg"]->setParent(allObjs["body"]);
	


	///////////////////////////////////////////////////////////////////////

	std::list<motion> motions;


	//motions.push_back(makeMotion(rotateTransform(allObjs["body"], 0, -20), 0, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["body"], 0,  -10), 0.0, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["body"], 0,  10), 0.5, 0.5, ease_QuadInOut));
	//motions.push_back(makeMotion(rotateTransform(allObjs["mlg"], 0, 10), 0.0, 0.5, ease_QuadInOut));
	//motions.push_back(makeMotion(rotateTransform(allObjs["mlg"], 0, -10), 0.5, 0.5, ease_QuadInOut));
	//motions.push_back(makeMotion(moveLinearX(allObjs["mlg"], -0, 5), 0, 1));

	motions.push_back(makeMotion(rotateTransform(allObjs["leftArm"], 0, 10), 0.0, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["leftArm"], -10, 0), 0.5, 0.5, ease_QuadInOut));


	animations["idle"] = new Animation(800, motions);

	std::list<motion> motions2;
	motions2.push_back(makeMotion(rotateTransform(allObjs["body"], -20, 0), 0, 1));
	animations["idle2"] = new Animation(400, motions2);


	std::list<motion> motions3;
	motions3.push_back(makeMotion(rotateTransform(allObjs["rightArm"], 0, 50), 0, 1));
	animations["lower"] = new Animation(800, motions3);

}


void MidBirdRenderComponent::animationLogic(){

	int purpleHealth = Stats::baseHealth_purple();
	int yellowHealth = Stats::baseHealth_yellow();


	if ((flagUp == 2 || flagUp == 0) && (purpleHealth > yellowHealth)){
		//setAnimation("lower");
		std::cout << "shiggle" << std::endl;
		allObjs["purpleFlag"]->visible = false;
		allObjs["yellowFlag"]->visible = true;
		flagUp = 1;
	}
	if ((flagUp == 1 || flagUp == 0) && (purpleHealth < yellowHealth)){
		//setAnimation("lower");
		std::cout << "shiggle" << std::endl;
		allObjs["purpleFlag"]->visible = true;
		allObjs["yellowFlag"]->visible = false;
		flagUp = 2;

	}

}


void MidBirdRenderComponent::Update(){

	RenderComponent::Update();
	RenderComponent::animate();
	animationLogic();

}