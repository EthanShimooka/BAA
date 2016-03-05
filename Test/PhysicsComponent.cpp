#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent(){}

PhysicsComponent::~PhysicsComponent(){}

void PhysicsComponent::setCollisionFilter(uint16 categoryBits, uint16 mask){
	//get the filter
	//b2FixtureDef boxFixtureDef;
	//b2Filter filter = mFixture->GetFilterData();
	boxFixtureDef.filter.categoryBits = categoryBits;
	boxFixtureDef.filter.maskBits = mask;
	//filter.groupIndex = ...;
	//and set it back
	mFixture->SetFilterData(boxFixtureDef.filter);
}

void PhysicsComponent::handleCollision(GameObject* otherObj){}

void PhysicsComponent::Update(){}
