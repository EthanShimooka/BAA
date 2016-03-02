#include "PhysicsListener.h"


PhysicsListener::PhysicsListener(){}

PhysicsListener::~PhysicsListener(){}


void PhysicsListener::BeginContact(b2Contact* contact){
	std::cout << "Begin Contact" << std::endl;
	GameObject* first = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	GameObject* second = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();
	PhysicsComponent* firstComp = (PhysicsComponent*)first->GetComponent(COMPONENT_PHYSICS);
	if(firstComp)firstComp->handleCollision(second);
	PhysicsComponent* secondComp = (PhysicsComponent*)second->GetComponent(COMPONENT_PHYSICS);
	if(secondComp)secondComp->handleCollision(first);
}
void PhysicsListener::EndContact(b2Contact* contact){
	//std::cout << "End Contact" << std::endl;
}
void PhysicsListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	//std::cout << "Post Solve" << std::endl;
}
void PhysicsListener::PreSolve(b2Contact* contact, const b2ContactImpulse* impulse){
	//std::cout << "Pre Solve" << std::endl;
}
