#include "PeacockClassComponent.h"

//Does not compile, not sure why it doesn't

PeacockClassComponent::PeacockClassComponent(GameObject* player)
{
	ClassComponent::ClassComponent();
	//speed = 10000;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_CLASS, this);
}


PeacockClassComponent::~PeacockClassComponent()
{
}

void PeacockClassComponent::Update()
{
}

void PeacockClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations){

	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 0, 0, 0);
	base->toggleIfRenderImage();
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3102, 48 - 24, 85 - 92);
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3104, 25 - 24, 109 - 92);
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3103, 33 - 24, 118 - 92);
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3100, 0, 0);
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3101, 31 - 24, 95 - 92);

	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 


	//objRef->setAnchor(0.5, 0.5);
	body->setAnchor(24 / double(body->renderRect.w), 92 / double(body->renderRect.h));
	armR->setAnchor(77 / double(armR->renderRect.w), 9 / double(armR->renderRect.h));
	armL->setAnchor(77 / double(armL->renderRect.w), 9 / double(armL->renderRect.h));
	legR->setAnchor(8 / double(legR->renderRect.w), 6 / double(legR->renderRect.h));
	legL->setAnchor(7 / double(legL->renderRect.w), 7 / double(legL->renderRect.h));
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
	motions.push_back(makeMotion(rotateTransform(armL, 0, 10), 0, 0.5));
	motions.push_back(makeMotion(rotateTransform(armL, 10, -10), 0.5, 0.5));
	motions.push_back(makeMotion(rotateTransform(armR, 0, 10), 0, 0.5));
	motions.push_back(makeMotion(rotateTransform(armR, 10, -10), 0.5, 0.5));
	motions.push_back(makeMotion(rotateTransform(legR, 0, 0), 0, 0));
	motions.push_back(makeMotion(rotateTransform(legL, 0, 0), 0, 0));
	Animation* idle = new Animation(800, motions);
	animations["idle"] = idle;
	//auto mot = idle.motions.begin();
	//currentAnimation = idle;
	////// WALKING ANIMATION 
	std::list<motion> motions2;
	motions2.push_back(makeMotion(moveCircArc(armR, 0, 5, 5, 0, 360), 0, 1));
	motions2.push_back(makeMotion(moveCircArc(armL, 0, 5, 5, 180, 360), 0, 1));
	motions2.push_back(makeMotion(rotateTransform(armL, 0, 10), 0, 0.5));
	motions2.push_back(makeMotion(rotateTransform(armL, 10, -10), 0.5, 0.5));
	motions2.push_back(makeMotion(rotateTransform(armR, 0, 10), 0, 0.5));
	motions2.push_back(makeMotion(rotateTransform(armR, 10, -10), 0.5, 0.5));
	motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legR, 30, -60), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, 30, -60), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, -30, 60), 0.5, 0.5, ease_QuadInOut));
	//motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0.5, 0.5, ease_QuadIn));
	animations["walk"] = new Animation(800, motions2);


}
