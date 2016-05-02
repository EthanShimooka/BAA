#include "LauncherPhysicsComponent.h"


LauncherPhysicsComponent::LauncherPhysicsComponent(GameObject * launcher)
{
	gameObjectRef = launcher;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(1.5f);
}


LauncherPhysicsComponent::~LauncherPhysicsComponent()
{
}


void LauncherPhysicsComponent::init(float size){
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
	boxFixtureDef.isSensor = true;

	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;


	//
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	setCollisionFilter(COLLISION_SWITCH, COLLISION_PLAYER);
}


void LauncherPhysicsComponent::handleCollision(GameObject* otherObj){
	switch (otherObj->type){

	case GAMEOBJECT_TYPE::OBJECT_PLAYER:{
											//if (otherObj->team)

											/// put render animation, or a call to render animate (the switch)
											 break;
	}
	default:
		break;
	}
}




void LauncherPhysicsComponent::Update(){

	if (gameObjectRef->isAlive){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}

}