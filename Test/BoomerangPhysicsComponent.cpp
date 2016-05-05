#include "BoomerangPhysicsComponent.h"


BoomerangPhysicsComponent::BoomerangPhysicsComponent(GameObject* boomerang, GameObject* _owner, int destX, int destY){
	gameObjectRef = boomerang;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	targetDest = b2Vec2(destX, destY); 
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

	if (gameObjectRef->isLocal)
		setCollisionFilter(COLLISION_FEATHER, COLLISION_MINION | COLLISION_BASE | COLLISION_SWITCH | COLLISION_PLAYER | COLLISION_POWERSHIELD);
	else
		setCollisionFilter(COLLISION_FEATHER, COLLISION_BASE | COLLISION_SWITCH | COLLISION_POWERSHIELD);

	//handle init stuff for positions
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), gameObjectRef->rotation / (float)(180.0 * M_PI));

}

BoomerangPhysicsComponent::~BoomerangPhysicsComponent(){
}

void BoomerangPhysicsComponent::Update(){
	if (returning){
		//straight line back
		b2Vec2 currPos = mBody->GetPosition();
		b2Vec2 destPos = ownerPhysics->mBody->GetPosition();
		b2Vec2 movementVec = destPos - currPos;
		//check to see how close we are
		if (movementVec.Length() < 1){
			returning = true;
		}
		movementVec.Normalize();
		movementVec *= 4;
		mBody->SetLinearVelocity(movementVec);
	}
	else{
		//curve to destination
		b2Vec2 currPos = mBody->GetPosition();
		b2Vec2 destPos = ownerPhysics->mBody->GetPosition();
		b2Vec2 movementVec = destPos - currPos;
		//check to see how close we are
		if (movementVec.Length() < 1){
			returning = true;
		}
	}
}