#include "MidBasePhysicsComponent.h"


MidBasePhysicsComponent::MidBasePhysicsComponent(GameObject * base)
{
	gameObjectRef = base;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	Init();

}


MidBasePhysicsComponent::~MidBasePhysicsComponent()
{
}


void MidBasePhysicsComponent::Init(){

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	/// Hitbox instantiation
	b2PolygonShape box;
	/// Set Box Shape
	box.SetAsBox(5.5f, 12.7f); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	setCollisionFilter(COLLISION_PLATFORM, COLLISION_PLAYER | COLLISION_MINION);




}


void MidBasePhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "FEATHER handling collision with object ID: " << otherObj->ID << std::endl;
	//probably destroy itself, maybe trigger a sound?
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_MINION:{

											// chack to see if it is of opposing minion type
											if otherObj()


											//give birdseed
											dynamic_cast<FeatherLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->giveBirdseed(1);
											//destroy self or return to object pool
											gameObjectRef->isAlive = false;
											break;
	}

	default:
		break;
	}
}




void MidBasePhysicsComponent::Update(){






}