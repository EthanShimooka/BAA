#include "MidBasePhysicsComponent.h"


MidBasePhysicsComponent::MidBasePhysicsComponent(GameObject * base)
{
	gameObjectRef = base;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	Init();

}


MidBasePhysicsComponent::~MidBasePhysicsComponent()
{
}


void MidBasePhysicsComponent::Init(){

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	/// Hitbox instantiation
	b2PolygonShape box;
	/// Set Box Shape
	box.SetAsBox(5.5, 12.7); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	setCollisionFilter(COLLISION_PLATFORM, COLLISION_PLAYER | COLLISION_MINION);




}

void MidBasePhysicsComponent::Update(){






}