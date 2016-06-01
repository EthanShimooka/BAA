#include "NetworkComponent.h"


NetworkComponent::NetworkComponent()
{
}


NetworkComponent::~NetworkComponent()
{
}


void NetworkComponent::Update(){
	
}

bool NetworkComponent::canSend(){
	clock_t difference = clock() - lastTimeSent;
	unsigned time = difference / (CLOCKS_PER_SEC / 1000);
	if (time >= interval){
		lastTimeSent = clock();
		return true;
	}
	return false;
}