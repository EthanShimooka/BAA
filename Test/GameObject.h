/**
*  GameObject.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	Game Object serves as the "Entity" of the Entity-Component-System
	pattern. The GameObject is essentially a component bag, with methods
	for component access and the overall objects "world position".

	(It was more trouble than it was worth to abstract the x and y pos).

*/


#pragma once

#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "include\SceneManager.h"
#include "Component.h"
#include <iostream>
#include <vector>

//#include "include\network\Command.h"

/// t_component struct contains a component and a int enumerating its type
/// used anytime trying to find a certain component of GameObject (entitiy)
struct t_component {
	int type;
	Component * component;

};


/// GameObject (entity) main class

class GameObject
{

private:
	/// Dynamic List of components
	std::vector<t_component> g_components;
	/// Number of Components Bound to GameObject
	//int component_count;
protected:

public:
	/// Constructor
	GameObject();
	/// Constructor
	GameObject(float x, float y);
	/// Destructor
	~GameObject();

	/// Object ID
	uint64_t ID = 0;
	/// Alive state
	bool isAlive;
	/// True if the local player made this object
	bool isLocal;
	/// type of game object
	int type;
	/// Object team
	int team;
	///World X Position
	float posX;
	///World Y Position
	float posY;
	///Rotation
	float rotation;
	/// scale X
	float scaleX ;
	/// scale Y
	float scaleY ;
	///Horizontal Flip
	bool flipH ;
	///Vertical Flip
	bool flipV ;
	/// Health
	int health;
	/// virtual update function
	virtual void update(){};

	/// Adds Component. See Component.h for list of ENUM types (c_type)
	void AddComponent(int c_type, Component* comp);

	/// Updates ALL components belonging in g_components
	void UpdateComponents();

	/// Updates Component of selected ENUM type (c_type). See Component.h for list of types.
	void UpdateComponentByType(int c_type);

	/// Gets the list of components for this object
	Component* GetComponent(int c_type);

	/// Set postion of gameObject
	void setPos(float x, float y);

	/// Frees memory of all components attached to gameobject
	static void FreeComponents(GameObject* toFree);
	/// To Be Implemented

///	void AttachComponent(ComponentType, argumentList, name);

///	void DetachComponent(name)
		

///	void UpdateComponentType(ComponentType typeOfComponentToUpdate);

///	void HandleMessage(MessageType message);// echoes to all attached components



};

enum GAMEOBJECT_TYPE {
	OBJECT_PLAYER = 0,
	OBJECT_MINION = 1,
	OBJECT_PLATFORM = 2,
	OBJECT_SWITCH = 3,
	OBJECT_FEATHER = 4,
	OBJECT_POWERSHIELD = 5,
	OBJECT_BASE = 6,
	OBJECT_MINE = 7,
	OBJECT_EFFECT = 8,
	OBJECT_FAN = 9,
	OBJECT_PARTICLE = 10, //change later, maybe
	//we can keep on adding more as needed
	OBJECT_BOOMERANG = 11,
	OBJECT_BUTTON = 12,
};

//DO NOT CHANGE ENUM ORDER
enum TEAM{
	TEAM_NEUTRAL = 0,
	TEAM_YELLOW = 1,
	TEAM_PURPLE = 2,
};

#endif