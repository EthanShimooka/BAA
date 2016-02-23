#pragma once

#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "include\SceneManager.h"
#include <iostream>

class GameObject
{
public:
	vector<Command*> commands;
	GameObject();
	~GameObject();
	virtual void update(){};
};

#endif