#include "BoomerangNetworkComponent.h"


BoomerangNetworkComponent::BoomerangNetworkComponent(GameObject* player){
	gameObjectRef = player;
	gameObjectRef->AddComponent(COMPONENT_NETWORK, this);
	prevClock = clock();
}


BoomerangNetworkComponent::~BoomerangNetworkComponent(){
}

void BoomerangNetworkComponent::Update(){
	float elapsedTime = double(clock() - prevClock)/CLOCKS_PER_SEC;
	//send update packet every half second
	if (elapsedTime > 500){

		prevClock = clock();
	}
}