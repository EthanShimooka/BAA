#pragma once

#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "include\SceneManager.h"
#include <iostream>
#include <vector>
//#include "include\network\Command.h"

class GameObject
{
public:
//	std::vector< Command* > commands;
	GameObject();
	~GameObject();
	virtual void update(){};
};

#endif