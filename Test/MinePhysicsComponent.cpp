#include "MinePhysicsComponent.h"


MinePhysicsComponent::MinePhysicsComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_RENDER, this);
	init();
}

MinePhysicsComponent::~MinePhysicsComponent(){
}


MinePhysicsComponent::MinePhysicsComponent(GameObject* player, float targetX, float targetY){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	targetPos = b2Vec2(targetX/worldScale, targetY/worldScale);
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
	//with the image used, the mine is 3 times as wide as tall. We bump it up a little more
	//that just 3 times for a larger proximity.
	box.SetAsBox(1.0f, 0.2f); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	boxFixtureDef.friction = 0.5;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);

	setCollisionFilter(COLLISION_MINE,  COLLISION_MINION | COLLISION_PLAYER);
}



void MinePhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "MINE handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		//check to see what team it's affiliated with, and detonate if needed
		if (otherObj->team != gameObjectRef->team){
			//if not on the same team, then explode
			std::cout << "Mine should explode now" << std::endl;
			MineLogicComponent* logicComp = dynamic_cast<MineLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			logicComp->lightFuse();
		}
		else std::cout << "same team, don't explode" << std::endl;
		break;
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:
		break;
	case  GAMEOBJECT_TYPE::OBJECT_MINION:
		//check to see what team it's affiliated with, and detonate if needed
		if (otherObj->team != gameObjectRef->team){
			//if not on the same team, then explode
			std::cout << "Mine should explode now" << std::endl;
			MineLogicComponent* logicComp = dynamic_cast<MineLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			logicComp->lightFuse();
		}
		break;
	default:
		break;
	}
}



void MinePhysicsComponent::Update(){
	//need to hover towards target position
	b2Vec2 vel = targetPos - mBody->GetPosition();
	if (vel.Length() < 0.03f){
		mBody->SetTransform(targetPos, mBody->GetAngle());
		mBody->SetLinearVelocity(b2Vec2(0, 0));
	}else{
		vel.Normalize();
		vel *= 3;
		mBody->SetLinearVelocity(vel);
	}
	gameObjectRef->posX = mBody->GetPosition().x*worldScale;
	gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	
}