#include "MidBaseRenderComponent.h"

void MidBaseRenderComponent::buildBody(int team){
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	int bodyID = team == TEAM_YELLOW ? 2015 : 2016;
	int hairID = team == TEAM_YELLOW ? 2024 : 2025;
	//objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 9991, 0, 0);
	float bodyAX = 2144 / 2144;//if the base image is resized, change first number: (width/2144) and (height/1190)
	float bodyAY = 1190 / 1190;
	float headAX = 1133 / 1133; //(headwidth/2144) and (headheight/1190)
	float headAY = 1499 / 1499;

	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), -1, 0, 0);
	SDLRenderObject * tail = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2022, (121 - 1072) * bodyAX, (489 - 595) * bodyAY);
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), bodyID, 0, 100 * bodyAY);
	SDLRenderObject * nest = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2017, 0, (1193 - 595)* bodyAY);
	SDLRenderObject * head = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2018, (1408 - 1072) * bodyAX, (404 - 595) * bodyAY);
	SDLRenderObject * hair = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), hairID, (1074 - 1133 * 0.413f)*headAX, (375 - 1499 * 0.737f) * headAY);
	SDLRenderObject * beak_bot = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2021, (879 - 1133 * 0.413f) * headAX, (582 - 1499 * 0.737f) * headAY);
	SDLRenderObject * beak_top = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2020, (768 - 1133 * 0.413f) * headAX, (624 - 1499 * 0.737f) * headAY);
	SDLRenderObject * eye = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2019, (732 - 1133 * 0.413f) * headAX, (333 - 1499 * 0.737f) * headAY);
	SDLRenderObject * arm = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 2023, (874 - 1072) * bodyAX, (506 - 595) * bodyAY);

	body->setAnchor(0.5, 0.5);
	tail->setAnchor(0.813, 0.821);
	nest->setAnchor(0.5, 0.5);
	hair->setAnchor(0.682, 0.882);
	head->setAnchor(0.413, 0.737);
	arm->setAnchor(0.717, 0.815);
	eye->setAnchor(0.5, 0.5);
	beak_top->setAnchor(0.0, 1.0);
	beak_bot->setAnchor(0.176, 0.25);


	body->setScale(body->calcXScale(300));
	body->setParent(objRef);
	head->setParent(body);
	nest->setParent(body);
	tail->setParent(body);
	arm->setParent(body);
	hair->setParent(head);
	eye->setParent(head);
	beak_top->setParent(head);
	beak_bot->setParent(head);

	SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 10, 10);
	//box->setIfRenderRect(true);
	allObjs["box"] = box;
	allObjs["base"] = objRef;

	allObjs["body"] = body;
	allObjs["nest"] = nest;
	allObjs["hair"] = hair;
	allObjs["arm"] = arm;
	allObjs["eye"] = eye;
	allObjs["head"] = head;
	allObjs["beak_bot"] = beak_bot;
	allObjs["beak_top"] = beak_top;
	allObjs["tail"] = tail;
}
void MidBaseRenderComponent::buildAnimations(){
std::list<motion> motions;
	motions.push_back(makeMotion(rotateTransform(allObjs["arm"], 0, 360), 0, 1));
	motions.push_back(makeMotion(rotateTransform(allObjs["eye"], 0, -360), 0, 1));
	motions.push_back(makeMotion(rotateTransform(allObjs["head"], -10, 20), 0, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["head"], 10, -20), 0.5, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["beak_bot"], 20, -40), 0, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["beak_bot"], -20, 40), 0.5, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["tail"], 20, -40), 0, 0.5, ease_QuadInOut));
	motions.push_back(makeMotion(rotateTransform(allObjs["tail"], -20, 40), 0.5, 0.5, ease_QuadInOut));
	animations["idle"] = new Animation(800, motions);

}
MidBaseRenderComponent::MidBaseRenderComponent(GameObject * base, int team)
{

	gameObjectRef = base;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	buildBody(team);
	
	buildAnimations();

	setAnimation("idle");
	
}


MidBaseRenderComponent::~MidBaseRenderComponent(){
	for (auto i : animations){
		delete i.second;
	}
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef->setVisible(false);
	sceneMan->RemoveObject(objRef, sceneMan->findLayer("layer1"));
}

void MidBaseRenderComponent::Update(){
	RenderComponent::Update();
	//RenderBoundingBox((allObjs["box"]));
	RenderComponent::animate();

}