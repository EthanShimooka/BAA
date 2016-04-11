#include "PowerShieldPhysicsComponent.h"


PowerShieldPhysicsComponent::PowerShieldPhysicsComponent(GameObject* shield)
{
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();
}


PowerShieldPhysicsComponent::~PowerShieldPhysicsComponent(){
	//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
}

void PowerShieldPhysicsComponent::init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	// Adjust offsets here yo
	bodyDef.position.Set(gameObjectRef->posX + 40, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	/// Hitbox instantiation
	b2PolygonShape box;
	/// Set Box Shape
	box.SetAsBox(100, 15); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);

	setCollisionFilter(COLLISION_PLATFORM, COLLISION_PLAYER | COLLISION_MINION);
}


void PowerShieldPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	std::cout << "PATFORM handling collision with object ID: " << otherObj->ID << std::endl;
}


void PowerShieldPhysicsComponent::Update(){

}