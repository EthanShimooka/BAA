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
		GameObject* featherOwner = dynamic_cast<FeatherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->owner;
		PlayerLogicComponent* otherPlayerLogicComp = dynamic_cast<PlayerLogicComponent*>(featherOwner->GetComponent(COMPONENT_LOGIC));
		uint64_t shooter = featherOwner->ID;
		if (otherObj->isLocal){
			//Triggers death stuff for player who fired feather
			logicComp->becomeEgg();
			//otherPlayerLogicComp->timer = new Invoke(0.5f);
			//otherPlayerLogicComp->invokeHelper = true;
			//otherPlayerLogicComp->death = true; //NEED TO BE setting this for logicComp attached not to gameObjectRef but to otherObj
			//Trigger death audio here for person who fired feather
			//Should be local player class here
			ClassComponent* classComp = dynamic_cast<ClassComponent*>(gameObjectRef->GetComponent(COMPONENT_CLASS));
			int localClass = classComp->getClass();
			logicComp->playDeathSFX(localClass);
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
										   if (otherObj->team != gameObjectRef->team){
											   MineLogicComponent* mineLogicComp = dynamic_cast<MineLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											   if (mineLogicComp->fuseLit){
												   //using fuseLit works, because once the fuse is lit the collision filter is turned off until it's blown up
												   PlayerLogicComponent* logicComp = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
												   GameObject* mineOwner = dynamic_cast<FeatherLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->owner;
												   PlayerLogicComponent* otherPlayerLogicComp = dynamic_cast<PlayerLogicComponent*>(mineOwner->GetComponent(COMPONENT_LOGIC));
												   uint64_t shooter = mineOwner->ID;
												   logicComp->becomeEgg();
												   //otherPlayerLogicComp->timer = new Invoke(0.5f);
												   //otherPlayerLogicComp->invokeHelper = true;
												   //otherPlayerLogicComp->death = true;
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
		std::cout << "BEING LAUNCHED?" << std::endl;//Never called when launched
		//Called when hatching after death?
		logicComp->hatchBird(false);
		logicComp->launchable = false;
		logicComp->launchableZone = false;
		currLaunch = false;
	}

	if ((gameObjectRef->posX < 0) && (gameObjectRef->team == TEAM_PURPLE)){
		std::cout << "BEING LAUNCHED 2?" << std::endl;//Never called when launched
		//Called when hatching after death?
		logicComp->hatchBird(false);
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
	if (logicComp->death) std::cout << "DEATH TRUE!!!!!!!!!!!!" << std::endl;
	//if (!logicComp->death) std::cout << "DEATH FALSE!!!!!!!!!!!!" << std::endl;
	if (logicComp->isEgg){
		mBody->SetAngularVelocity(-5);
		gameObjectRef->rotation = mBody->GetAngle()*180/M_PI;
		//check if back at base yet
		if (logicComp->death && abs(gameObjectRef->posX) > 1300){//This way death gets set to true for whoever fired the feather but not the player who was killed, 
																 //enters this if and plays rooster noise for the player still alive
		//if (logicComp->invokeHelper && logicComp->timer->isDone() && abs(gameObjectRef->posX) > 1300){ 
		//if (abs(gameObjectRef->posX > 1300)){//Without invokeTimer never enters this just using catapult, can probably use this as the check
			logicComp->timer->destroy();
			logicComp->invokeHelper = false;
			logicComp->hatchBird(true);
			logicComp->death = false;
			std::cout << "BOTTOM IF TRIGGERED!!!!!!!!!!!!!!!" << std::endl;
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



