#include "PeacockClassComponent.h"

//Does not compile, not sure why it doesn't

PeacockClassComponent::PeacockClassComponent(GameObject* player)
{
	ClassComponent::ClassComponent();
	isPeacock = true;
	speed += 2;
	seedRequired = 7;
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_CLASS, this);
}


PeacockClassComponent::~PeacockClassComponent()
{
}

void PeacockClassComponent::Update()
{
	if (invokeHelper && timer->isDone()){
		timer->destroy();
		activeFans--;
		invokeHelper = false;
		destroyFan();
		//std::cout << "Destroyed fan 1!" << std::endl;
		//std::cout << "activeFans = " << activeFans << std::endl;
	}
	/*if (invokeHelper2 && timer2->isDone()){
		timer2->destroy();
		activeFans--;
		invokeHelper2 = false;
		destroyFan();
		std::cout << "Destroyed fan 2!" << std::endl;
		std::cout << "activeFans = " << activeFans << std::endl;
	}
	if (invokeHelper3 && timer3->isDone()){
		timer3->destroy();
		activeFans--;
		invokeHelper3 = false;
		destroyFan();
		std::cout << "Destroyed fan 3!" << std::endl;
		std::cout << "activeFans = " << activeFans << std::endl;
	}
	if (invokeHelper4 && timer4->isDone()){
		timer4->destroy();
		activeFans--;
		invokeHelper4 = false;
		destroyFan();
	}
	if (invokeHelper5 && timer5->isDone()){
		timer5->destroy();
		activeFans--;
		invokeHelper5 = false;
		destroyFan();
	}
	if (invokeHelper6 && timer6->isDone()){
		timer6->destroy();
		activeFans--;
		invokeHelper6 = false;
		destroyFan();
	}
	if (invokeHelper7 && timer7->isDone()){
		timer7->destroy();
		activeFans--;
		invokeHelper7 = false;
		destroyFan();
	}
	if (invokeHelper8 && timer8->isDone()){
		timer8->destroy();
		activeFans--;
		invokeHelper8 = false;
		destroyFan();
	}*/
}

void PeacockClassComponent::animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations){

	int bodyAX = 155;
	int bodyAY = 81;
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	RenderManager* renderMan = RenderManager::getRenderManager();
	SDLRenderObject * base = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 0, 0, 0);
	base->toggleIfRenderImage();
	SDLRenderObject * armL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3102, (float)(158 - bodyAX), (float)(95 - bodyAY));
	SDLRenderObject * legL = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3104, (float)(163 - bodyAX), (float)(109 - bodyAY));
	SDLRenderObject * legR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3103, (float)(156 - bodyAX), (float)(117 - bodyAY));
	SDLRenderObject * body = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3100, 0, -8);
	SDLRenderObject * armR = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 3101, (float)(140 - bodyAX), (float)(85 - bodyAY));

	//PlayerPhysicsComponent pos = gameObjectRef->GetComponent(COMPONENT_PHYSICS); 


	//objRef->setAnchor(0.5, 0.5);
	body->setAnchor(bodyAX / double(body->renderRect.w), bodyAY / double(body->renderRect.h));
	armR->setAnchor(9 / double(armR->renderRect.w), 7 / double(armR->renderRect.h));
	armL->setAnchor(9 / double(armL->renderRect.w), 7 / double(armL->renderRect.h));
	legR->setAnchor(15 / double(legR->renderRect.w), 6 / double(legR->renderRect.h));
	legL->setAnchor(13 / double(legL->renderRect.w), 7 / double(legL->renderRect.h));
	//armR->setCurrentFrame(1);
	armR->toggleFlippedH();
	body->setParent(base);
	armL->setParent(body);
	armR->setParent(body);
	legL->setParent(body);
	legR->setParent(body);

	//body->setScale(0.1);
	//body->calcScale(50,50);
	body->setScale(body->calcYScale(50));
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
	motions2.push_back(makeMotion(moveCircArc(armL, 0, 5, 5, 0, 360), 0, 1));
	motions2.push_back(makeMotion(rotateTransform(armL, -30, 10), 0, 0.5));
	motions2.push_back(makeMotion(rotateTransform(armL, -20, -10), 0.5, 0.5));
	motions2.push_back(makeMotion(rotateTransform(armR, -30, 10), 0, 0.5));
	motions2.push_back(makeMotion(rotateTransform(armR, -20, -10), 0.5, 0.5));
	motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legR, 30, -60), 0.5, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, 30, -60), 0, 0.5, ease_QuadInOut));
	motions2.push_back(makeMotion(rotateTransform(legL, -30, 60), 0.5, 0.5, ease_QuadInOut));
	//motions2.push_back(makeMotion(rotateTransform(legR, -30, 60), 0.5, 0.5, ease_QuadIn));
	animations["walk"] = new Animation(800, motions2);



	////// THROW ANIMATION 
	std::list<motion> motions3;
	//motions3.push_back(makeMotion(keyframeJump(armR, 1), 0.0, 0.0));
	motions3.push_back(makeMotion(rotateTransform(armR, 0, -180), 0.0, 1.0, ease_QuadOut));
	animations["throw"] = new Animation(100, motions3);
	////// CHARGE ANIMATION 
	std::list<motion> motions4;
	motions4.push_back(makeMotion(rotateTransform(armR, -20, 0), 0.0, 0.0));
	animations["charge"] = new Animation(100, motions4);
}

