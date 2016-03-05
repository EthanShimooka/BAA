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
		Controller* controller = input->controller;
		//handle input for moving
		float speed = 60.0f;

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
		if (input->isKeyDown(KEY_SPACE)) {
			body->SetLinearVelocity(b2Vec2(15 * body->GetLinearVelocity().x, -speed));
		}
		////keyboard move down (not really needed)
		if (input->isKeyDown(KEY_S) || input->isKeyDown(KEY_DOWN)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, speed));
		}
		//shoot feather
		if (input->isMouseDown(MOUSE_LEFT)){
			PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			uint64_t id = logic->spawnFeather(input->getMouseX(), input->getMouseY());
			PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			net->createFeatherPacket(id, input->getMouseX(), input->getMouseY());
		}
		//change direction of player sprite if needed
		if (body->GetLinearVelocity().x<0)gameObjectRef->flipH = true;
		else if (body->GetLinearVelocity().x>0)gameObjectRef->flipH = false;
	}
}

