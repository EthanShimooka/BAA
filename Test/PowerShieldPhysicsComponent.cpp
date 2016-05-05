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
	box.SetAsBox(1, 1); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);

	setCollisionFilter(COLLISION_POWERSHIELD, COLLISION_FEATHER);
}


void PowerShieldPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	//std::cout << "PLATFORM handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:
		//std::cout << "COLLISION BETWEEN SHIELD AND FEATHER" << std::endl;
		break;
	default:
		break;
	}
}


void PowerShieldPhysicsComponent::Update(){

}