#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent(GameObject* player, ClassComponent* _classComp){
	input = InputManager::getInstance();
	gameObjectRef = player;
	playerSpeed = _classComp->speed;
	featherSpeed = _classComp->featherSpeed;
	classComp = _classComp;
	gameObjectRef->AddComponent(COMPONENT_INPUT, this);

	physicsComp = dynamic_cast<PlayerPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	netComp = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
}


PlayerInputComponent::~PlayerInputComponent(){
}

void PlayerInputComponent::handleControllerInput(RenderManager* renderMan, InputManager* input, Controller* controller){
	//precondition checking
	if (!controller->isControllerOn())return;

	//handle movement
	b2Body* body = physicsComp->mBody;
	body->SetLinearVelocity(b2Vec2(controller->getLeftThumbX()*playerSpeed, body->GetLinearVelocity().y));

	//handle jumping
	if (controller->isJoystickPressed(JOYSTICK_A) && !physicsComp->inAir) {
		physicsComp->inAir = true;
		if (gameObjectRef->posY > 0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -playerSpeed));
		else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, playerSpeed));
	}

	//handle firing
	//controller aiming
	int controllerSensitivity = 12;
	int mouseX = input->getMouseX() + controller->getRightThumbX() * controllerSensitivity;
	int mouseY = input->getMouseY() + controller->getRightThumbY() * controllerSensitivity;
	if (mouseX > SCREEN_WIDTH)mouseX = SCREEN_WIDTH;
	else if (mouseX < 0)mouseX = 0;
	if (mouseY > SCREEN_HEIGHT)mouseY = SCREEN_HEIGHT;
	else if (mouseY < 0)mouseY = 0;
	input->setMouseX(mouseX);
	input->setMouseY(mouseY);

	//firing with controller
	if (controller->getRightTrigger() < 0.75&& controller->lastRightTriggerValue>0.75&& canFire&&isChargingAttack){
		canFire = false;
		isChargingAttack = false;
		Timing::sInstance.StartAttackCooldown();
		controller->rumble(1, 200);
		float xDir, yDir;
		renderMan->windowCoordToWorldCoord(xDir, yDir, renderComp->crosshairRef->posX, renderComp->crosshairRef->posY);
		//std::cout << "xdir=" << xDir << " ydir=" << std::endl;
		//PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		uint64_t id = logicComp->spawnFeather(xDir, yDir, 150 * featherSpeed);
		//PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		//not working yet
		netComp->createFeatherPacket(id, xDir, yDir, 100);
	}
	if (controller->getRightTrigger() > 0.75)isChargingAttack = true;

	//handle special abilites
	if (controller->isJoystickReleased(JOYSTICK_RIGHTSHOULDER)) {
		int powerUsed = classComp->useAbility();
		//	uint64_t id = logic->spawnFeather(input->getMouseX(), input->getMouseY());
		// PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		//	net->createFeatherPacket(id, input->getMouseX(), input->getMouseY());
	}

}

void PlayerInputComponent::handleKeyboardInput(RenderManager* renderMan, InputManager* input, Controller* controller){
	if (logicComp->isEgg)return;
	b2Body* body = physicsComp->mBody;
	//keyboard move right
	if (input->isKeyDown(KEY_D) || input->isKeyDown(KEY_RIGHT)) {
		body->SetLinearVelocity(b2Vec2(playerSpeed, body->GetLinearVelocity().y));
	}
	//keyboard move left
	else if (input->isKeyDown(KEY_A) || input->isKeyDown(KEY_LEFT)) {
		body->SetLinearVelocity(b2Vec2(-playerSpeed, body->GetLinearVelocity().y));
	}
	else{
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
	}
	//keyboard jump
	if (input->isKeyDown(KEY_SPACE)  && !physicsComp->inAir) {
		physicsComp->inAir = true;
		if (gameObjectRef->posY > 0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -playerSpeed));
		else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, playerSpeed));
	}

	//shoot feather
	if (input->isMouseDown(MOUSE_LEFT) && canFire){ 
		//old check that doesn't allow for charging during shot cool down. This breaks the charge up bar.
		isChargingAttack = true;
		logicComp->startCharge(); // need to synchronize charge bar "animation" wtih actual charging time
	}

	if (isChargingAttack && input->isMouseLeftReleased()){
		double chargeTime = input->getMousePressDuration();
		if (chargeTime > maxCharge)
			chargeTime = maxCharge;
		isChargingAttack = false;
		logicComp->currChargePercentage = 0;
		

		Timing::sInstance.StartAttackCooldown();
		canFire = false;
		float dx, dy;
		renderMan->windowCoordToWorldCoord(dx, dy, input->getMouseX(), input->getMouseY());
		uint64_t id = logicComp->spawnFeather(dx, dy, chargeTime * featherSpeed);
		//PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		netComp->createFeatherPacket(id, dx, dy, chargeTime * featherSpeed);
	}
	if (input->isKeyDown(KEY_O)){
		//THIS IS FOR PLAYER DEATH TESTING!!!! REMOVE WHEN DONE!!
		logicComp->becomeEgg();
	}
	
	
	//spawn shield, checks for full birdseed in logic component
	if (input->isMouseDown(MOUSE_RIGHT) ) {
		int powerUsed = classComp->useAbility();
		//	uint64_t id = logic->spawnFeather(input->getMouseX(), input->getMouseY());
		// PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		//	net->createFeatherPacket(id, input->getMouseX(), input->getMouseY());
	}
}


void PlayerInputComponent::Update(){
	//get needed stuff
	Controller* controller = input->controller;
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	b2Body* body = physicsComp->mBody;

	//handle input from sources
	handleControllerInput(renderMan, input, controller);
	handleKeyboardInput(renderMan, input, controller);
	//handle input bounds stuff here to make sure you don't double up on inputs from both

	//2 Sec delay on feather firing, need some visual representation of cd
	if (Timing::sInstance.AttackCooldownEnded()){
		if (!canFire && input->getMousePressDuration() > 0)
			input->resetMousePressClock();
		canFire = true;
	}

	//orient character and set idle animation if necessary
	if (body->GetLinearVelocity().x<0)gameObjectRef->flipH = true;
	else if (body->GetLinearVelocity().x>0)gameObjectRef->flipH = false;
	if (body->GetLinearVelocity().x == 0)renderComp->setAnimation("idle");
	else renderComp->setAnimation("walk");

	//handle charging meter
	if (isChargingAttack) {
		if (controller->isControllerOn()){
			float chargePercent = controller->getRightTriggerDuration() / maxCharge;
			logicComp->currChargePercentage = chargePercent > 1 ? 1 : chargePercent;
		}
		else logicComp->currChargePercentage = input->getMousePressDuration() / maxCharge;
	}
}

