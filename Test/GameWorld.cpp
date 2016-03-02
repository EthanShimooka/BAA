#include "GameWorld.h"

GameWorld* GameWorld::gameWorld = nullptr;

GameWorld::GameWorld(){
	//initialize the class here
	//Note: hardcoded gravity for testing
	const b2Vec2 gravity =  b2Vec2(0, 1000);
	physicsWorld = new b2World(gravity);
	currTime = clock();
}

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

void GameWorld::update(){
	//TODO: replace first hardcoded value of time length to actual time since last frame
	//the last two values are how many calculations are done within this time period. Higher is
	// more precise, but more computationally intensive
	double fps = (clock() - currTime+1) / (double)(CLOCKS_PER_SEC / 1000);
	currTime = clock();
	physicsWorld->Step(1/fps,5,5);
}