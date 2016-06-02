#include "BoomerangPhysicsComponent.h"


BoomerangPhysicsComponent::BoomerangPhysicsComponent(GameObject* boomerang, GameObject* _owner, int destX, int destY){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	targetDest = b2Vec2(destX/worldScale, destY/worldScale); 
	owner = _owner;
	ownerPhysics = dynamic_cast<PlayerPhysicsComponent*>(_owner->GetComponent(COMPONENT_PHYSICS));
	init();
}

void BoomerangPhysicsComponent::init(){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);
	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	if (!mBody)
		mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox(1, 1); // look up other functions for polygons
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	boxFixtureDef.isSensor = true;
	if (!mFixture)
		mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);

	setCollisionFilter(COLLISION_FEATHER, COLLISION_MINION | COLLISION_PLAYER);

	//handle init stuff for positions
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), gameObjectRef->rotation / (float)(180.0 * M_PI));

}

BoomerangPhysicsComponent::~BoomerangPhysicsComponent(){
}

void BoomerangPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "MINE handling collision with object ID: " << otherObj->ID << std::endl;
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:
		//check to see what team it's affiliated with, and detonate if needed
		if (otherObj == owner && returning){
			PlayerRenderComponent* ownerRenderComp = dynamic_cast<PlayerRenderComponent*>(otherObj->GetComponent(COMPONENT_RENDER));
			ownerRenderComp->allObjs["armL"]->visible = true;
			ownerRenderComp->allObjs["armR"]->visible = true;
			gameObjectRef->isAlive = false;
		}
		if (otherObj->team != gameObjectRef->team){
			//maybe kill the other teammates?
			std::cout << "boomerang hit enemy player" << std::endl;
			otherObj->isAlive = false;
		}
		break;
	case  GAMEOBJECT_TYPE::OBJECT_MINION:
		//check to see what team it's affiliated with, and detonate if needed
		if (otherObj->team != gameObjectRef->team){
			//if hit a minion, kill the minion
			if (gameObjectRef->isLocal){
				AudioManager* audioMan = AudioManager::getAudioInstance();
				audioMan->playByName("miniondeathsfx.ogg");
			}
			MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
			logicComp->MinionDeath(gameObjectRef->isLocal);
			otherObj->isAlive = false;
		}
		break;
	default:
		break;
	}
}

void BoomerangPhysicsComponent::Update(){
	int moveSpeed = 15;
	if (returning){
		//straight line back
		b2Vec2 currPos = mBody->GetPosition();
		b2Vec2 destPos = ownerPhysics->mBody->GetPosition();
		b2Vec2 movementVec = destPos - currPos;

		movementVec.Normalize();
		movementVec *= (float32)moveSpeed;
		mBody->SetLinearVelocity(movementVec);
	}
	else{
		//curve to destination
		b2Vec2 currPos = mBody->GetPosition();
		b2Vec2 movementVec = targetDest - currPos;
		//check to see how close we are
		movementVec.Normalize();
		movementVec *= (float32)moveSpeed;
		mBody->SetLinearVelocity(movementVec);
	}
	gameObjectRef->posX = mBody->GetPosition().x*worldScale;
	gameObjectRef->posY = mBody->GetPosition().y*worldScale;
}