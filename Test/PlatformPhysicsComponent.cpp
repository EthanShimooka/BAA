#include "PlatformPhysicsComponent.h"


PlatformPhysicsComponent::PlatformPhysicsComponent(GameObject* platform){
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();

}


PlatformPhysicsComponent::~PlatformPhysicsComponent()
{
}

void PlatformPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(350, 1); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);

	setCollisionFilter(COLLISION_PLATFORM, COLLISION_PLAYER | COLLISION_MINION);
}

void PlatformPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	cout << "PATFORM handling collision with object ID: " << otherObj->ID << endl;
}

void PlatformPhysicsComponent::Update(){
	//gameObjectRef->posX = mBody->GetPosition().x;// *20.0f;
	//gameObjectRef->posY = mBody->GetPosition().y;// *20.0f;
	//cout << "x=" << mBody->GetPosition().x << "y=" << mBody->GetPosition().y<<endl;
}

