#pragma once

#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "include\SceneManager.h"
#include "Component.h"
#include <iostream>
#include <vector>
//#include "include\network\Command.h"

class GameObject
{

private:
	/// Dynamic List of components
	std::vector<Component *> g_components;
	int component_count;
protected:

public:
	/// Object ID
	int ID;

	GameObject();
	~GameObject();

	/// virtual update function
	virtual void update(){};


	void AddComponent(Component* comp);

///	void AttachComponent(ComponentType, argumentList, name);

///	void DetachComponent(name)
		
	void UpdateComponents();

///	void UpdateComponentType(ComponentType typeOfComponentToUpdate);

///	void HandleMessage(MessageType message);// echoes to all attached components

};

#endif