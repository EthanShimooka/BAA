#include "PlayerPhysicsComponent.h"
#include "Stats.h"

PlayerPhysicsComponent::PlayerPhysicsComponent(GameObject* player, float height, float width)
{
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(height, width);
}

PlayerPhysicsComponent::~PlayerPhysicsComponent(){
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

	setCollisionFilter(COLLISION_PLAYER, COLLISION_PLATFORM | COLLISION_MINE | COLLISION_FEATHER | COLLISION_SWITCH | COLLISION_BASE | COLLISION_BOOMERANG);
}



void PlayerPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "PLAYER handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_BOOMERANG:{
											   PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											   if (otherObj->team != gameObjectRef->team && !logicComp->isEgg){
												   //kill yourself
												   logicComp->death = true;
												   logicComp->becomeEgg();
												   PlayerNetworkComponent* networkComp = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
												   ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
												   BoomerangPhysicsComponent* boomLogicComp = dynamic_cast<BoomerangPhysicsComponent*>(otherObj->GetComponent(COMPONENT_PHYSICS));
												   GameObject* boomOwner = boomLogicComp->owner;
												   networkComp->createDeathPacket(boomOwner->ID, classComp->getClass(), gameObjectRef->ID);
											   }
											   break;
	}
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{
		 if (otherObj->team == gameObjectRef->team)break;
		 //signal self death and turn to egg
		PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		FeatherLogicComponent* featherLogicComp = dynamic_cast<FeatherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
		GameObject* featherOwner = featherLogicComp->owner;
		uint64_t shooter = featherOwner->ID;
		if (otherObj->isLocal && !logicComp->isEgg){
			//Triggers death stuff for player who fired feather
			logicComp->becomeEgg();
			logicComp->death = true;
			ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
			int localClass = classComp->getClass();
			featherLogicComp->giveBirdseed(3);
			logicComp->playDeathSFX(localClass, gameObjectRef->ID);
			PlayerNetworkComponent* networkComp = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			networkComp->createDeathPacket(shooter, localClass, gameObjectRef->ID);
		}
		GameObject* killer = dynamic_cast<FeatherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->owner;
		if (killer->isLocal){	
			dynamic_cast<PlayerUIComponent*>(killer->GetComponent(COMPONENT_UI))->addToKillList(killer->ID, gameObjectRef->ID);
			//debug this line below. I added in the if statement since it was breaking when calling it on gameobjects that didn't have UIComponents (HUD)
			//I'm not sure why I originally was calling it if didn't have HUD stuff
			if(gameObjectRef->isLocal) dynamic_cast<PlayerUIComponent*>(gameObjectRef->GetComponent(COMPONENT_UI))->addToKillList(GamerServices::sInstance->GetLocalPlayerId(), shooter);
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
		if (otherObj->team == gameObjectRef->team) break;
		PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		MineLogicComponent* mineLogicComp = dynamic_cast<MineLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
		GameObject* mineOwner = mineLogicComp->owner;
		uint64_t shooter = mineOwner->ID;
		if (otherObj->isLocal && !logicComp->isEgg){
			logicComp->becomeEgg();
			logicComp->death = true;
			ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
			int localClass = classComp->getClass();
			mineLogicComp->giveBirdseed(3);
			logicComp->playDeathSFX(localClass, gameObjectRef->ID);
			PlayerNetworkComponent* networkComp = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
			networkComp->createDeathPacket(shooter, localClass, gameObjectRef->ID);
		}
		GameObject* killer = dynamic_cast<MineLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->owner;
		if (killer->isLocal){

			dynamic_cast<PlayerUIComponent*>(killer->GetComponent(COMPONENT_UI))->addToKillList(killer->ID, gameObjectRef->ID);
			//debug this line below. I added in the if statement since it was breaking when calling it on gameobjects that didn't have UIComponents (HUD)
			//I'm not sure why I originally was calling it if didn't have HUD stuff
			if (gameObjectRef->isLocal) dynamic_cast<PlayerUIComponent*>(gameObjectRef->GetComponent(COMPONENT_UI))->addToKillList(GamerServices::sInstance->GetLocalPlayerId(), shooter);
		}
										   
		break;
	}
	case GAMEOBJECT_TYPE::OBJECT_LAUNCHER:{
											//do nothing or push past each other
											//		LauncherLogicComponent* logic = dynamic_cast<LauncherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
											PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											logicComp->launchableZone = true;

											if (launchThrow){
												LauncherRenderComponent* launcherRend = dynamic_cast<LauncherRenderComponent*>(otherObj->GetComponent(COMPONENT_RENDER));
												launcherRend->throwLauncher();
												launchThrow = false;
											}

											break;
	}
	default:
		break;
	}
}


void PlayerPhysicsComponent::endCollision(GameObject* otherObj){

	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		//do nothing or push past each other
		break;


	case  GAMEOBJECT_TYPE::OBJECT_PLATFORM:{
											   inAir = false;
											   PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											   logicComp->launchable = false;

											   break;
	}

	case GAMEOBJECT_TYPE::OBJECT_LAUNCHER:{									
											  PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											  logicComp->launchableZone = false;
											
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


	if (gameObjectRef->team == TEAM_YELLOW){
		   mBody->SetLinearVelocity(b2Vec2(vel.x + 1.0f, vel.y - 0.1f));
		} else{
	       mBody->SetLinearVelocity(b2Vec2(vel.x + -1.0f, vel.y + 0.1f));
     }

	//check if back at base yet
	if ((gameObjectRef->posX > 0 && gameObjectRef->team == TEAM_YELLOW) || (gameObjectRef->posX < 0 && gameObjectRef->team == TEAM_PURPLE)){
		logicComp->hatchBird(false);
		logicComp->launchable = false;
		logicComp->launchableZone = false;
		currLaunch = false;
	}

}

void PlayerPhysicsComponent::Update(){
	//add gravity
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
	//handle walking animations and orientation
	PlayerRenderComponent* renderComp = dynamic_cast<PlayerRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	float32 xVel = mBody->GetLinearVelocity().x;
	if (abs(xVel) > 0.01){
		renderComp->setAnimation("walk");
	}else renderComp->setAnimation("idle");
	if (xVel<-0.01){
		gameObjectRef->flipH = true;
	}
	else if (xVel>0.01){
		gameObjectRef->flipH = false;
	}
	//handle egg physics
	PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
	if (logicComp->isEgg){
		mBody->SetAngularVelocity(-5);
		gameObjectRef->rotation = (float)(mBody->GetAngle()*180/M_PI);
		//check if back at base yet
		if (logicComp->death && abs(gameObjectRef->posX) > 1300){
			logicComp->hatchBird(true);
			logicComp->death = false;
		}
	}

	if (logicComp->launchable && logicComp->launchableZone){
		currLaunch = true;
		launchPlayer();
		launchThrow = true;
		}

	if (currLaunch)
	{
		launchPlayer();
	}

}



