#pragma once

#include "include\box2D\Box2D.h"
class GameWorld{
protected:
	// constructor only called by getInstance()
	GameWorld();
	GameWorld(GameWorld const&) {};
	void operator=(GameWorld const&) {};

	// single instance of InputManager
	static GameWorld* gameWorld;
public:
	b2World* physicsWorld;
	static GameWorld* getInstance();
	b2World* getPhysicsWorld();
	~GameWorld();
};

