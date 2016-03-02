#include "PlayerInputComponent.h"


PlayerInputComponent::PlayerInputComponent()
{
}


PlayerInputComponent::~PlayerInputComponent()
{
}


void PlayerInputComponent::Update()
{
	//use the input manager to update the player
	//most of this function is prototype code

	InputManager* input = InputManager::getInstance();

	if (input->isKeyDown(KEY_RIGHT)) {
		gameObjectRef->posX += 2.0;
		gameObjectRef->flipH = false;
	}
	if (input->isKeyDown(KEY_LEFT)) {
		gameObjectRef->posX += -2.0;
		gameObjectRef->flipH = true;

	}
	if (input->isKeyDown(KEY_UP)) {
		gameObjectRef->posY += -2.0;

	}
	if (input->isKeyDown(KEY_DOWN)) {
		gameObjectRef->posY += 2.0;
	}

	if (input->isMouseDown(MOUSE_LEFT)){
		PlayerLogicComponent* logic = dynamic_cast<PlayerLogicComponent*>(gameObjectRef->GetComponent(COMPONENT_LOGIC));
		logic->spawnFeather(input->getMouseX(), input->getMouseY());
		PlayerNetworkComponent* net = dynamic_cast<PlayerNetworkComponent*>(gameObjectRef->GetComponent(COMPONENT_NETWORK));
		OutputMemoryBitStream featherPacket;
		featherPacket.Write(NetworkManager::sInstance->kPosCC);
		featherPacket.Write(gameObjectRef->ID);
		featherPacket.Write(2);
		featherPacket.Write(0);
		featherPacket.Write(gameObjectRef->posX);
		featherPacket.Write(gameObjectRef->posY);
		featherPacket.Write(input->getMouseX());
		featherPacket.Write(input->getMouseY());
		net->outgoingPackets.push(&featherPacket);
	}


}

