#include "MidPlatShieldPhysicsComponent.h"


MidPlatShieldPhysicsComponent::MidPlatShieldPhysicsComponent(GameObject * platform)
{
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(1.5f);
}


MidPlatShieldPhysicsComponent::MidPlatShieldPhysicsComponent(GameObject * platform, int size)
{
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init((float)size);
}



MidPlatShieldPhysicsComponent::~MidPlatShieldPhysicsComponent()
{
}


void MidPlatShieldPhysicsComponent::init(float size){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);
	/// Hitbox instantiation
	b2CircleShape box;
	/// Set Box Shape
	box.m_radius = size;

	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;


	//
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	setCollisionFilter(COLLISION_SWITCH, COLLISION_FEATHER);
}

void MidPlatShieldPhysicsComponent::handleCollision(GameObject* otherObj){
	switch (otherObj->type){

	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{
											 MidPlatShieldLogicComponent* logicComponent = dynamic_cast<MidPlatShieldLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											 logicComponent->toggleShield();
											 break;
	}
	default:
		break;
	}
}

void MidPlatShieldPhysicsComponent::changeShape(){


}


void MidPlatShieldPhysicsComponent::Update(){

	if (gameObjectRef->isAlive){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}

}

