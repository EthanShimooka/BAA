#include "MidPlatPhysicsComponent.h"


MidPlatPhysicsComponent::MidPlatPhysicsComponent(GameObject* platform)
{
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();

}


MidPlatPhysicsComponent::~MidPlatPhysicsComponent()
{
}

void MidPlatPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	/// Hitbox instantiation
	b2PolygonShape box;
	/// Set Box Shape
	box.SetAsBox(8.5f, 20.1f); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	setCollisionFilter(COLLISION_PLATFORM, COLLISION_PLAYER | COLLISION_MINION | COLLISION_MINE);
}

void MidPlatPhysicsComponent::Update(){



}
