#include "PlayerPhysicsComponent.h"


PlayerPhysicsComponent::PlayerPhysicsComponent(){}

PlayerPhysicsComponent::~PlayerPhysicsComponent(){}

void PlayerPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	physicsBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(1, 1); // look up other functions for polygons
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	physicsBody->CreateFixture(&boxFixtureDef);
	physicsBody->SetUserData(gameObjectRef);
	//hardcoded for debugging purposes
	physicsBody->SetTransform(b2Vec2(0,-50),0);
}

void PlayerPhysicsComponent::handleCollision(GameObject* otherObj){

}

void PlayerPhysicsComponent::Update(){
	gameObjectRef->posX = physicsBody->GetPosition().x;
	gameObjectRef->posY = physicsBody->GetPosition().y;
	//cout << "x=" << physicsBody->GetPosition().x << "y=" << physicsBody->GetPosition().y<<endl;
}