#include "Player.h"

Player::Player(){}

Player::Player(uint64_t playerID, int x, int y){
	//do initialization stuff here in the contructor
	//TODO: this is hard coded in to load the first object to be the reference
	//also requires there to be an object since it's hard coded for now
	//setPlayerID();
	ID = playerID;
	visible = true;
	posX = x;
	posY = y;

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
}

void Player::updatePlayerFromNetwork(){
	//of the recieved packets, find the ones pertaining to this puppet
	//once found, process the packet
	//most likely free the packet after it has been processed.
	
	while (!commands.empty()){
		InputMemoryBitStream packet = commands.front();
		commands.pop();

		int mCommand;
		packet.Read(mCommand);
		switch (mCommand){
		case Command::CM_ABILITY:
			//handle 
			break;
		case Command::CM_ATTACK:
			//handle 
			break;
		case Command::CM_DIE:
			//handle 
			break;
		case Command::CM_INVALID:
			//handle 
			break;
		case Command::CM_JUMP:
			//handle 
			break;
		case Command::CM_MOVE:
			//handle movement
			InputMemoryBitStream data = NetworkManager::sInstance->test.front();
			data.Read(posX);
			data.Read(posY);
			break;
		}
	}


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
	if (!isNetworkControlled)updatePlayerFromInput();
	//updatePhysics();
	updateRef();
	sendPlayerDataToNetwork();


}

void Player::setPlayerID(){
	ID = NetworkManager::sInstance->GetMyPlayerId();
}