int PeacockClassComponent::useAbility(){
	if (currBirdseed >= 1){//seedRequired){
		FanObjectFactory fFactory;
		timer = new Invoke(fanLength);
		invokeHelper = true;
		activeFans++;
		/*switch (++activeFans){
		case 1:
			timer = new Invoke(fanLength);
			invokeHelper = true;
			std::cout << "Starting timer for fan 1!" << std::endl;
			std::cout << "activeFans = " << activeFans << std::endl;
			break;
		case 2:
			timer2 = new Invoke(fanLength);
			invokeHelper2 = true;
			std::cout << "Starting timer for fan 2!" << std::endl;
			std::cout << "activeFans = " << activeFans << std::endl;
			break;
		case 3:
			timer3 = new Invoke(fanLength);
			invokeHelper3 = true;
			std::cout << "Starting timer for fan 3!" << std::endl;
			std::cout << "activeFans = " << activeFans << std::endl;
			break;
		case 4:
			timer4 = new Invoke(fanLength);
			invokeHelper4 = true;
			break;
		case 5:
			timer5 = new Invoke(fanLength);
			invokeHelper5 = true;
			break;
		case 6:
			timer6 = new Invoke(fanLength);
			invokeHelper6 = true;
			break;
		case 7:
			timer7 = new Invoke(fanLength);
			invokeHelper7 = true;
			break;
		case 8:
			timer8 = new Invoke(fanLength);
			invokeHelper8 = true;
			break;
		default:
			break;
		}*/

		InputManager* input = InputManager::getInstance();
		RenderManager* renderMan = RenderManager::getRenderManager();
		float posX, posY, forceX, forceY, rotation;
		// Negative rotation if on right side of screen, positive rotation if on left side of screen
		// ForceX positive if on bottom half, forceX negative if on top half
		// ForceY positive if on left side, forceY negative if on right side
		renderMan->windowCoordToWorldCoord(posX, posY, input->getMouseX(), input->getMouseY());
		//Orient fan based on position
		if (posX > 0){
			rotation = -63;
			forceY = -10;
		}
		else{
			rotation = 63;
			forceY = 10;
		}
		if (posY > 0){
			forceX = -5;
		}
		else{
			forceX = 5;
		}
		GameObjects.AddObject(fFactory.Spawn((*powerNum)++, posX, posY, rotation, gameObjectRef->team));
		writeNetAbility((*powerNum) - 1, posX, posY, rotation);
		fanIDs.push_back((*powerNum) - 1);
		currBirdseed = 0;
		return true;
	}
	else{
		//not enough birdseed to use power. Maybe play a dry firing sound like how guns make a click when they're empty
		return false;
	}
}

void PeacockClassComponent::destroyFan(){
	GameObjects.GetGameObject(*fanIDs.begin())->isAlive = false;
	assert(!fanIDs.empty());
	fanIDs.pop_front();
}

void PeacockClassComponent::writeNetAbility(uint64_t PID, float posX, float posY, float rotation){
	OutputMemoryBitStream *outData = new OutputMemoryBitStream();
	outData->Write(NetworkManager::sInstance->kPosCC);
	outData->Write(gameObjectRef->ID);
	outData->Write((int)3); // have to include the enum here
	outData->Write(PID);
	outData->Write(posX);
	outData->Write(posY);
	//outData->Write(forceX);
	//outData->Write(forceY);
	outData->Write(rotation);
	dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->outgoingPackets.push(outData);
}

void PeacockClassComponent::readNetAbility(InputMemoryBitStream& aPacket){
	FanObjectFactory fFactory;
	uint64_t ID;
	float posX, posY, forceX, forceY, rotation;
	aPacket.Read(ID);
	aPacket.Read(posX);
	aPacket.Read(posY);
	//aPacket.Read(forceX);
	//aPacket.Read(forceY);
	aPacket.Read(rotation);
	timer = new Invoke(fanLength);
	invokeHelper = true;
	activeFans++;
	/*switch (++activeFans){
	case 1:
		timer = new Invoke(fanLength);
		invokeHelper = true;
		std::cout << "Starting networked timer for fan 1!" << std::endl;
		std::cout << "activeFans = " << activeFans << std::endl;
		break;
	case 2:
		timer2 = new Invoke(fanLength);
		invokeHelper2 = true;
		std::cout << "Starting networked timer for fan 2!" << std::endl;
		std::cout << "activeFans = " << activeFans << std::endl;
		break;
	case 3:
		timer3 = new Invoke(fanLength);
		invokeHelper3 = true;
		std::cout << "Starting networked timer for fan 3!" << std::endl;
		std::cout << "activeFans = " << activeFans << std::endl;
		break;
	case 4:
		timer4 = new Invoke(fanLength);
		invokeHelper4 = true;
		break;
	case 5:
		timer5 = new Invoke(fanLength);
		invokeHelper5 = true;
		break;
	case 6:
		timer6 = new Invoke(fanLength);
		invokeHelper6 = true;
		break;
	case 7:
		timer7 = new Invoke(fanLength);
		invokeHelper7 = true;
		break;
	case 8:
		timer8 = new Invoke(fanLength);
		invokeHelper8 = true;
		break;
	default:
		break;
	}*/
	fanIDs.push_back(ID);
	GameObjects.AddObject(fFactory.Spawn(ID, posX, posY, rotation, gameObjectRef->team));
}

int PeacockClassComponent::getClass(){
	return CLASS_PEACOCK;
}