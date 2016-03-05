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
	int component_count;
protected:

public:
	/// Constructor
	GameObject();
	/// Constructor
	GameObject(float x, float y);
	/// Destructor
	~GameObject();

	/// Object ID
	uint64_t ID;
	/// Alive state
	bool isAlive;
	/// type of game object
	int type;
	///World X Position
	float posX;
	///World Y Position
	float posY;
	///Rotation
	float rotation;

	///Horizontal Flip
	bool flipH;
	///Vertical Flip
	bool flipV;
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
	OBJECT_PLAYER,
	OBJECT_MINION,
	OBJECT_PLATFORM,
	OBJECT_SWTICH,
	OBJECT_FEATHER,
	//we can keep on adding more as needed
};

#endif