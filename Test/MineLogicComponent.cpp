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
	/*MineRenderComponent* renderComp = dynamic_cast<MineRenderComponent*>(gameObjectRef->GetComponent(COMPONENT_RENDER));
	SceneManager* sceneMan = SceneManager::GetSceneManager();
	renderComp->objRef->unrender();
	SDLRenderObject* poofSprite = sceneMan->InstantiateObject(sceneMan->findLayer("layer1"), 4001, gameObjectRef->posX, gameObjectRef->posY);
	renderComp->AssignSprite(poofSprite);*/
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

void MineLogicComponent::detonateMine(){
	// May need to scale up hitbox if we want blast radius larger than trigger radius
	// *NOTE*: We're not actually destroying the objects until the gamesession ends and the gameobject
	// destructor is called. Currently just getting rid of collisions and making object invisible
	gameObjectRef->isAlive = false;
	MinePhysicsComponent* physicsComp = dynamic_cast<MinePhysicsComponent*>(gameObjectRef->GetComponent(COMPONENT_PHYSICS));
	physicsComp->setCollisionFilter(COLLISION_MINE, 0);
}

void MineLogicComponent::checkTimer(){
	//if mine has been alive for too long, light the fuse so it doesn't stay forever
	clock_t clockDiff = clock() - timeSinceBirth;
	unsigned aliveTime = clockDiff / (CLOCKS_PER_SEC / 1000);
	//all mines will detonate after 20 seconds
	if (aliveTime > mineLength){
		//lightFuse();
		detonateMine();
		std::cout << "boom!" << std::endl;
	}
}

void MineLogicComponent::giveBirdseed(int numSeeds) {
	ClassComponent* classComp = dynamic_cast<ClassComponent*>(owner->GetComponent(COMPONENT_CLASS));
	if (classComp->currBirdseed + numSeeds <= classComp->maxsBirdseed){
		classComp->currBirdseed += numSeeds;
		createAbsorbParticle(gameObjectRef, owner, classComp->currBirdseed, 0, 0);
	}
	else classComp->currBirdseed = classComp->maxsBirdseed;
}

void MineLogicComponent::Update(){
	checkTimer();
	/*if (fuseLit){
		//removed delay timer for now
		clock_t clockDiff = clock() - timeSinceFuseLit;
		unsigned timeElapsed = clockDiff / (CLOCKS_PER_SEC / 1000);
		if (timeElapsed > 0){
			if(blownUp==0)blowUp();
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
	}*/
}