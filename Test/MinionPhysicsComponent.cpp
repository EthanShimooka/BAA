#include "MinionPhysicsComponent.h"

MinionPhysicsComponent::MinionPhysicsComponent(GameObject* minion)
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
	box.SetAsBox(16, 16); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);

	setCollisionFilter(COLLISION_MINION, COLLISION_FEATHER | COLLISION_PLATFORM);
}

void MinionPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	cout << "MINION handling collision with object ID: " << otherObj->ID << endl;
	switch (otherObj->type){
		case GAMEOBJECT_TYPE::OBJECT_FEATHER:
			gameObjectRef->isAlive = false;
			gameObjectRef->setPos(-500, -500);
			break;
		case GAMEOBJECT_TYPE::OBJECT_MINION:
			//just push each other around. Most likely done for us by box2d already
			break;
		default:
			break;
	}
}

void MinionPhysicsComponent::Update(){
	//gameObjectRef->posX = mBody->GetPosition().x;
	gameObjectRef->posY = mBody->GetPosition().y;
	if (!gameObjectRef->isAlive)
		mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), 0);
	//cout << "x=" << mBody->GetPosition().x << "y=" << mBody->GetPosition().y<<endl;
}

	