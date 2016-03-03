#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(){}

PhysicsComponent::~PhysicsComponent(){}

void PhysicsComponent::setCollisionFilter(uint16 mask){
	//get the filter
	b2Filter filter = mFixture->GetFilterData();
	filter.maskBits = mask;
	//filter.groupIndex = ...;
	//and set it back
	mFixture->SetFilterData(filter);
}

void PhysicsComponent::handleCollision(GameObject* otherObj){}

void PhysicsComponent::Update(){}
