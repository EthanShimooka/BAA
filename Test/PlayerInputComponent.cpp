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
	if (physicsComp){
		b2Body* body = physicsComp->mBody;
		InputManager* input = InputManager::getInstance();
		RenderManager* renderMan = RenderManager::getRenderManager();
		Controller* controller = input->controller;
		//handle input for moving
		body->SetLinearVelocity(b2Vec2((float)controller->getLeftThumbX()*playerSpeed, body->GetLinearVelocity().y));
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
		if (input->isKeyDown(KEY_SPACE)||controller->isJoystickPressed(JOYSTICK_A)) {
			if (gameObjectRef->posY>0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -playerSpeed/2));
			else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, playerSpeed / 2));
		}
		////keyboard move down (not really needed)
		if (input->isKeyDown(KEY_S) || input->isKeyDown(KEY_DOWN)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, playerSpeed));
		}
		//shoot feather
		if (input->isMouseLeftPressed()){
			isChargingAttack = true;
		}
		if (isChargingAttack && input->isMouseLeftReleased()){
			double chargeTime = input->getMousePressDuration();
			if (chargeTime > maxCharge)
				chargeTime = maxCharge;
			isChargingAttack = false;
			// for testing 
			//chargeTime = 1300;
			//std::cout << "Charge time: " << chargeTime << std::endl;
			PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			float dx, dy;
			renderMan->windowCoordToWorldCoord(dx, dy, input->getMouseX(), input->getMouseY());
			uint64_t id = logic->spawnFeather((int)dx, (int)dy, (float)chargeTime, featherSpeed);
			PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			net->createFeatherPacket(id, (int)dx, (int)dy, (float)chargeTime);
		}

		//if (controller->getLeftTrigger() > 0.8){	
		//	controller->rumble(1, 750);
		//	//renderMan->worldCoordToWindowCoord(xDir, yDir, gameObjectRef->posX, gameObjectRef->posY);
		//	int xDir = gameObjectRef->posX + 200 * controller->getRightThumbX();
		//	int yDir = gameObjectRef->posY + 200 * controller->getRightThumbY();
		//	std::cout << "xdir=" << xDir << " ydir=" << std::endl;
		//	PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		//	uint64_t id = logic->spawnFeather(xDir, yDir, chargeTime);
		//	PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		//	//not working yet
		//	net->createFeatherPacket(id, xDir, yDir);
		//}

		//change direction of player sprite if needed
		if (body->GetLinearVelocity().x<0)gameObjectRef->flipH = true;
		else if (body->GetLinearVelocity().x>0)gameObjectRef->flipH = false;
		if (body->GetLinearVelocity().x == 0)renderComp->setAnimation("idle");
		//spawn shield
		if (input->isMouseDown(MOUSE_RIGHT)) {
			PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			logic->spawnShield();
		//	uint64_t id = logic->spawnFeather(input->getMouseX(), input->getMouseY());
		//  PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		//	net->createFeatherPacket(id, input->getMouseX(), input->getMouseY());
		}

	}
}

