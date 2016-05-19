#include "FanPhysicsComponent.h"

#define PI 3.14159265

FanPhysicsComponent::FanPhysicsComponent(GameObject* player, double rotation)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(rotation);
}

FanPhysicsComponent::~FanPhysicsComponent(){

}

void FanPhysicsComponent::init(double rotation)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();

	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2CircleShape box;
	box.m_radius = 6.0f;
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1.0f;
	boxFixtureDef.isSensor = true;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	// fan force variables
	forceStrength = 11.0f; //default strenth, pass in as argument if you want to set strength dynamically
	forceVec = b2Vec2((forceStrength * cos(rotation * PI / 180.0f)), (forceStrength * sin(rotation * PI / 180.0f))); // takes angle in degrees and converts it into a force vector times a constant strength

	setCollisionFilter(COLLISION_FAN, COLLISION_MINION);

}


void FanPhysicsComponent::handleCollision(GameObject* otherObj){
	switch (otherObj->type){
	case  GAMEOBJECT_TYPE::OBJECT_MINION:
		// APPLY FORCE TO MINION
		if (gameObjectRef->isAlive){ //Keeps dead fans from blowing
			dynamic_cast<PhysicsComponent*>(otherObj->GetComponent(COMPONENT_PHYSICS))->mBody->ApplyForceToCenter(forceVec, true);
		}
		break;
	default:
		break;
	}
}

void FanPhysicsComponent::Update(){
	
}