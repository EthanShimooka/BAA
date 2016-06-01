#include "MidBasePhysicsComponent.h"
#include "Stats.h"

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
											 base_hit = true;

											 //std::cout << "Health = " << gameObjectRef->health << std::endl;
											 MidBaseRenderComponent* renderComp = dynamic_cast<MidBaseRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
											 renderComp->setAnimation("damage");
											 renderComp->setNextAnimation("idle");

											 if (NetworkManager::sInstance->IsMasterPeer()){
												 gameObjectRef->health++;
												 Stats::incBaseHealth(gameObjectRef->team);
												 dynamic_cast<MidBaseNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->SendBaseHealth();
											 }
											 MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
											 logicComp->MinionDeath();
											 if (otherObj->team != GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
												RenderManager* renderMan = RenderManager::getRenderManager();
												renderMan->ShakeScreen(0.3f, 0.2f);
											}

											 //if (gameObjectRef->team == TEAM_YELLOW && NetworkManager::sInstance->IsMasterPeer()){
												// dynamic_cast<MinionNetworkComponent*>(otherObj->GetComponent(COMPONENT_NETWORK))->SendBaseHit(TEAM_YELLOW, otherObj->ID, gameObjectRef->ID);
												// gameObjectRef->health++;
												// MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
												// logicComp->MinionDeath();
												// //Only shake if our own base is being attacked
												// if (otherObj->team != GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
												//	 RenderManager* renderMan = RenderManager::getRenderManager();
												//	 renderMan->ShakeScreen(0.3f, 0.2f);
												// }
												// Stats::incBaseHealth_yellow();
											 //}
											 //else if (gameObjectRef->team == TEAM_PURPLE && NetworkManager::sInstance->IsMasterPeer()){
												// dynamic_cast<MinionNetworkComponent*>(otherObj->GetComponent(COMPONENT_NETWORK))->SendBaseHit(TEAM_PURPLE, otherObj->ID, gameObjectRef->ID);
												// gameObjectRef->health++;
												// MinionLogicComponent* logicComp = dynamic_cast<MinionLogicComponent*>(otherObj->GetComponent(COMPONENT_LOGIC));
												// logicComp->MinionDeath();
												// //Only shake if our own base is being attacked
												// if (otherObj->team != GameObjects.GetGameObject(GamerServices::sInstance->GetLocalPlayerId())->team){
												//	 RenderManager* renderMan = RenderManager::getRenderManager();
												//	 renderMan->ShakeScreen(0.3f, 0.2f);
												// }
												// Stats::incBaseHealth_purple();
											 //}

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