#include "MinionLogicComponent.h"
#include "ShrapnelExplosionParticle.h"
#include "DustCloudParticle.h"

MinionLogicComponent::MinionLogicComponent(GameObject* minion)
{
	gameObjectRef = minion;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


MinionLogicComponent::~MinionLogicComponent()
{
}

void MinionLogicComponent::Update(){
}

void MinionLogicComponent::MinionDeath(bool otherObjLocal){

	EffectObjectFactory efFactory;
	MinionRenderComponent * minRend = (MinionRenderComponent*)gameObjectRef->GetComponent(COMPONENT_RENDER);

	//Visual cues first
	//MinionRenderComponent* renderComp = dynamic_cast<MinionRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	//SceneManager* sceneMan = SceneManager::GetSceneManager();
	//renderComp->objRef->unrender();
	//SDLRenderObject* poofSprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer2"), 4001, gameObjectRef->posX, gameObjectRef->posY);
	//renderComp->AssignSprite(poofSprite);
	MinionPhysicsComponent* physicsComp = dynamic_cast<MinionPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	if (otherObjLocal)
		dynamic_cast<MinionNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK))->SendMinionDeath();
	if (!otherObjLocal) std::cout << "not ";
	std::cout << "local" << std::endl;
	physicsComp->setCollisionFilter(COLLISION_MINION, 0);
	// Need to make minion sprite invisible/gone, instantiate poofsprite at correct x,y , then 
	// start 1second timer, which destroys poof object when it runs out (set gameObjectRef->isAlive = false)
	//GameObjects.AddObject(efFactory.Spawn(gameObjectRef->posX, gameObjectRef->posY, EFFECT_EXPLOSION));
	createParticle(minRend->allObjs["body"], 20, gameObjectRef->posX, gameObjectRef->posY);
	createDustCloudParticle(2, 150, 200, gameObjectRef->posX, gameObjectRef->posY);

	gameObjectRef->setPos(-10000, 0);
	gameObjectRef->isAlive = false;
}