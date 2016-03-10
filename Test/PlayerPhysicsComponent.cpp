#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();
}

PlayerPhysicsComponent::~PlayerPhysicsComponent(){}

void PlayerPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	//box.SetAsBox(471, 480); // look up other functions for polygons
	box.SetAsBox(75, 75);
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);

	setCollisionFilter(COLLISION_PLAYER, COLLISION_PLATFORM);
}



void PlayerPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "PLAYER handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		//do nothing or push past each other
		break;
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:
		//take damage on self, maybe make a sqauaking sound?
		break;
	default:
		break;
	}
}

void PlayerPhysicsComponent::Update(){
	gameObjectRef->posX = mBody->GetPosition().x;// *20.0f;
	gameObjectRef->posY = mBody->GetPosition().y;// *20.0f;
	//cout << "x=" << gameObjectRef->posX << "y=" << gameObjectRef->posY << endl;
}