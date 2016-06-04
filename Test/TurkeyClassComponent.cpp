#include "TurkeyClassComponent.h"


TurkeyClassComponent::TurkeyClassComponent(GameObject* player)
{
	ClassComponent::ClassComponent();
	speed -= 3;
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
	m_allObjs = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER))->allObjs;
}


TurkeyClassComponent::~TurkeyClassComponent(){
}

void TurkeyClassComponent::Update(){
	ClassComponent::Update();
	if (currBirdseed == seedRequired){
		m_allObjs["ammoIcon1"]->visible = true;
		m_allObjs["ammoIcon2"]->visible = true;
		if (currArmsSpawned >= 1)m_allObjs["ammoIcon1"]->visible = false;
		if (currArmsSpawned >= 2)m_allObjs["ammoIcon2"]->visible = false;
	}
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

	SDLRenderObject * ammoIcon1 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3502, (float)(-60 - bodyAX), (float)(-20 - bodyAY));
	SDLRenderObject * ammoIcon2 = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3502, (float)(-60 - bodyAX), (float)(40 - bodyAY));
	ammoIcon1->visible = false;
	ammoIcon2->visible = false;

	//objRef->setAnchor(0.5, 0.5);
	body->setAnchor(bodyAX / double(body->renderRect.w), bodyAY / double(body->renderRect.h));
	armR->setAnchor(21 / double(armR->renderRect.w), 12 / double(armR->renderRect.h));
	armL->setAnchor(15 / double(armL->renderRect.w), 14 / double(armL->renderRect.h));
	legR->setAnchor(23 / double(legR->renderRect.w), 17 / double(legR->renderRect.h));
	legL->setAnchor(23 / double(legL->renderRect.w), 18 / double(legL->renderRect.h));
	//armR->setCurrentFrame(1);
	body->setParent(base);
	ammoIcon1->setParent(body);
	ammoIcon2->setParent(body);
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
	allObjs["ammoIcon1"] = ammoIcon1;
	allObjs["ammoIcon2"] = ammoIcon2;
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

	////// THROW ANIMATION 
	std::list<motion> motions3;
	//motions3.push_back(makeMotion(keyframeJump(armR, 1), 0.0, 0.0));
	motions3.push_back(makeMotion(rotateTransform(armR, -90, 0), 0.0, 1.0, ease_QuadOut));
	animations["throw"] = new Animation(100, motions3);
	////// CHARGE ANIMATION 
	std::list<motion> motions4;
	motions4.push_back(makeMotion(rotateTransform(armR, 90, 0), 0.0, 0.0));
	animations["charge"] = new Animation(100, motions4);
}

void TurkeyClassComponent::readNetAbility(InputMemoryBitStream& aPacket){
	uint64_t PID;
	//uint64_t owner;
	//int classEnum;
	float destX, destY;
	//int team;
	aPacket.Read(PID);
	aPacket.Read(destX);
	aPacket.Read(destY);
	//aPacket.Read(team);
	//now make a boomerang with this data just unpacked
	BoomerangObjectFactory boomMaker;
	GameObject* boomerang = boomMaker.Spawn(gameObjectRef, PID, destX, destY);
	GameObjects.AddObject(boomerang);
}

void TurkeyClassComponent::writeNetAbility(uint64_t PID, float posX, float posY, int team){
	OutputMemoryBitStream *outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)CM_ABILITY); // have to include the enum here
	outData->Write(PID);
	outData->Write(posX);
	outData->Write(posY);
	//outData->Write(team);
	dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->outgoingPackets.push(outData);
}

int TurkeyClassComponent::useAbility(){
	if (currBirdseed >= maxsBirdseed){
	//if (currBirdseed >= seedRequired){
		InputManager* input = InputManager::getInstance();
		RenderManager* renderMan = RenderManager::getRenderManager();
		playAbilityUseSound();
		//find target destination for boomerang arms
		float targetX, targetY;
		renderMan->windowCoordToWorldCoord(targetX, targetY, input->getMouseX(), input->getMouseY());
		//make boomerang arms
		BoomerangObjectFactory boomMaker;
		GameObject* boomerang = boomMaker.Spawn(gameObjectRef, (*powerNum)++, targetX, targetY);
		GameObjects.AddObject(boomerang);
		//turn player arms invisible
		PlayerRenderComponent* renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
		renderComp->allObjs["armL"]->visible = false;
		renderComp->allObjs["armR"]->visible = false;

		//send it over the wire
		float destX, destY;
		renderMan->windowCoordToWorldCoord(destX, destY, input->getMouseX(), input->getMouseY());
		currArmsSpawned++;
		if (currArmsSpawned >= 2){
			currBirdseed = 0;
			birdseedFullPlayed = false;
			currArmsSpawned = 0;
			m_allObjs["ammoIcon1"]->visible = false;
			m_allObjs["ammoIcon2"]->visible = false;
		}
		writeNetAbility((*powerNum)-1, destX, destY, gameObjectRef->team);
		return true;
	}
	else{
		dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->playFailSound();
		return false;
	}
}

int TurkeyClassComponent::getClass(){
	return CLASS_TURKEY;
}