#include "PlayerPhysicsComponent.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject* player, float height, float width)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(height, width);
}

PlayerPhysicsComponent::~PlayerPhysicsComponent(){

	//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
}

void PlayerPhysicsComponent::init(float height, float width){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	if (!mBody)
		mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2CircleShape box;
	//box.SetAsBox(471, 480); // look up other functions for polygons
	//box.SetAsBox(width, height);
	box.m_radius = width;
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);

	setCollisionFilter(COLLISION_PLAYER, COLLISION_PLATFORM | COLLISION_MINE | COLLISION_FEATHER);
}



void PlayerPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "PLAYER handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		//do nothing or push past each other
		break;
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:
		//signal self death and turn to egg
		dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->becomeEgg();
		break;
	case  GAMEOBJECT_TYPE::OBJECT_PLATFORM:
		inAir = false;
		break;
	case  GAMEOBJECT_TYPE::OBJECT_MINE:
		if (otherObj->team != gameObjectRef->team){
			MineLogicComponent* mineLogicComp = dynamic_cast<MineLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
			if(mineLogicComp->fuseLit){
				//using fuseLit works, because once the fuse is lit the collision filter is turned off until it's blown up
				PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
				logicComp->becomeEgg();
				

			}
		}
		break;
	default:
		break;
	}
}



void PlayerPhysicsComponent::Update(){
	b2Vec2 vel = mBody->GetLinearVelocity();
	if (gameObjectRef->posY < 0){
		//mBody->ApplyForce(b2Vec2(200, 0), mBody->GetWorldCenter(), true);
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y-0.5f));
	}
	else{
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y + 0.5f));
		//mBody->ApplyForce(b2Vec2(-200, 0), mBody->GetWorldCenter(), true);
	}
	if (gameObjectRef->isLocal){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}
	else{
		mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale),0);
	}
	PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	if (logicComp->isEgg){
		mBody->SetAngularVelocity(3);
		gameObjectRef->rotation = mBody->GetAngle()*180/M_PI;
		//check if back at base yet
		if (abs(gameObjectRef->posX) > 900){
			logicComp->hatchBird();
		}
	}
}