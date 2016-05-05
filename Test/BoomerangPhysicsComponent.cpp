#include "BoomerangPhysicsComponent.h"


BoomerangPhysicsComponent::BoomerangPhysicsComponent(GameObject* boomerang, GameObject* _owner, int destX, int destY){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	targetDest = b2Vec2(destX, destY); 
	owner = _owner;
	ownerPhysics = dynamic_cast<PlayerPhysicsComponent*>(_owner->GetComponent(COMPONENT_PHYSICS));
}


BoomerangPhysicsComponent::~BoomerangPhysicsComponent(){
}

void BoomerangPhysicsComponent::Update(){
	if (returning){
		//straight line back
		b2Vec2 currPos = mBody->GetPosition();
		b2Vec2 destPos = ownerPhysics->mBody->GetPosition();
		b2Vec2 movementVec = destPos - currPos;
		movementVec.Normalize();
		movementVec *= 4;
		mBody->SetLinearVelocity(movementVec);
	}
	else{
		//curve to destination

	}
}