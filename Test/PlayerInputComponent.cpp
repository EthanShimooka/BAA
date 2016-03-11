#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent(GameObject* player)
{
	input = InputManager::getInstance();
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_INPUT, this);
}


PlayerInputComponent::~PlayerInputComponent()
{
}

void PlayerInputComponent::Update(){
	PlayerPhysicsComponent* physicsComp = (PlayerPhysicsComponent*)gameObjectRef->GetComponent(COMPONENT_PHYSICS);
	if (physicsComp){
		b2Body* body = physicsComp->mBody;
		InputManager* input = InputManager::getInstance();
		RenderManager* renderMan = RenderManager::getRenderManager();
		Controller* controller = input->controller;
		//handle input for moving
		float speed = 15.0f;
		body->SetLinearVelocity(b2Vec2(controller->getLeftThumbX()*speed, body->GetLinearVelocity().y));
		//keyboard move right
		if (input->isKeyDown(KEY_D) || input->isKeyDown(KEY_RIGHT)) {
			body->SetLinearVelocity(b2Vec2(speed, body->GetLinearVelocity().y));
		}
		//keyboard move left
		if (input->isKeyDown(KEY_A) || input->isKeyDown(KEY_LEFT)) {
			body->SetLinearVelocity(b2Vec2(-speed, body->GetLinearVelocity().y));
		}
		//keyboard jump
		if (input->isKeyDown(KEY_SPACE)||controller->isJoystickPressed(JOYSTICK_A)) {
			if (gameObjectRef->posY>0)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -speed/2));
			else body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, speed / 2));
		}
		////keyboard move down (not really needed)
		if (input->isKeyDown(KEY_S) || input->isKeyDown(KEY_DOWN)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, speed));
		}
		//shoot feather
		if (input->isMouseDown(MOUSE_LEFT)){
			PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			float dx, dy;
			renderMan->windowCoordToWorldCoord(dx,dy,input->getMouseX(), input->getMouseY());
			std::cout << atan(dy / dx) / M_PI * 180 << std::endl;
			uint64_t id = logic->spawnFeather(dx,dy);
			PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			//std::cout << "x=" << input->getMouseX() << " y=" << input->getMouseY() << std::endl;
			net->createFeatherPacket(id, input->getMouseX(), input->getMouseY());
		}

		if (controller->getLeftTrigger() > 0.8){	
			//renderMan->worldCoordToWindowCoord(xDir, yDir, gameObjectRef->posX, gameObjectRef->posY);
			int xDir = gameObjectRef->posX + 200 * controller->getRightThumbX();
			int yDir = gameObjectRef->posY + 200 * controller->getRightThumbY();
			std::cout << "xdir=" << xDir << " ydir=" << std::endl;
			PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			uint64_t id = logic->spawnFeather(xDir, yDir);
			PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			//not working yet
			net->createFeatherPacket(id, xDir, yDir);
		}
		//change direction of player sprite if needed
		if (body->GetLinearVelocity().x<0)gameObjectRef->flipH = true;
		else if (body->GetLinearVelocity().x>0)gameObjectRef->flipH = false;
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

