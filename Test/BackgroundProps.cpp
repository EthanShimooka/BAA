#include "BackgroundProps.h"


BackgroundProps::BackgroundProps()
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	objRef = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), -1, 0, 0);
	//Planets
	allObjs["planet1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2105, 0.0f, -200.0f, 400.0f);
	allObjs["planet1"]->setScale(20);
	allObjs["planet2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2104, 80000.0f, 0.0f, 4000.0f);
	allObjs["planet2"]->setScale(200);
	allObjs["planet3"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2103, -80000.0f, 40000.0f, 4000.0f);
	allObjs["planet3"]->setScale(200);

	//Clouds
	allObjs["cloudB1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2106, 0.0f, 25000.0f, 4000.1f);
	allObjs["cloudB1"]->setScale(300);
	allObjs["cloudT1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2106, 0.0f, -25000.0f, 4000.1f);
	allObjs["cloudT1"]->setScale(300);
	allObjs["cloudT1"]->setRotation(180);
	allObjs["cloudB2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2107, 0.0f, 1400.0f, 300.0f);
	allObjs["cloudB2"]->setScale(25);
	allObjs["cloudT2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2107, 0.0f, -1400.0f, 300.0f);
	allObjs["cloudT2"]->setScale(25);
	allObjs["cloudT2"]->setRotation(180);

	//Boids
	allObjs["boidB1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2108, 3250.0f, 2200.0f, 99.9f);
	allObjs["boidB1"]->setScale(1);
	allObjs["boidB2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2109, 1200.0f, 2000.0f, 99.9f);
	allObjs["boidB2"]->setScale(1);
	allObjs["boidB2"]->setFlippedH(true);
	allObjs["boidB3"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2108, -1500.0f, 2100.0f, 99.9f);
	allObjs["boidB3"]->setScale(1);
	allObjs["boidB3"]->setFlippedH(true);
	allObjs["boidB4"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2109, -3400.0f, 2200.0f, 99.9f);
	allObjs["boidB4"]->setScale(1);

	allObjs["boidT1"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2108, -3250.0f, -2200.0f, 99.9f);
	allObjs["boidT1"]->setScale(1);
	allObjs["boidT1"]->setFlippedV(true);
	allObjs["boidT2"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2109, -1200.0f, -2000.0f, 99.9f);
	allObjs["boidT2"]->setScale(1);
	allObjs["boidT2"]->setFlippedH(true);
	allObjs["boidT2"]->setFlippedV(true);
	allObjs["boidT3"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2108, 1500.0f, -2100.0f, 99.9f);
	allObjs["boidT3"]->setScale(1);
	allObjs["boidT3"]->setFlippedH(true);
	allObjs["boidT3"]->setFlippedV(true);
	allObjs["boidT4"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2109, 3400.0f, -2200.0f, 99.9f);
	allObjs["boidT4"]->setScale(1);
	allObjs["boidT4"]->setFlippedV(true);
	//cloudT2->setRotation(180);

	//Protein Mountain


	//Beaches

	allObjs["beachB"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2101, 0.0f, 2200.0f, 100.0f);
	allObjs["beachT"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2101, 0.0f, -2200.0f, 100.0f);
	allObjs["surfB"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2102, 0.0f, 0.0f, 0.0f);
	allObjs["surfT"] = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 2102, 0.0f, 0.0f, 0.0f);
	allObjs["beachB"]->setScale(6);
	allObjs["beachT"]->setScale(6);
	allObjs["surfB"]->setParent(allObjs["beachB"]);
	allObjs["surfT"]->setParent(allObjs["beachT"]);
	allObjs["beachT"]->setRotation(180);
	std::list<motion> surfMotions;
	surfMotions.push_back(makeMotion(transformFlipH(allObjs["surfB"], false), 0.0, 0.0));
	surfMotions.push_back(makeMotion(transformFlipH(allObjs["surfT"], false), 0.0, 0.0));
	surfMotions.push_back(makeMotion(moveLinearY(allObjs["surfB"], -21, -6), 0, 0.5));
	surfMotions.push_back(makeMotion(moveLinearY(allObjs["surfT"], -21, -6), 0, 0.5));
	surfMotions.push_back(makeMotion(transformFlipH(allObjs["surfB"], true), 0.5, 0.5));
	surfMotions.push_back(makeMotion(transformFlipH(allObjs["surfT"], true), 0.5, 0.5));
	surfMotions.push_back(makeMotion(moveLinearY(allObjs["surfB"], -21, -6), 0.5, 1.0));
	surfMotions.push_back(makeMotion(moveLinearY(allObjs["surfT"], -21, -6), 0.5, 1.0));
	animations["surf"] = new Animation(1000, surfMotions);
	setAnimation("surf");
}


BackgroundProps::~BackgroundProps()
{
	//delete surf;
	allObjs.clear();
	animations.clear();

}

void BackgroundProps::Update(){
	//RenderComponent::Update();
	RenderComponent::animate();
	//runWater->animate(float(aniCounter) / 100);
	//surf->animate(float(aniCounter) / 100);
	//aniCounter++;
	//aniCounter = aniCounter % 100;

}
void LoadBackgroundProps(){
	GameObject* objBase = new GameObject();
	objBase->isAlive = true;
	objBase->type = GAMEOBJECT_TYPE::OBJECT_PARTICLE;
	objBase->setPos(0, 0);

	BackgroundProps* rend = new BackgroundProps();
	objBase->AddComponent(COMPONENT_RENDER, rend);
	rend->gameObjectRef = objBase;
	GameObjects.AddObject(objBase);
}