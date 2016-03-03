#include "MinionPhysicsComponent.h"


MinionPhysicsComponent::MinionPhysicsComponent(){}


MinionPhysicsComponent::~MinionPhysicsComponent(){}

void MinionPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	physicsBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(100,1); // look up other functions for polygons
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	b2Fixture* fixture = physicsBody->CreateFixture(&boxFixtureDef);
	physicsBody->SetUserData(gameObjectRef);
	physicsBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);

	
}

void MinionPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	cout << "minion handling physics" << endl;
}

void MinionPhysicsComponent::Update(){
	gameObjectRef->posX = physicsBody->GetPosition().x;
	gameObjectRef->posY = physicsBody->GetPosition().y;
	//cout << "x=" << physicsBody->GetPosition().x << "y=" << physicsBody->GetPosition().y<<endl;
}

	