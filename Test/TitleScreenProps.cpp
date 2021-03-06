#include "TitleScreenProps.h"


TitleScreenProps::TitleScreenProps()
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, 0, 0);
	//Logo
	allObjs["logo"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2112, -20000.0f, -5000.0f, 10000.0f);
	allObjs["logo"]->setScale(300.0f);
	//Planets
	//allObjs["planet1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2105, 0.0f, -200.0f, 400.0f);
	allObjs["planet1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2105, 0.0f, 0.0f, 0.0f);
	allObjs["planet1"]->setScale(1);
	allObjs["planet2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2104, 80000.0f, -20000.0f, 4000.0f);
	//allObjs["planet2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2104, 0.0f, 0.0f, 400.0f);
	allObjs["planet2"]->setScale(200);
	allObjs["planet3"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2103, -80000.0f, 40000.0f, 4000.0f);
	//allObjs["planet3"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2103, 0.0f, 0.0f, 400.0f);
	allObjs["planet3"]->setScale(200);
	allObjs["boid1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2109, 0.0f, -145.0f, 0.0f);
	allObjs["boid1"]->setParent(allObjs["planet2"]);
	allObjs["boid1"]->setScale(0.4);
	allObjs["boid2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2108, 0.0f, -90.0f, 0.0f);
	allObjs["boid2"]->setParent(allObjs["planet1"]);
	allObjs["boid2"]->setScale(0.4);
	allObjs["planet1"]->setParent(allObjs["planet3"]);
	std::list<motion> motions;
	//motions.push_back(makeMotion(transformFlipH(allObjs["surfB"], false), 0.0, 0.0));
	//motions.push_back(makeMotion(transformFlipH(allObjs["surfT"], false), 0.0, 0.0));
	//motions.push_back(makeMotion(moveLinearY(allObjs["surfB"], -21, -6), 0, 0.5));
	motions.push_back(makeMotion(moveEllipseArc(allObjs["planet1"], 0.0f, 0.0f, -250.0f, 800.0f, 0, 360), 0, 1));
	float zDelta = 2500.0f;
	motions.push_back(makeMotion(moveLinearZ(allObjs["planet1"], 0.0f, -zDelta), 0, 0.25, ease_SineOut));
	motions.push_back(makeMotion(moveLinearZ(allObjs["planet1"], -zDelta, 0.0f), 0.25, 0.25, ease_SineIn));
	motions.push_back(makeMotion(moveLinearZ(allObjs["planet1"], 0.0f, zDelta), 0.5, 0.25, ease_SineOut));
	motions.push_back(makeMotion(moveLinearZ(allObjs["planet1"], zDelta, 0.0f), 0.75, 0.25, ease_SineIn));
	motions.push_back(makeMotion(rotateTransform(allObjs["planet1"], 0, 720), 0.0, 1.0));
	motions.push_back(makeMotion(rotateTransform(allObjs["planet2"], 0, 360), 0.0, 1.0));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], false), 0.0, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], true), 0.1, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], false), 0.2, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], true), 0.3, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], false), 0.4, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], true), 0.5, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], false), 0.6, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], true), 0.7, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], false), 0.8, 0.1));
	motions.push_back(makeMotion(transformFlipH(allObjs["boid1"], true), 0.9, 0.1));
	animations["idle"] = new Animation(10000, motions);
	setAnimation("idle");
}


TitleScreenProps::~TitleScreenProps()
{
	allObjs.clear();
	animations.clear();
}

void TitleScreenProps::Update(){
	//RenderComponent::Update();
	RenderComponent::animate();
	//runWater->animate(float(aniCounter) / 100);
	//surf->animate(float(aniCounter) / 100);
	//aniCounter++;
	//aniCounter = aniCounter % 100;

}
GameObject * LoadTitleScreenProps(){
	GameObject* objBase = new GameObject();
	objBase->isAlive = true;
	objBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	objBase->setPos(0, 0);

	TitleScreenProps* rend = new TitleScreenProps();
	objBase->AddComponent(COMPONENT_RENDER, rend);
	rend->gameObjectRef = objBase;
	GameObjects.AddObject(objBase);
	return objBase;
}