#include "Player.h"

Player::Player(){}

Player::Player(int playerID){
	//do initialization stuff here in the contructor
	//TODO: this is hard coded in to load the first object to be the reference
	//also requires there to be an object since it's hard coded for now

	ID = playerID;
	visible = true;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(posX, posY);
	//b2World world;
	//body = world.CreateBody(&bodyDef);
}

Player::Player(SDLRenderObject* obj){
	objRef = obj;
}

void Player::updateRef(){
	//Updates the related SDLRenderObject with the player's values
	//The SDLRenderObject is was is showed on screen, but is only 
	//a 'figurehead' for the player object 
	objRef->posX = posX;
	objRef->posY = posY;
	objRef->rotation = rotation;
	objRef->visible = visible;
	//there is most likely more attributes to send over. update as needed
}

void Player::updatePlayerFromInput(){
	//use the input manager to update the player
	//most of this function is prototype code
	cout << posX << "  ";
	InputManager* input = InputManager::getInstance();

	if (input->isKeyDown(KEY_RIGHT)) {
		posX += 2.0;

	}
	else if (input->isKeyDown(KEY_LEFT)) {
		posX += -2.0;

	}
	else if (input->isKeyDown(KEY_UP)) {
		posY += -2.0;

	}
	else if (input->isKeyDown(KEY_DOWN)) {
		posY += 2.0;
	}
	cout << posX << endl;
	cout << "ref:" << objRef->posX << endl;
}

void Player::updatePlayerFromNetwork(){
	//of the recieved packets, find the ones pertaining to this puppet
	//once found, process the packet
	//most likely free the packet after it has been processed.
	InputMemoryBitStream data = NetworkManager::sInstance->test.front();
	data.Read(posX);
	data.Read(posY);
	NetworkManager::sInstance->test.pop();
}

void Player::sendPlayerDataToNetwork(){
	OutputMemoryBitStream outData;
	outData.Write(NetworkManager::sInstance->kPosCC);
	outData.Write(ID);
	outData.Write(posX);
	outData.Write(posY);
	NetworkManager::sInstance->sendPacketToAllPeers(outData);
}

void Player::updatePhysics(){
	b2Vec2 pos = body->GetPosition();
	posX = pos.x;
	posY = pos.y;
	//do collision checks
}

void Player::update(){
	if (isNetworkControlled)updatePlayerFromNetwork();
	else updatePlayerFromInput();
	//updatePhysics();
	updateRef();
	sendPlayerDataToNetwork();


}