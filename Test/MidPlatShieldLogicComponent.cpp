#include "MidPlatShieldLogicComponent.h"


MidPlatShieldLogicComponent::MidPlatShieldLogicComponent(GameObject * shield)
{
	gameObjectRef = shield;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	timeSinceToggle = clock();
}

MidPlatShieldLogicComponent::~MidPlatShieldLogicComponent()
{
}

void MidPlatShieldLogicComponent::toggleShield(){

	if (!shieldtoggle){
		shieldtoggle = true;

		MidPlatShieldPhysicsComponent* physicsComp = dynamic_cast<MidPlatShieldPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
		//physicsComp->setCollisionFilter(COLLISION_PLATFORM, 0);
		physicsComp->setCollisionFilter(COLLISION_BASE, COLLISION_FEATHER);
		physicsComp->changeShape();

		timeSinceToggle = clock();

		//b2Shape* shape = physicsComp->mFixture->GetShape();

		//turn all sprites of player invisible
		MidPlatShieldRenderComponent* renderComp = dynamic_cast<MidPlatShieldRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
		renderComp->allObjs["button"]->visible = false;
		renderComp->allObjs["shield"]->visible = true;

		//convert collider to be a circle
		///physicsComp->mBody->SetFixedRotation(false);

		AudioManager* audioMan = AudioManager::getAudioInstance();
		audioMan->playByName("SFX_Shield.wav");
	}

}

void MidPlatShieldLogicComponent::resetShield(){

	if (shieldtoggle){

		MidPlatShieldPhysicsComponent* physicsComp = dynamic_cast<MidPlatShieldPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
		//physicsComp->setCollisionFilter(COLLISION_PLATFORM, 0);
		physicsComp->setCollisionFilter(COLLISION_SWITCH, COLLISION_FEATHER);
		timeSinceToggle = clock();

		//b2Shape* shape = physicsComp->mFixture->GetShape();

		MidPlatShieldRenderComponent* renderComp = dynamic_cast<MidPlatShieldRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));

		//turn all sprites of player invisible
		renderComp->allObjs["button"]->visible = true;
		renderComp->allObjs["shield"]->visible = false;

		//convert collider to be a circle
		///	physicsComp->mBody->SetFixedRotation(false);

		AudioManager* audioMan = AudioManager::getAudioInstance();
		audioMan->playByName("SFX_Shield.wav");

		shieldtoggle = false;

	}
}


void MidPlatShieldLogicComponent::Update(){

	clock_t clockDiff = clock() - timeSinceToggle;
	unsigned aliveTime = clockDiff / (CLOCKS_PER_SEC / 1000);
	if (clockDiff > 5000)
		resetShield();


	/*
	if (blownUp > 0){
	if (blownUp >= 2){ //after 2 frames, die
	//destroy self
	MidPlatShieldPhysicsComponent* physicsComp = dynamic_cast<MidPlatShieldPhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	physicsComp->setCollisionFilter(COLLISION_MINE, COLLISION_MINION | COLLISION_PLAYER);
	gameObjectRef->isAlive = false;
	}
	blownUp++;
	}
	*/

}