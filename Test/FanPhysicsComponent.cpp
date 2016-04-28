#include "FanPhysicsComponent.h"


FanPhysicsComponent::FanPhysicsComponent(GameObject* player)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	init();
}

FanPhysicsComponent::~FanPhysicsComponent(){

}

void FanPhysicsComponent::init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();

	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2CircleShape box;
	box.m_radius = 3.0f;
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.isSensor = true;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	// fan force variables
	forceVec = b2Vec2(0, -500.0f);

	setCollisionFilter(COLLISION_FAN, COLLISION_MINION);

}


void FanPhysicsComponent::handleCollision(GameObject* otherObj){
	switch (otherObj->type){
	case  GAMEOBJECT_TYPE::OBJECT_MINION:
		// APPLY FORCE TO MINION
		dynamic_cast<PhysicsComponent*>(otherObj->GetComponent(COMPONENT_PHYSICS))->mBody->ApplyForceToCenter(forceVec, true);
		break;
	default:
		break;
	}
}

void FanPhysicsComponent::Update(){
	
}