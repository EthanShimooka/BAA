#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject* player, float height, float width)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(height, width);
}

PlayerPhysicsComponent::~PlayerPhysicsComponent(){
	//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
}

void PlayerPhysicsComponent::init(float height, float width){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	//box.SetAsBox(471, 480); // look up other functions for polygons
	box.SetAsBox(height, width);
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
	b2Vec2 vel = mBody->GetLinearVelocity();
	if (gameObjectRef->posY < 0){
		//mBody->ApplyForce(b2Vec2(200, 0), mBody->GetWorldCenter(), true);
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y-0.5));
	}
	else{
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y + 0.5));
		//mBody->ApplyForce(b2Vec2(-200, 0), mBody->GetWorldCenter(), true);
	}
	gameObjectRef->posX = mBody->GetPosition().x*worldScale;
	gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	//std::cout << "x=" << gameObjectRef->posX << "y=" << gameObjectRef->posY << std::endl;
}