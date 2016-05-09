#include "MineLogicComponent.h"

MineLogicComponent::MineLogicComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
	timeSinceBirth = clock();
}


MineLogicComponent::~MineLogicComponent(){
}

//starts process of blowing up, ends in update
void MineLogicComponent::blowUp(){ 
	blownUp++;
	//TODO: instaniate an explosion, and destroy everything touching explosion
	MinePhysicsComponent* physicsComp = dynamic_cast<MinePhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	physicsComp->setCollisionFilter(COLLISION_MINE, COLLISION_MINION | COLLISION_PLAYER);
	MineRenderComponent* renderComp = dynamic_cast<MineRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderComp->objRef->unrender();
	SDLRenderObject* poofSprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 4001, gameObjectRef->posX, gameObjectRef->posY);
	renderComp->AssignSprite(poofSprite);
	//scale collider larger. if we need to scale hitbox, do it here
	//b2Shape* shape = physicsComp->mFixture->GetShape();
}

void MineLogicComponent::lightFuse(){
	if (!fuseLit){
		MinePhysicsComponent* physicsComp = dynamic_cast<MinePhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
		fuseLit = true;
		physicsComp->setCollisionFilter(COLLISION_MINE, 0);
		timeSinceFuseLit = clock();
	}
}

void MineLogicComponent::Update(){
	//if mine has been alive for too long, light the fuse so it doesn't stay forever
	clock_t clockDiff = clock() - timeSinceBirth;
	unsigned aliveTime = clockDiff / (CLOCKS_PER_SEC / 1000);
	//all mines will light their fuses after 20 seconds
	if (aliveTime > 20000){
		lightFuse();
		std::cout << "boom!" << std::endl;
	}
	if (fuseLit){
		//removed delay timer for now
		/*clock_t clockDiff = clock() - timeSinceFuseLit;
		unsigned timeElapsed = clockDiff / (CLOCKS_PER_SEC / 1000);
		if (timeElapsed > 0){
			if(blownUp==0)*/blowUp();
		//}
	}
	if (blownUp>0){
		if (blownUp >= 2){ //after 2 frames, die
			//destroy self
			MinePhysicsComponent* physicsComp = dynamic_cast<MinePhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
			physicsComp->setCollisionFilter(COLLISION_MINE, COLLISION_MINION | COLLISION_PLAYER);
			gameObjectRef->isAlive = false;
		}
		blownUp++;
	}
}