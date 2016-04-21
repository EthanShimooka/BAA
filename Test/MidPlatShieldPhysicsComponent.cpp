#include "MidPlatShieldPhysicsComponent.h"


MidPlatShieldPhysicsComponent::MidPlatShieldPhysicsComponent(GameObject * platform)
{
	gameObjectRef = platform;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();
}


MidPlatShieldPhysicsComponent::~MidPlatShieldPhysicsComponent()
{
}


void MidPlatShieldPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	/// Hitbox instantiation
	b2PolygonShape box;
	/// Set Box Shape
	box.SetAsBox(3, 3); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	setCollisionFilter(COLLISION_SWITCH, COLLISION_FEATHER);
}

void MidPlatShieldPhysicsComponent::handleCollision(GameObject* otherObj){
	switch (otherObj->type){

	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{
										   std::cout << "shiggle buz" << std::endl;
											gameObjectRef->isAlive = false;
											ShieldToggle();
											MidPlatShieldLogicComponent* logicComponent = dynamic_cast<MidPlatShieldLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));

											//logicComponent->ShieldToggle();

											break;
	}
	default:
		break;
	}
}


void MidPlatShieldPhysicsComponent::ShieldToggle(){



}




void MidPlatShieldPhysicsComponent::Update(){

	if (gameObjectRef->isAlive){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}
	
}

