#include "MineLogicComponent.h"


MineLogicComponent::MineLogicComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_LOGIC, this);
}


MineLogicComponent::~MineLogicComponent(){
}

void MineLogicComponent::blowUp(){
	gameObjectRef->isAlive = false;
	//TODO: instaniate an explosion, and destroy everything touching explosion
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
			blowUp();
		}
	}
}