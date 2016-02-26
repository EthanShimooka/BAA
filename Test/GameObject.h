#pragma once

#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "include\SceneManager.h"
#include "Component.h"
#include <iostream>
#include <vector>

//#include "include\network\Command.h"



struct t_component {
	int type;
	Component * component;

};

class GameObject
{

private:
	/// Dynamic List of components
	std::vector<t_component> g_components;
	int component_count;
protected:

public:
	/// Object ID
	int ID;

	GameObject();
	~GameObject();

	float posX;
	float posY;
	float rotation;


	/// virtual update function
	virtual void update(){};


	void AddComponent(int c_type, Component* comp);

///	void AttachComponent(ComponentType, argumentList, name);

///	void DetachComponent(name)
		
	void UpdateComponents();

///	void UpdateComponentType(ComponentType typeOfComponentToUpdate);

///	void HandleMessage(MessageType message);// echoes to all attached components


	void UpdateComponentByType(int c_type);

};

#endif