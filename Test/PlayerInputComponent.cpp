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
		//handle input for moving
		bool moving = false;
		float speed = 60.0f;
		if (input->isKeyDown(KEY_D)) {
			body->SetLinearVelocity(b2Vec2(speed, body->GetLinearVelocity().y));
			moving = true;
			gameObjectRef->flipH = false;
		}
		if (input->isKeyDown(KEY_A)) {
			body->SetLinearVelocity(b2Vec2(-speed, body->GetLinearVelocity().y));
			moving = true;		
			gameObjectRef->flipH = true;
		}
		if (input->isKeyDown(KEY_SPACE)) {
			body->SetLinearVelocity(b2Vec2(10*body->GetLinearVelocity().x, -speed));
			//moving = true;
		}
		if (input->isKeyDown(KEY_S)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, speed));
			moving = true;
		}
		if (!moving)body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x*0.8, body->GetLinearVelocity().y));
		if (input->isMouseDown(MOUSE_LEFT)){
			PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			logic->spawnFeather(input->getMouseX(), input->getMouseY());
			PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			net->createFeatherPacket(0, input->getMouseX(), input->getMouseY());
		}

	}
}

