#include "MineLogicComponent.h"


MineLogicComponent::MineLogicComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


MineLogicComponent::~MineLogicComponent(){
}

void MineLogicComponent::blowUp(){
	blownUp++;
	//TODO: instaniate an explosion, and destroy everything touching explosion
	MinePhysicsComponent* physicsComp = dynamic_cast<MinePhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	physicsComp->setCollisionFilter(COLLISION_MINE, COLLISION_MINION | COLLISION_PLAYER);
	//scale collider larger. if we need to scale hitbox, do it here
	//b2Shape* shape = physicsComp->mFixture->GetShape();
}

void MineLogicComponent::lightFuse(){
	if (!fuseLit){
		fuseLit = true;
		timeSinceFuseLit = clock();
	}
}

void MineLogicComponent::Update(){
	if (fuseLit){
		clock_t clockDiff = clock() - timeSinceFuseLit;
		unsigned timeElapsed = clockDiff / (CLOCKS_PER_SEC / 1000);
		if (timeElapsed > 1000){
			if(blownUp==0)blowUp();
		}
	}
	if (blownUp>0){
		if (blownUp >= 2){
			//destroy self
			gameObjectRef->isAlive = false;
		}
		blownUp++;
	}
}