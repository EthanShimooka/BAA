#include "GameWorld.h"

GameWorld* GameWorld::gameWorld = nullptr;

GameWorld::GameWorld(){}

GameWorld::~GameWorld(){}

GameWorld* GameWorld::getInstance() {
	// if gameWorld is nullptr
	if (!gameWorld) {
		gameWorld = new GameWorld();
	}
	return gameWorld;
}

b2World* GameWorld::getPhysicsWorld(){
	return physicsWorld;
}
