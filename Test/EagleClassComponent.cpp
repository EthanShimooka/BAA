#include "EagleClassComponent.h"


EagleClassComponent::EagleClassComponent(GameObject* player)
{
	ClassComponent::ClassComponent();
	//width = 1.33f;
	//height = 1.35f;
	//seedRequired = 5;
	//featherSpeed = 1.0f / 7.0f;
	//featherWidth = 1;
	//featherHeight = 1;
	//abilityCooldown = 15;
	seedRequired = 8;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_CLASS, this);
}


EagleClassComponent::~EagleClassComponent()
{
}

void EagleClassComponent::Update()
{
}

void EagleClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations)
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 0, 0, 0);
	base->toggleIfRenderImage();
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100103, 0, 0);
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100105, 30, 300);
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100101, 0, -18);
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100104, 50, 300);
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 100102, 0, 0);

	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 


	//objRef->setAnchor(0.5, 0.5);

	armR->setAnchor(174 / double(armR->renderRect.w), 154 / double(armR->renderRect.h));
	armL->setAnchor(178 / double(armL->renderRect.w), 168 / double(armL->renderRect.h));
	legR->setAnchor(128 / double(legR->renderRect.w), 39 / double(legR->renderRect.h));
	legL->setAnchor(253 / double(legL->renderRect.w), 62 / double(legL->renderRect.h));
	//armR->setCurrentFrame(1);
	body->setParent(base);
	armL->setParent(body);
	armR->setParent(body);
	legL->setParent(body);
	legR->setParent(body);

	//body->setScale(0.1);
	//body->calcScale(50,50);
	body->setScale(body->calcXScale(50));
	//body->setScale(body->calcXScale(90));

	*objRef = base;
	allObjs["base"] = base;
	allObjs["body"] = body;
	allObjs["legL"] = legL;
	allObjs["legR"] = legR;
	allObjs["armL"] = armL;
	allObjs["armR"] = armR;

	SDLRenderObject * box = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 0, 0);
	box->setIfRenderRect(true);
	//box->setParent(base);
	allObjs["box"] = box;
	//SDLRenderObject * name = sceneMan->InstantiateBlankObject(sceneMan->findLayer("layer2"), 0, 0, 0, 0);
	// changing the values in InstantiateBlankObject does not stop the text from being stretched
	// need fixing (to not stretch text to fill box)
	// text, R, G, B, fontsize, fontname

	//std::string playerName = GamerServices::sInstance->GetLocalPlayerName();
	//name->setResourceObject(renderMan->renderText(playerName.c_str(), 200, 0, 200, 20, "BowlbyOneSC-Regular"));
	//name->setParent(base);
	//name->setPos(0, -60);
	//allObjs["name"] = name;

	/////// IDLE ANIMATION
	std::list<motion> motions;
	motions.push_back(makeMotion(moveCircArc(armR, 0, 50, 50, 0, 360), 0, 1));
	motions.push_back(makeMotion(moveCircArc(armL, 0, 50, 50, 180, 360), 0, 1));
	motions.push_back(makeMotion(rotateTransform(legR, 0, 0), 0, 0));
	motions.push_back(makeMotion(rotateTransform(legL, 0, 0), 0, 0));
	Animation* idle = new Animation(400, motions);
	animations["idle"] = idle;
	//auto mot = idle.motions.begin();
	//currentAnimation = idle;
	////// WALKING ANIMATION 
	std::list<motion> motions2;
	motions2.push_back(makeMotion(moveCircArc(armR, 0, 50, 50, 0, 360), 0, 1));
	motions2.push_back(makeMotion(moveCircArc(armL, 0, 50, 50, 180, 360), 0, 1));
	motions2.push_back(makeMotion(rotateTransform(legR, -60, 120), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legR, 60, -120), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, 60, -120), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, -60, 120), 0.5, 0.5, ease_QuadInOut));
	//motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0.5, 0.5, ease_QuadIn));
	animations["walk"] = new Animation(400, motions2);
}

int EagleClassComponent::useAbility(){
	std::cout << "eagleclasscomp->useAbility() not implemented yet" << std::endl;
	return false;
}

int EagleClassComponent::getClass(){
	return CLASS_EAGLE;
}