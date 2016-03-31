#include "FeatherPhysicsComponent.h"


FeatherPhysicsComponent::FeatherPhysicsComponent(GameObject* feather, float initX, float initY, float dx, float dy)
{
	gameObjectRef = feather;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	init(initX,  initY,  dx,  dy);
}
FeatherPhysicsComponent::~FeatherPhysicsComponent(){
	//GameWorld::getInstance()->physicsWorld->DestroyBody(mBody);
}

void FeatherPhysicsComponent::init(float initX, float initY, float dx, float dy){
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

	setCollisionFilter(COLLISION_FEATHER, COLLISION_MINION);
	
	//handle init stuff for positions
	gameObjectRef->posX = initX;
	gameObjectRef->posY =  initY;
	float xAngle = dx - initX;
	if (xAngle == 0)xAngle == 0.00001;
	gameObjectRef->rotation = atan((dy - initY) / (xAngle)) / M_PI * 180;
	gameObjectRef->flipH = !(dx-initX > 0);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX/worldScale, gameObjectRef->posY/worldScale), gameObjectRef->rotation / 180.0 * M_PI);
	mBody->SetLinearVelocity(b2Vec2(dx - initX, dy - initY));
}

void FeatherPhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "FEATHER handling collision with object ID: " << otherObj->ID << std::endl;
	//probably destroy itself, maybe trigger a sound?
	switch (otherObj->type){
		case GAMEOBJECT_TYPE::OBJECT_MINION:
		{
			//destroy self or return to object pool
			gameObjectRef->isAlive = false;
			GameObjects.dead_feathers.push_back(gameObjectRef);
			break;
		}
		case GAMEOBJECT_TYPE::OBJECT_PLAYER:
			//destroy self or return to object pool
			break;
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
		/*for (int i = 0; i < GameObjects.alive_objects.size(); i++){
			if (GameObjects.alive_objects[i] == gameObjectRef){
				GameObjects.alive_objects.erase(GameObjects.alive_objects.begin() + i);
				break;
			}
		}*/
	}
	
	//mBody->SetTransform(b2Vec2(gameObjectRef->posX, gameObjectRef->posY), gameObjectRef->rotation / 180.0 * M_PI);
}