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
	//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
	//not sure if next line is needed;
	//delete this;

}

void MinionPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(1, 1); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), 0);
	mBody->SetLinearVelocity(b2Vec2(50, 0));
	setCollisionFilter(COLLISION_MINION, COLLISION_FEATHER | COLLISION_MINION | COLLISION_BASE);
}

void MinionPhysicsComponent::handleCollision(GameObject* otherObj){
	//if hit, destroy minion or move it out of the alive_objects queue
	//std::cout << "MINION handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:

		gameObjectRef->setPos(-10000, 0);
		//setCollisionFilter(COLLISION_MINION, 0);
		gameObjectRef->isAlive = false;
		//GameObjects.dead_feathers.push_back(gameObjectRef);
		break;

	case GAMEOBJECT_TYPE::OBJECT_MINION:
		//just push each other around. Most likely done for us by box2d already
		//std::cout << "Value of coliding minion : " << otherObj->team  << "\n"<< std::endl;
		//std::cout << "Value of our minion : " << gameObjectRef->team << "\n" << std::endl;
		if (otherObj->team != gameObjectRef->team){
			std::cout << "shig buzz \n" << std::endl;
			gameObjectRef->setPos(-10000, 0);
			gameObjectRef->isAlive = false;
		
		}


		gameObjectRef->isAlive = false;
		break;
	case GAMEOBJECT_TYPE::OBJECT_BASE:{
		//Still need to trigger shake effect, visually update dmg to base
		//Currently destroys minions and updates base health logic
		gameObjectRef->setPos(-10000, 0);
		gameObjectRef->isAlive = false;

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
		gameObjectRef->setPos(-10000, 0);
		mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);
	}
	//temp testing code from here down
	if (gameObjectRef->team = 1){
			mBody->SetLinearVelocity(b2Vec2(10, 0));
	}else{
			mBody->SetLinearVelocity(b2Vec2(-10, 0));
	}
}

	