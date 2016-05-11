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


	setCollisionFilter(COLLISION_PLAYER, COLLISION_PLATFORM | COLLISION_MINE | COLLISION_FEATHER | COLLISION_SWITCH );
}



void PlayerPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "PLAYER handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		//do nothing or push past each other
		break;

	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{
		 if (otherObj->team == gameObjectRef->team)break;
		 //signal self death and turn to egg
		PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		uint64_t shooter = dynamic_cast<FeatherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->owner->ID;
		if (otherObj->isLocal){
			logicComp->becomeEgg();
			//Trigger death audio here for person who fired feather
			//Should be local player class here
			ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
			int localClass = classComp->getClass();
			logicComp->playDeathSFX(localClass);
			PlayerNetworkComponent* networkComp = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			networkComp->createDeathPacket(shooter, localClass);
		}
		GameObject* killer = dynamic_cast<FeatherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->owner;
		if (killer->isLocal){	
			dynamic_cast<PlayerLogicComponent*>(killer->GetComponent(COMPONENT_LOGIC))->addToKillList(killer->ID, gameObjectRef->ID);
			logicComp->addToKillList(GamerServices::sInstance->GetLocalPlayerId(), shooter);
		}
		break;
	}
	case  GAMEOBJECT_TYPE::OBJECT_PLATFORM:{
											   inAir = false;
											   PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											   logicComp->launchable = false;
											  
											   break;
	}
	case  GAMEOBJECT_TYPE::OBJECT_MINE:{
										   if (otherObj->team != gameObjectRef->team){
											   MineLogicComponent* mineLogicComp = dynamic_cast<MineLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											   if (mineLogicComp->fuseLit){
												   //using fuseLit works, because once the fuse is lit the collision filter is turned off until it's blown up
												   PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
												   logicComp->becomeEgg();
											   }
										   }

										   break;
	}
	case GAMEOBJECT_TYPE::OBJECT_SWITCH:{
											//do nothing or push past each other
											//		LauncherLogicComponent* logic = dynamic_cast<LauncherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
											PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											logicComp->launchableZone = true;


											break;
	}
	default:
		break;
	}
}

void PlayerPhysicsComponent::launchPlayer(){
	PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	b2Vec2 vel = mBody->GetLinearVelocity();

	logicComp->becomeEgg();
	std::cout << "horizontal velocity: " << vel.x << std::endl;


	if (gameObjectRef->team == TEAM_YELLOW){
		   mBody->SetLinearVelocity(b2Vec2(vel.x + 1.0f, vel.y - 0.1f));
		} else{
	       mBody->SetLinearVelocity(b2Vec2(vel.x + -1.0f, vel.y + 0.1f));
     }

	//check if back at base yet
	if ((gameObjectRef->posX > 0) && (gameObjectRef->team == TEAM_YELLOW)){

		logicComp->hatchBird();
		logicComp->launchable = false;
		logicComp->launchableZone = false;
		currLaunch = false;
	}

	if ((gameObjectRef->posX < 0) && (gameObjectRef->team == TEAM_PURPLE)){
		logicComp->hatchBird();
		logicComp->launchable = false;
		logicComp->launchableZone = false;
		currLaunch = false;
	}

}

void PlayerPhysicsComponent::Update(){
	b2Vec2 vel = mBody->GetLinearVelocity();
	if (gameObjectRef->team==TEAM_PURPLE){
		//mBody->ApplyForce(b2Vec2(200, 0), mBody->GetWorldCenter(), true);
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y-0.5f));
	}
	else if(gameObjectRef->team == TEAM_YELLOW){
		mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y + 0.5f));
		//mBody->ApplyForce(b2Vec2(-200, 0), mBody->GetWorldCenter(), true);
	}
	if (gameObjectRef->isLocal){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}
	else{
		mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale),mBody->GetAngle());
	}
	PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	if (logicComp->isEgg){
		mBody->SetAngularVelocity(-5);
		gameObjectRef->rotation = mBody->GetAngle()*180/M_PI;
		//check if back at base yet
		if (abs(gameObjectRef->posX) > 1300){
			logicComp->hatchBird();
		}
	}

	if (logicComp->launchable && logicComp->launchableZone){
		currLaunch = true;
		launchPlayer();
		}

	if (currLaunch)
	{
		launchPlayer();
	}

}



