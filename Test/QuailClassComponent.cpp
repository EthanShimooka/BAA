#include "QuailClassComponent.h"


QuailClassComponent::QuailClassComponent(GameObject* player)
{
	ClassComponent::ClassComponent();
	speed += 3;
	//width = 1.33f;
	//height = 1.35f;
	//seedRequired = 5;
	//featherSpeed = 1.0f / 7.0f;
	//featherWidth = 1;
	//featherHeight = 1;
	//abilityCooldown = 15;
	seedRequired = 6;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_CLASS, this);
	timerLength = 3;
}

QuailClassComponent::~QuailClassComponent()
{
}

void QuailClassComponent::Update()
{
	ClassComponent::Update();
	if (endTimer()) {
		speed = 19;
	}
}

void QuailClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations)
{
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 0, 0, 0);
	base->toggleIfRenderImage();
	int bodyAX = 71;
	int bodyAY = 50;
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3302, (float)(88 - bodyAX), (float)(66 - bodyAY));
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3304, (float)(79 - bodyAX), (float)(85 - bodyAY));
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3300, 0, -14);
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3303, (float)(70 - bodyAX), (float)(80 - bodyAY));
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3301, (float)(87 - bodyAX), (float)(63 - bodyAY));

	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 


	//objRef->setAnchor(0.5, 0.5);
	body->setAnchor(bodyAX / double(body->renderRect.w), bodyAY / double(body->renderRect.h));
	armR->setAnchor(7 / double(armR->renderRect.w), 7 / double(armR->renderRect.h));
	armL->setAnchor(6 / double(armL->renderRect.w), 18 / double(armL->renderRect.h));
	legR->setAnchor(12 / double(legR->renderRect.w), 7 / double(legR->renderRect.h));
	legL->setAnchor(8 / double(legL->renderRect.w), 6 / double(legL->renderRect.h));
	//armR->setCurrentFrame(1);
	body->setParent(base);
	armL->setParent(body);
	armR->setParent(body);
	legL->setParent(body);
	legR->setParent(body);

	//body->setScale(0.1);
	//body->calcScale(50,50);
	body->setScale(body->calcXScale(70));
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
	motions.push_back(makeMotion(moveCircArc(armR, (float)(87 - bodyAX), (float)(63 - bodyAY), 5, 0, 360), 0, 1));
	motions.push_back(makeMotion(moveCircArc(armL, (float)(87 - bodyAX), (float)(63 - bodyAY), 5, 180, 360), 0, 1));
	motions.push_back(makeMotion(rotateTransform(legR, 0, 0), 0, 0));
	motions.push_back(makeMotion(rotateTransform(legL, 0, 0), 0, 0));
	motions.push_back(makeMotion(rotateTransform(armR, 90, 0), 0, 0));
	motions.push_back(makeMotion(rotateTransform(armL, 90, 0), 0, 0));
	Animation* idle = new Animation(400, motions);
	animations["idle"] = idle;
	//auto mot = idle.motions.begin();
	//currentAnimation = idle;
	////// WALKING ANIMATION 
	std::list<motion> motions2;
	motions2.push_back(makeMotion(rotateTransform(armR, -180, 0), 0, 0));
	motions2.push_back(makeMotion(rotateTransform(armL, -180, 0), 0, 0));
	motions2.push_back(makeMotion(moveCircArc(armR, (float)(66 - bodyAX), (float)(44 - bodyAY), 5, 0, 360), 0, 1));
	motions2.push_back(makeMotion(moveCircArc(armL, (float)(66 - bodyAX), (float)(44 - bodyAY), 5, 180, 360), 0, 1));
	motions2.push_back(makeMotion(rotateTransform(legR, -60, 120), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legR, 60, -120), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, 60, -120), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, -60, 120), 0.5, 0.5, ease_QuadInOut));
	//motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0.5, 0.5, ease_QuadIn));
	animations["walk"] = new Animation(400, motions2);


	////// THROW ANIMATION 
	std::list<motion> motions3;
	//motions3.push_back(makeMotion(keyframeJump(armR, 1), 0.0, 0.0));
	motions3.push_back(makeMotion(rotateTransform(armR, -30, 0), 0.0, 1.0, ease_QuadOut));
	animations["throw"] = new Animation(100, motions3);
	////// CHARGE ANIMATION 
	std::list<motion> motions4;
	motions4.push_back(makeMotion(rotateTransform(armR, -20, 0), 0.0, 0.0));
	animations["charge"] = new Animation(100, motions4);
}

int QuailClassComponent::useAbility(){
	if (currBirdseed >= seedRequired){
		playAbilityUseSound();
		Timing::sInstance.SetQuailAbilityTimer();
		setTimer();
		speed *= 3;
		currBirdseed = 0;
		birdseedFullPlayed = false;
		return true;
	}
	else{
		//not enough birdseed to use power. Maybe play a dry firing sound like how guns make a click when they're empty
		dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->playFailSound();
		return false;
	}
}

int QuailClassComponent::getClass(){
	return CLASS_QUAIL;
}