#pragma once

#include "include\box2D\Box2D.h"
#include <time.h>
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
	void update();
	~GameWorld();
};

