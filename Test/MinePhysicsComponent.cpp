#include "MinePhysicsComponent.h"


MinePhysicsComponent::MinePhysicsComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	init();
}

MinePhysicsComponent::~MinePhysicsComponent(){
}


MinePhysicsComponent::MinePhysicsComponent(GameObject* player, float height, float width){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init();
}

void MinePhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	if (!mBody)
		mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(1, 1); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);

	setCollisionFilter(COLLISION_FEATHER, COLLISION_PLATFORM | COLLISION_MINION);
}



void MinePhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "PLAYER handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		break;
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:
		break;
	case  GAMEOBJECT_TYPE::OBJECT_PLATFORM:
		break;
	default:
		break;
	}
}



void MinePhysicsComponent::Update(){
	b2Vec2 vel = mBody->GetLinearVelocity();
	if (gameObjectRef->posY > 0){
		//mBody->ApplyForce(b2Vec2(200, 0), mBody->GetWorldCenter(), true);
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y - 0.5f));
	}
	else{
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y + 0.5f));
		//mBody->ApplyForce(b2Vec2(-200, 0), mBody->GetWorldCenter(), true);
	}
	gameObjectRef->posX = mBody->GetPosition().x*worldScale;
	gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	
}