#include "TurkeyClassComponent.h"


TurkeyClassComponent::TurkeyClassComponent(GameObject* player)
{
	ClassComponent::ClassComponent();
	//speed = 15;
	//width = 1.33f;
	//height = 1.35f;
	//seedRequired = 5;
	//featherSpeed = 1.0f / 7.0f;
	//featherWidth = 1;
	//featherHeight = 1;
	//abilityCooldown = 15;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_CLASS, this);
}


TurkeyClassComponent::~TurkeyClassComponent()
{
}

void TurkeyClassComponent::Update()
{
}

void TurkeyClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations)
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 0, 0, 0);
	base->toggleIfRenderImage();
	int bodyAX = 107;
	int bodyAY = 100;
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3502, (float)(175 - bodyAX), (float)(78 - bodyAY));
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3504, (float)(127 - bodyAX), (float)(114 - bodyAY));
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3500, 0, -8);
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3503, (float)(96 - bodyAX), (float)(128 - bodyAY));
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3501, (float)(81 - bodyAX), (float)(83 - bodyAY));

	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 


	//objRef->setAnchor(0.5, 0.5);
	body->setAnchor(bodyAX / double(body->renderRect.w), bodyAY / double(body->renderRect.h));
	armR->setAnchor(21 / double(armR->renderRect.w), 12 / double(armR->renderRect.h));
	armL->setAnchor(15 / double(armL->renderRect.w), 14 / double(armL->renderRect.h));
	legR->setAnchor(23 / double(legR->renderRect.w), 17 / double(legR->renderRect.h));
	legL->setAnchor(23 / double(legL->renderRect.w), 18 / double(legL->renderRect.h));
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
	//motions.push_back(makeMotion(moveCircArc(armR, 0, 50, 50, 0, 360), 0, 1));
	//motions.push_back(makeMotion(moveCircArc(armL, 0, 50, 50, 180, 360), 0, 1));
	//motions.push_back(makeMotion(moveCircArc(legR, 0, 0, 0, 0, 0), 0, 0));
	//motions.push_back(makeMotion(moveCircArc(legR, 0, 0, 0, 0, 0), 0, 0));
	Animation* idle = new Animation(400, motions);
	animations["idle"] = idle;
	//auto mot = idle.motions.begin();
	//currentAnimation = idle;
	////// WALKING ANIMATION 
	std::list<motion> motions2;
	motions2.push_back(makeMotion(moveEllipseArc(legR, (float)(96 - bodyAX), (float)(128 - bodyAY), 14, 2, 180, 360), 0, 1));
	motions2.push_back(makeMotion(moveEllipseArc(legL, (float)(127 - bodyAX), (float)(114 - bodyAY), 14, 2, 0, 360), 0, 1));
	motions2.push_back(makeMotion(moveEllipseArc(body, 0, -8, 4, 1, 90, 360), 0, 1));
	motions2.push_back(makeMotion(rotateTransform(legR, 10, -20), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legR, -10, 20), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, -10, 20), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, 10, -20), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(armL, -10, 20), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(armL, 10, -20), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(armR, 10, -20), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(armR, -10, 20), 0.5, 0.5, ease_QuadInOut));
	//motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0.5, 0.5, ease_QuadIn));
	animations["walk"] = new Animation(400, motions2);
}

int TurkeyClassComponent::useAbility(){
	std::cout << "turkeyclasscomp->useAbility() not implemented yet" << std::endl;
	return false;
}