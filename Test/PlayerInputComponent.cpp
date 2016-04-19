#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent(GameObject* player, float _playerSpeed, float _featherSpeed)
{
	input = InputManager::getInstance();
	gameObjectRef = player;
	playerSpeed = _playerSpeed;
	featherSpeed = _featherSpeed;
	gameObjectRef->AddComponent(COMPONENT_INPUT, this);
}


PlayerInputComponent::~PlayerInputComponent()
{
}

void PlayerInputComponent::Update(){
	PlayerPhysicsComponent* physicsComp = (PlayerPhysicsComponent*)gameObjectRef->GetComponent(COMPONENT_PHYSICS);
	PlayerRenderComponent* renderComp = (PlayerRenderComponent*)gameObjectRef->GetComponent(COMPONENT_RENDER);
	PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));

	if (physicsComp){
		b2Body* body = physicsComp->mBody;
		if (!logicComp->isEgg){
			InputManager* input = InputManager::getInstance();
			RenderManager* renderMan = RenderManager::getRenderManager();
			Controller* controller = input->controller;
			//handle input for moving
			body->SetLinearVelocity(b2Vec2(controller->getLeftThumbX()*playerSpeed, body->GetLinearVelocity().y));
			//keyboard move right
			if (input->isKeyDown(KEY_D) || input->isKeyDown(KEY_RIGHT)) {
				body->SetLinearVelocity(b2Vec2(playerSpeed, body->GetLinearVelocity().y));
				renderComp->setAnimation("walk");
			}
			//keyboard move left
			if (input->isKeyDown(KEY_A) || input->isKeyDown(KEY_LEFT)) {
				body->SetLinearVelocity(b2Vec2(-playerSpeed, body->GetLinearVelocity().y));
				renderComp->setAnimation("walk");
			}
			//keyboard jump
			if ((input->isKeyDown(KEY_SPACE) || controller->isJoystickPressed(JOYSTICK_A)) && !physicsComp->inAir) {
				physicsComp->inAir = true;
				if (gameObjectRef->posY > 0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -playerSpeed));
				else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, playerSpeed));
			}
			////keyboard move down (not really needed)
			if (input->isKeyDown(KEY_S) || input->isKeyDown(KEY_DOWN)) {
				body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, playerSpeed));
			}
			//shoot feather
			if (input->isMouseDown(MOUSE_LEFT) && canFire){ //old check that doesn't allow for charging during shot cool down. This breaks the charge up bar.
			//if (input->getMousePressDuration() > 0 && canFire && input->isMouseDown(MOUSE_LEFT)){
				isChargingAttack = true;
				logicComp->startCharge(); // need to synchronize charge bar "animation" wtih actual charging time
			}
			if (isChargingAttack) {
				if (input->getMousePressDuration() < maxCharge) {
					logicComp->currChargePercentage = input->getMousePressDuration() / maxCharge;
					// std::cout << logicComp->currChargePercentage << std::endl;
				}
			}
			if (isChargingAttack && input->isMouseLeftReleased()){
				double chargeTime = input->getMousePressDuration();
				if (chargeTime > maxCharge)
					chargeTime = maxCharge;
				isChargingAttack = false;
				logicComp->currChargePercentage = 0;
				// for testing 
				//chargeTime = 1300;
				//std::cout << "Charge time: " << chargeTime << std::endl;
				
				Timing::sInstance.StartAttackCooldown();
				canFire = false;
				float dx, dy;
				renderMan->windowCoordToWorldCoord(dx, dy, input->getMouseX(), input->getMouseY());
				uint64_t id = logicComp->spawnFeather(dx, dy, chargeTime, featherSpeed);
				PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
				net->createFeatherPacket(id, dx, dy, chargeTime);
			}
			if (input->isKeyDown(KEY_O)){
				//THIS IS FOR PLAYER DEATH TESTING!!!! REMOVE WHEN DONE!!
				dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->becomeEgg();
			}
			//2 Sec delay on feather firing, need some visual representation of cd
			if (Timing::sInstance.AttackCooldownEnded()){
				if (!canFire && input->getMousePressDuration() > 0)
					input->resetMousePressClock();
				canFire = true;
			}

			if (controller->isControllerOn()){
				//controller aiming
				int controllerSensitivity = 10;
				input->setMouseX(input->getMouseX() + controller->getRightThumbX() * controllerSensitivity);
				input->setMouseY(input->getMouseY() + controller->getRightThumbY() * controllerSensitivity);

				//firing with controller

				if (controller->getRightTrigger() < 0.8&& canFire&&isChargingAttack){
					canFire = false;
					isChargingAttack = false;
					controller->rumble(1, 200);
					float xDir, yDir;
					renderMan->windowCoordToWorldCoord(xDir, yDir, renderComp->crosshairRef->posX, renderComp->crosshairRef->posY);
					//std::cout << "xdir=" << xDir << " ydir=" << std::endl;
					PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
					uint64_t id = logic->spawnFeather(xDir, yDir, 150, featherSpeed);
					PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
					//not working yet
					net->createFeatherPacket(id, xDir, yDir, 100);
				}
				if (controller->getRightTrigger() > 0.8)isChargingAttack = true;
			}
			//change direction of player sprite if needed
			if (body->GetLinearVelocity().x<0)gameObjectRef->flipH = true;
			else if (body->GetLinearVelocity().x>0)gameObjectRef->flipH = false;
			if (body->GetLinearVelocity().x == 0)renderComp->setAnimation("idle");
			//spawn shield
			if ((input->isMouseDown(MOUSE_RIGHT)||controller->isJoystickReleased(JOYSTICK_RIGHTSHOULDER)) && (logicComp->currBirdseed == logicComp->maxsBirdseed)) {
				PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
				logic->spawnMine();
				//	uint64_t id = logic->spawnFeather(input->getMouseX(), input->getMouseY());
				//  PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
				//	net->createFeatherPacket(id, input->getMouseX(), input->getMouseY());
			}
		}
	}
}

