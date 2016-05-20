#include "MidBasePhysicsComponent.h"


MidBasePhysicsComponent::MidBasePhysicsComponent(GameObject * base)
{
	gameObjectRef = base;
	gameObjectRef->AddComponent(COMPONENT_PHYSICS, this);
	Init();

}

MidBasePhysicsComponent::~MidBasePhysicsComponent()
{
}

void MidBasePhysicsComponent::Init(){

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(gameObjectRef->posX, gameObjectRef->posY);

	bodyDef.angle = 0;// ... which direction it's facing

	GameWorld* gameWorld = GameWorld::getInstance();
	mBody = gameWorld->getPhysicsWorld()->CreateBody(&bodyDef);

	/// Hitbox instantiation
	b2PolygonShape box;
	/// Set Box Shape
	box.SetAsBox(5.5f, 12.7f); // look up other functions for polygons
	// 
	boxFixtureDef.shape = &box;
	boxFixtureDef.density = 1;
	// Create Fixture 
	mFixture = mBody->CreateFixture(&boxFixtureDef);
	mBody->SetUserData(gameObjectRef);
	mBody->SetTransform(b2Vec2(gameObjectRef->posX / worldScale, gameObjectRef->posY / worldScale), 0);

	//if base is same team as local player
	if (gameObjectRef->team == GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
		setCollisionFilter(COLLISION_BASE, COLLISION_FEATHER | COLLISION_MINION);
	}
	else {
		setCollisionFilter(COLLISION_BASE, COLLISION_FEATHER | COLLISION_MINION | COLLISION_PLAYER);
	}
}

void MidBasePhysicsComponent::handleCollision(GameObject* otherObj){
	//std::cout << "FEATHER handling collision with object ID: " << otherObj->ID << std::endl;
	//probably destroy itself, maybe trigger a sound?
	switch (otherObj->type){
	case GAMEOBJECT_TYPE::OBJECT_FEATHER:{								
							         		break;
	}

	case GAMEOBJECT_TYPE::OBJECT_MINION:{
											 // chack to see if it is of opposing minion type
											if (otherObj->team == gameObjectRef->team) break;
											 std::cout << "base hit! \n" << std::endl;
											 base_hit = true;
											 // MidBaseLogicComponent* logicComponent = dynamic_cast<MidBaseLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
											 // logicComponent->attacked();
											 gameObjectRef->health++;
											 std::cout << "Health = " << gameObjectRef->health << std::endl;
											 //
											 //		}

											 break;
	}

		
	case GAMEOBJECT_TYPE::OBJECT_PLAYER:{
											//Do nothing, triggers collision between base/player of opposing team
											break;
	}

	default:
		break;
	}
}

void MidBasePhysicsComponent::Update(){




}