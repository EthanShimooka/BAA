#include "MinionPhysicsComponent.h"

MinionPhysicsComponent::MinionPhysicsComponent(GameObject* minion, float _initialX, float _initialY, float _length, bool _walkRight)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();
}

MinionPhysicsComponent::~MinionPhysicsComponent(){}

void MinionPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(1, 1); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);
	mBody->SetLinearVelocity(b2Vec2(50, 0));
	setCollisionFilter(COLLISION_MINION, COLLISION_FEATHER | COLLISION_PLATFORM);
}

void MinionPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	//std::cout << "MINION handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
		case GAMEOBJECT_TYPE::OBJECT_FEATHER:
		{
			gameObjectRef->setPos(-10000, 0);
			//mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);
			gameObjectRef->isAlive = false;
			

			break;
		}
		case GAMEOBJECT_TYPE::OBJECT_MINION:
			//just push each other around. Most likely done for us by box2d already
			break;
		default:
			break;
	}
}

void MinionPhysicsComponent::Update(){
	gameObjectRef->posX = mBody->GetPosition().x*worldScale;
	gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	//temp testing code from here down
	if (gameObjectRef->posX > 400){
		mBody->SetLinearVelocity(b2Vec2(-10, 0));
	}
	else if (gameObjectRef->posX < -400){
		mBody->SetLinearVelocity(b2Vec2(10, 0));
	}
}

	