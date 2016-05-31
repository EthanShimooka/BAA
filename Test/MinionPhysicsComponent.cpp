#include "MinionPhysicsComponent.h"
#include "FanPhysicsComponent.h"
#include "ShrapnelExplosionParticle.h"
#include "DustCloudParticle.h"
#include "FanPhysicsComponent.h"

MinionPhysicsComponent::MinionPhysicsComponent(GameObject* minion, float _initialX, float _initialY, int team)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	gameObjectRef->team = team;
	init();
}

MinionPhysicsComponent::~MinionPhysicsComponent(){
	std::cout << "calling minion physics destructor" << std::endl;
	if (mBody){
		//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
	}
	//not sure if next line is needed;
	//delete this;

}

void MinionPhysicsComponent::init(){
	if (!mBody){
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
		bodyDef.angle = 0;// ... which direction it's facing

		GameWorld* gameWorld = GameWorld::getInstance();

		mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);


		b2PolygonShape box;
		box.SetAsBox(.8f, .8f); // look up other functions for polygons
		boxFixtureDef.shape = &box;
		boxFixtureDef.density = 1;
		mFixture = mBody->CreateFixture(&boxFixtureDef);
		mBody->SetUserData(gameObjectRef);
	}
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);

	float rando[10] = {
		-285,
		285,
		-100,
		50,
		-25,
		160,
		-240,
		60,
		-130,
		250
	};

	float yForce = rando[(gameObjectRef->ID%10)];
	if (gameObjectRef->team == TEAM_YELLOW){
		mBody->SetLinearVelocity(b2Vec2(7, 0));
		mBody->ApplyForce(b2Vec2(50, yForce), mBody->GetWorldCenter(), true);
	}
	else if (gameObjectRef->team == TEAM_PURPLE){
		mBody->SetLinearVelocity(b2Vec2(-7, 0));
		mBody->ApplyForce(b2Vec2(-50, yForce), mBody->GetWorldCenter(), true);
	}
	
	setCollisionFilter(COLLISION_MINION, COLLISION_FEATHER | COLLISION_MINION | COLLISION_BASE | COLLISION_MINE | COLLISION_FAN | COLLISION_PLATFORM);
	blownForce = b2Vec2(0.0f, 0.0f);
	savedYForce = 0.0f;

}

void MinionPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	//std::cout << "MINION handling collision with object ID: " << otherObj->ID << std::endl;

	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{
											 if (otherObj->team == gameObjectRef->team)break;
											 if (otherObj->isLocal){
												 AudioManager* audioMan = AudioManager::getAudioInstance();
												 audioMan->playByName("miniondeathsfx.ogg");
											 }
											 dynamic_cast<MinionNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->SendMinionDeath();
											 //createParticle(minRend->allObjs["body"], 20, gameObjectRef->posX, gameObjectRef->posY);
											 //createDustCloudParticle(4, 50, 200, gameObjectRef->posX, gameObjectRef->posY);
											 MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											 logicComp->MinionDeath();
											 
											 //GameObjects.dead_feathers.push_back(gameObjectRef);
											 break;
	}
	case GAMEOBJECT_TYPE::OBJECT_MINION:{
											//just push each other around. Most likely done for us by box2d already
											//std::cout << "Value of coliding minion : " << otherObj->team  << "\n"<< std::endl;
											//std::cout << "Value of our minion : " << gameObjectRef->team << "\n" << std::endl;
											if (otherObj->team != gameObjectRef->team){
												if (gameObjectRef->team == TEAM_YELLOW)
													std::cout << gameObjectRef->ID % 1000 << ", " << otherObj->ID % 1000 << ", " << gameObjectRef->posX << std::endl;
												//createParticle(minRend->allObjs["body"], 20, gameObjectRef->posX, gameObjectRef->posY);
												//createDustCloudParticle(4, 50, 200, gameObjectRef->posX, gameObjectRef->posY);
												MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
												logicComp->MinionDeath();
											}

											//gameObjectRef->isAlive = false;//currently setting the poof to dead,
											//w/o this obj keeps moving around
											break;
	}
	case GAMEOBJECT_TYPE::OBJECT_BASE:{
										  if (otherObj->team == gameObjectRef->team) break;
										  if (NetworkManager::sInstance->IsMasterPeer())
											  dynamic_cast<MinionNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->SendBaseHit(otherObj->team);
										  //createParticle(minRend->allObjs["body"], 20, gameObjectRef->posX, gameObjectRef->posY);
										  MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
										  logicComp->MinionDeath();
										  //gameObjectRef->setPos(-10000, 0);
										  //gameObjectRef->isAlive = false;
										  //Only shake if our own base is being attacked
										  if (gameObjectRef->team != GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
											  RenderManager* renderMan = RenderManager::getRenderManager();
											  renderMan->ShakeScreen(0.3f, 0.2f);
										  }
										  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_FAN:{

									 	 //mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, mBody->GetLinearVelocity().y-500));
								  	 	  FanPhysicsComponent* fanPhys = dynamic_cast<FanPhysicsComponent*>(otherObj->GetComponent(COMPONENT_PHYSICS));
										  blownForce = fanPhys->forceVec;
									 	  isGettingBlown = true;
									   	  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_PLATFORM:{
										  if (mBody->GetPosition().y < 0){
											  //hit top wall
											  mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, -mBody->GetLinearVelocity().y));
										  }
										  else {
											  //hit bot wall
											  mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, -mBody->GetLinearVelocity().y));
										  }
										  if (!isBounce){
											  savedYForce = -mBody->GetLinearVelocity().y;
										  }
										  isBounce = true;
										  ////Bounce off the walls
										  //b2Vec2 vel = mBody->GetLinearVelocity();
										  //vel.y = -1.0f * vel.y;
										  ////Ensure moving in right direction
										  //if (gameObjectRef->team == TEAM_YELLOW) vel.x = abs(vel.x);
										  //if (gameObjectRef->team == TEAM_PURPLE) vel.x = -abs(vel.x);
										  //mBody->SetLinearVelocity(vel);
										  //mBody->ApplyForce(b2Vec2(0, -50*mBody->GetLinearVelocity().y), mBody->GetWorldCenter(), true);
										  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_MINE:{

										  if (gameObjectRef->team == otherObj->team) break;
										  if (otherObj->isLocal){
											  AudioManager* audioMan = AudioManager::getAudioInstance();
											  audioMan->playByName("miniondeathsfx.ogg");
										  }
										 MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
										 logicComp->MinionDeath();
										 break;
	}
	default:
		break;
	}
}

void MinionPhysicsComponent::endCollision(GameObject* otherObj){
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_FAN: 
		isGettingBlown = false;
		blownForce = b2Vec2_zero;
		break;
	case GAMEOBJECT_TYPE::OBJECT_PLATFORM:
		isBounce = false;
		break;

	default:
		break;
	}
}

void MinionPhysicsComponent::Update(){
	if (gameObjectRef->isAlive){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}
	else{
		gameObjectRef->setPos(-10, 1000);
		mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);
	}
	if (isGettingBlown){
		if ((blownForce.x > 0 && mBody->GetLinearVelocity().x > 0) || (blownForce.x < 0 && mBody->GetLinearVelocity().x < 0)) {//if minion is moving positively and force is positive, apply force
 			mBody->ApplyForceToCenter(blownForce, false);
 		}
 		else {
 			mBody->ApplyForceToCenter(b2Vec2(0, blownForce.y), false);
 		}
		//mBody->ApplyForceToCenter(blownForce, false);
	}
	if (isBounce) {
		mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, -savedYForce));
	}
	//temp testing code from here down


	/*
	if (gameObjectRef->team == 1){
			mBody->SetLinearVelocity(b2Vec2(-10, 0));
	}else{
			mBody->SetLinearVelocity(b2Vec2(10, 0));
	}*/
	
}

void MinionPhysicsComponent::DestroyMinion(){
	gameObjectRef->setPos(-10, 1000);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);
	gameObjectRef->isAlive = false;
}