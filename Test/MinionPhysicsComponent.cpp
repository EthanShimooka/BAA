#include "MinionPhysicsComponent.h"

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
		box.SetAsBox(.5, .5); // look up other functions for polygons
		boxFixtureDef.shape = &box;
		boxFixtureDef.density = 1;
		mFixture = mBody->CreateFixture(&boxFixtureDef);
		mBody->SetUserData(gameObjectRef);
	}
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);
	mBody->SetLinearVelocity(b2Vec2(5, 0));
	//int yForce = rand() % 50 + 250;
	int yForce = rand() % 350 - 350;
	if (gameObjectRef->team == TEAM_PURPLE){
		mBody->SetLinearVelocity(b2Vec2(5, 0));
	}
	else if (gameObjectRef->team == TEAM_YELLOW){
		mBody->SetLinearVelocity(b2Vec2(-5, 0));
	}
	mBody->ApplyForce(b2Vec2(100, yForce), mBody->GetWorldCenter(), true);
	setCollisionFilter(COLLISION_MINION, COLLISION_FEATHER | COLLISION_MINION | COLLISION_BASE | COLLISION_MINE | COLLISION_FAN | COLLISION_PLATFORM);
}

void MinionPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	//std::cout << "MINION handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{
											 if (otherObj->team == gameObjectRef->team)break;
											 //Cue Audio/Visual death (UPDATE: Audio is placeholder)
											 AudioManager* audioMan = AudioManager::getAudioInstance();
											 audioMan->playByName("coinjingling.ogg");//Going to be different audio asset in each case
											dynamic_cast<MinionNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->SendMenionDeath();
											 MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
											 logicComp->MinionDeath();

											 gameObjectRef->setPos(-10000, 0);
											 //setCollisionFilter(COLLISION_MINION, 0);
											 gameObjectRef->isAlive = false;
											 //GameObjects.dead_feathers.push_back(gameObjectRef);
											 break;
	}
	case GAMEOBJECT_TYPE::OBJECT_MINION:{
											//just push each other around. Most likely done for us by box2d already
											//std::cout << "Value of coliding minion : " << otherObj->team  << "\n"<< std::endl;
											//std::cout << "Value of our minion : " << gameObjectRef->team << "\n" << std::endl;
											if (otherObj->team != gameObjectRef->team){
												//std::cout << "shig buzz \n" << std::endl;
												//Cue Audio/Visual death (UPDATE: Audio is placeholder)
												AudioManager* audioMan = AudioManager::getAudioInstance();
												std::cout << "MINION ON MINION COLLISION" << std::endl;
												audioMan->playByName("coinjingling.ogg");//Going to be different audio asset in each case

												MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
												logicComp->MinionDeath();
												gameObjectRef->setPos(-10000, 0);
												gameObjectRef->isAlive = false;

											}


											//gameObjectRef->isAlive = false;//currently setting the poof to dead,
											//w/o this obj keeps moving around
											break;
	}
	case GAMEOBJECT_TYPE::OBJECT_BASE:{
										  //Still need to visually update dmg to base
										  //Currently destroys minions, updates base health logic, and shakes screen
										  AudioManager* audioMan = AudioManager::getAudioInstance();
										  audioMan->playByName("coinjingling.ogg");//Going to be different audio asset in each case

										  MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
										  logicComp->MinionDeath();

										  gameObjectRef->setPos(-10000, 0);
										  gameObjectRef->isAlive = false;
										  RenderManager* renderMan = RenderManager::getRenderManager();
										  renderMan->ShakeScreen(0.3f, 0.4f);
										  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_FAN:{
										 //otherObj;
										//mBody->SetLinearVelocity(b2Vec2(mBody->GetLinearVelocity().x, mBody->GetLinearVelocity().y-500));
										  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_PLATFORM:{
											  //Bounce off the walls
											  b2Vec2 vel = mBody->GetLinearVelocity();
											  //mBody->SetLinearVelocity(b2Vec2(vel.x, vel.y));
											  mBody->ApplyForce(b2Vec2(0, 50), mBody->GetWorldCenter(), true);
											  break;
	}
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
	