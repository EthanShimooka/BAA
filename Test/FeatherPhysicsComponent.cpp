#include "FeatherPhysicsComponent.h"
#include "MidBaseLogicComponent.h"


FeatherPhysicsComponent::FeatherPhysicsComponent(GameObject* feather, float initX, float initY, float dx, float dy, float speed)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(initX,  initY,  dx,  dy, speed);
}
FeatherPhysicsComponent::~FeatherPhysicsComponent(){
	//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
}

void FeatherPhysicsComponent::init(float initX, float initY, float dx, float dy, float speed){
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
	gameObjectRef->posX = initX;
	gameObjectRef->posY =  initY;
	float xAngle = dx - initX;
	if (xAngle == 0)xAngle = 0.00001f;
	gameObjectRef->rotation = (float)(atan((dy - initY) / (xAngle)) / M_PI * 180);
	//gameObjectRef->flipH = !(dx-initX < 0);
	if (dx - initX < 0) gameObjectRef->rotation += 180;
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), gameObjectRef->rotation / (float)(180.0 * M_PI));

	// have to play with the ratio to find a good solution
	float magnitude = sqrt(pow((dx - initX), 2) + pow((dy - initY), 2));
	mBody->SetLinearVelocity(b2Vec2(((dx - initX) / magnitude) * speed, ((dy - initY) / magnitude) * speed));
}

void FeatherPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "FEATHER handling collision with object ID: " << otherObj->ID << std::endl;
	//probably destroy itself, maybe trigger a sound?
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_MINION:{
											//give birdseed
											if (otherObj->team == gameObjectRef->team)break;
											if (gameObjectRef->isLocal)
												dynamic_cast<FeatherLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC))->giveBirdseed(1);
											//destroy self or return to object pool
											gameObjectRef->isAlive = false;
											break;
	}
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:{
											//destroy self or return to object pool
											//birdseed assigned in PlayerPhysicsComponent
											if (otherObj->team == gameObjectRef->team)break;
											gameObjectRef->isAlive = false;
											break;
	}
	case GAMEOBJECT_TYPE::OBJECT_BASE:{
										  //destroy self or return to object pool
										// dynamic_cast<MidBaseLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC))->attacked();
										  if (otherObj->team == gameObjectRef->team)break;
										  gameObjectRef->isAlive = false;
										  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_LAUNCHER:{
									      //std::cout << "FEATHER handling collision with object ID: " << otherObj->ID << "SHIG" << std::endl;

										  gameObjectRef->isAlive = false;
										  break;
	}
	case GAMEOBJECT_TYPE::OBJECT_POWERSHIELD:{
											//std::cout << "FEATHER handling collision with object ID: " << otherObj->ID << "SHIG" << std::endl;
											if (otherObj->team != gameObjectRef->team) gameObjectRef->isAlive = false;
											break;
	}
	default:
		break;
}
}

void FeatherPhysicsComponent::Update() {
	if (gameObjectRef->isAlive){
		gameObjectRef->posX = mBody->GetPosition().x*worldScale;
		gameObjectRef->posY = mBody->GetPosition().y*worldScale;
	}
	else{
		gameObjectRef->setPos(-10000, 0);
		mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);
	}
}
