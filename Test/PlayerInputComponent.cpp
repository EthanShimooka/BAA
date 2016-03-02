#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent(){}

PlayerInputComponent::~PlayerInputComponent(){}

void PlayerInputComponent::Update(){
	PlayerPhysicsComponent* physicsComp = (PlayerPhysicsComponent*)gameObjectRef->GetComponent(COMPONENT_PHYSICS);
	if (physicsComp){
		b2Body* body = physicsComp->physicsBody;
		InputManager* input = InputManager::getInstance();
		//handle input for moving
		bool moving = false;
		if (input->isKeyDown(KEY_RIGHT)) {
			body->SetLinearVelocity(b2Vec2(10000, body->GetLinearVelocity().y));
			moving = true;
		}
		if (input->isKeyDown(KEY_LEFT)) {
			body->SetLinearVelocity(b2Vec2(-10000, body->GetLinearVelocity().y));
			moving = true;		}
		if (input->isKeyDown(KEY_UP)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -10000));
			moving = true;
		}
		if (input->isKeyDown(KEY_DOWN)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 10000));
			moving = true;
		}
		if (!moving)body->SetLinearVelocity(b2Vec2(0, 0));

	}
}

