#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent(GameObject* player, ClassComponent* _classComp){
	input = InputManager::getInstance();
	gameObjectRef = player;
	playerSpeed = _classComp->speed;
	jumpSpeed = _classComp->jumpSpeed;
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
	body->SetLinearVelocity(b2Vec2((float)(controller->getLeftThumbX()*playerSpeed), (float)(body->GetLinearVelocity().y)));

	//handle jumping
	if (controller->isJoystickPressed(JOYSTICK_A) && !physicsComp->inAir) {
		physicsComp->inAir = true;
		if (gameObjectRef->posY > 0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -jumpSpeed));
		else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jumpSpeed));
		PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		logic->launchable = true;
	}

	//limit controller aiming to screen size
	int controllerSensitivity = 12;
	int mouseX = input->getMouseX() + (int)(controller->getRightThumbX() * controllerSensitivity);
	int mouseY = input->getMouseY() + (int)(controller->getRightThumbY() * controllerSensitivity);
	if (mouseX > SCREEN_WIDTH)mouseX = SCREEN_WIDTH;
	else if (mouseX < 0)mouseX = 0;
	if (mouseY > SCREEN_HEIGHT)mouseY = SCREEN_HEIGHT;
	else if (mouseY < 0)mouseY = 0;
	input->setMouseX(mouseX);
	input->setMouseY(mouseY);

	//firing with controller
	if (controller->getRightTrigger() < 0.75&& controller->lastRightTriggerValue>0.75&& canFire&&isChargingAttack){
		canFire = false;
		isChargingAttack = true;
		logicComp->startCharge(); // need to synchronize charge bar "animation" wtih actual charging time
		Timing::sInstance.StartAttackCooldown();
		controller->rumble(1, 200);
		float dx, dy;
		renderMan->windowCoordToWorldCoord(dx, dy, input->getMouseX(), input->getMouseY());
		uint64_t id = logicComp->spawnFeather(dx, dy, featherSpeed);
		//PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		netComp->createFeatherPacket(id, (int)dx, (int)dy, featherSpeed);
	}
	if (controller->getRightTrigger() > 0.75)isChargingAttack = true;

	//handle special abilites
	if (controller->isJoystickReleased(JOYSTICK_RIGHTSHOULDER)) {
		int powerUsed = classComp->useAbility();
	}

}

void PlayerInputComponent::handleKeyboardInput(RenderManager* renderMan, InputManager* input, Controller* controller){
	b2Body* body = physicsComp->mBody;
	PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));

	//keyboard move right
	if (input->isKeyDown(KEY_D) || input->isKeyDown(KEY_RIGHT)) {
		if(!renderMan->flippedScreen)body->SetLinearVelocity(b2Vec2(playerSpeed, body->GetLinearVelocity().y));
		else body->SetLinearVelocity(b2Vec2(-playerSpeed, body->GetLinearVelocity().y));
		logic->launchable = false;
		//if(!footstepsPlaying) Play footsteps
		//Set bool footstepsPlaying = true
		//Need to check in-air collisions before we play sound
		//if (!physicsComp->inAir) dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->playFootstepSFX();
	}
	//keyboard move left
	else if (input->isKeyDown(KEY_A) || input->isKeyDown(KEY_LEFT)) {
		if (!renderMan->flippedScreen)body->SetLinearVelocity(b2Vec2(-playerSpeed, body->GetLinearVelocity().y));
		else body->SetLinearVelocity(b2Vec2(playerSpeed, body->GetLinearVelocity().y));
		logic->launchable = false;
		//if(!footstepsPlaying) Play footsteps
		//Set bool footstepsPlaying = true
		//if (!physicsComp->inAir) dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->playFootstepSFX();
	}
	else if(!controller->isControllerOn()){
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		logic->launchable = false;
		//Stop play footsteps
		//Set bool footstepsPlaying = false;
		//dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->stopFootstepSFX();
	}
	//keyboard jump
	if (input->isKeyDown(KEY_SPACE)  && !physicsComp->inAir) {
			physicsComp->inAir = true;
			if (gameObjectRef->posY > 0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -jumpSpeed));
			else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, jumpSpeed));
			logic->launchable = true;
	}

	//shoot feather
	if (input->isMouseDown(MOUSE_LEFT) && canFire){ 
		//old check that doesn't allow for charging during shot cool down. This breaks the charge up bar.
		isChargingAttack = true;
		logicComp->startCharge(); // need to synchronize charge bar "animation" wtih actual charging time
	}else{
		logicComp->endCharge();
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
		uint64_t id = logicComp->spawnFeather(dx, dy, featherSpeed);
		//PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		netComp->createFeatherPacket(id, (int)dx, (int)dy, featherSpeed);
	}
	else if(input->isMouseLeftReleased()){
		//Attempting to fire feather before cd over
		dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->playFailSound();
	}
	
	//spawn shield, checks for full birdseed in logic component
	if (input->isMouseRightReleased() ) {
		int powerUsed = classComp->useAbility();
	}
}

bool PlayerInputComponent::isCharging(){
	return isChargingAttack;
}
void PlayerInputComponent::Update(){
	//get needed stuff
	Controller* controller = input->controller;
	InputManager* input = InputManager::getInstance();
	RenderManager* renderMan = RenderManager::getRenderManager();
	b2Body* body = physicsComp->mBody;

	//handle input from sources
	if (!logicComp->isEgg){
		handleControllerInput(renderMan, input, controller);
		handleKeyboardInput(renderMan, input, controller);
	}
	//handle input bounds stuff here to make sure you don't double up on inputs from both

	//2 Sec delay on feather firing, need some visual representation of cd
	if (Timing::sInstance.AttackCooldownEnded()){
		if (!canFire && input->getMousePressDuration() > 0)
			input->resetMousePressClock();
		canFire = true;
		
	}

	//orient character and set idle animation if necessary
	if (body->GetLinearVelocity().x<-0.01)gameObjectRef->flipH = true;
	else if (body->GetLinearVelocity().x>0.01)gameObjectRef->flipH = false;
	if (abs(body->GetLinearVelocity().x) < 0.01)renderComp->setAnimation("idle");
	else renderComp->setAnimation("walk");

	//handle charging variables for crosshair
	if (isChargingAttack) {
		//renderComp->setAnimation("charge");
		//renderComp->setNextAnimation("charge");
		if (controller->isControllerOn()){
			float chargePercent = (float)controller->getRightTriggerDuration() / maxCharge;
			logicComp->currChargePercentage = chargePercent > 1 ? 1 : chargePercent;
		}
		else{
			float chargePercent = (float)input->getMousePressDuration() / maxCharge;
			logicComp->currChargePercentage = chargePercent > 1 ? 1 : chargePercent;
		}
	}

	//check for quail ability
	if (dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS))->getClass() == CLASS_QUAIL){
		QuailClassComponent* quailComp = dynamic_cast<QuailClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
		playerSpeed = quailComp->speed;
	}

	dynamic_cast<PlayerUIComponent*>(gameObjectRef->GetComponent(COMPONENT_UI))->Update();
}