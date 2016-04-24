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
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	if (!mBody)
		mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2CircleShape box;
	//with the image used, the mine is 3 times as wide as tall. We bump it up a little more
	//that just 3 times for a larger proximity. 0.6f is the width for current landmine texture
	box.m_radius = 2.0f;
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.friction = 0.5f;
	boxFixtureDef.isSensor = true;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	// fan force variables
	forceStrength = 5.0f;
	forceVec = b2Vec2(0, -50);

	setCollisionFilter(COLLISION_FAN, COLLISION_MINION | COLLISION_FEATHER);
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