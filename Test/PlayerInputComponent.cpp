#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent(){}

PlayerInputComponent::~PlayerInputComponent(){}

void PlayerInputComponent::Update(){
	PlayerPhysicsComponent* physicsComp = (PlayerPhysicsComponent*)gameObjectRef->GetComponent(COMPONENT_PHYSICS);
	if (physicsComp){
		b2Body* body = physicsComp->mBody;
		InputManager* input = InputManager::getInstance();
		//handle input for moving
		bool moving = false;
		float speed = 6.0f;
		if (input->isKeyDown(KEY_D)) {
			body->SetLinearVelocity(b2Vec2(speed, body->GetLinearVelocity().y));
			moving = true;
		}
		if (input->isKeyDown(KEY_A)) {
			body->SetLinearVelocity(b2Vec2(-speed, body->GetLinearVelocity().y));
			moving = true;		}
		if (input->isKeyDown(KEY_SPACE)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -speed));
			moving = true;
		}
		if (input->isKeyDown(KEY_S)) {
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, speed));
			moving = true;
		}
		if (!moving)body->SetLinearVelocity(b2Vec2(0,body->GetLinearVelocity().y));

	}
}

