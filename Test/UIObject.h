/**
*  GameObject.h
*  Authors: Ethan Shimooka, Vincent Moudy
*  Date 2/25/2016
*  Description :
UI Object serves as the "Entity" of the Entity-Component-System
pattern. The UIObject is essentially a component bag, with methods
for component access and the overall objects "world position".

*/


#pragma once

#ifndef UIOBJECT_H_INCLUDED
#define UIOBJECT_H_INCLUDED

#include "include\SceneManager.h"
#include "Component.h"
#include <iostream>
#include <vector>

const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;
const int READY_BUTTON_WIDTH = 25;
const int READY_BUTTON_HEIGHT = 12;

enum UIType{
	PLAY_BUTTON = 1,
	CANCEL_BUTTON = 2,
	BACK_BUTTON = 3,
	JOIN_BUTTON = 4,
	INVITE_BUTTON= 5,
	TIMER = 6,
	MENU_NAME = 7,
	OPTIONS_BUTTON = 8,
	READY_BUTTON = 9,
	PLAYER_SLOT = 10,
	CHICKEN = 3000,
	PEACOCK = 3100,
	FLAMINGO = 3200,
	QUAIL = 3300,
	TURKEY = 3500,
	EAGLE = 0,
	BIRDSEED_SHELL = 12,
	BIRDSEED_BAR = 13,
	CROSSHAIR = 14,
	CHARGE_SHELL = 15,
	CHARGE_BAR = 16,
	LOBBY_TIMER = 17,
	KILL_NOTIFICATION = 18,
};

/// t_component struct contains a component and a int enumerating its type
/// used anytime trying to find a certain component of UIObject (entitiy)
struct uiT_component {
	int type;
	Component * component;

};


/// UIObject (entity) main class

class UIObject{
public:

	/// Constructor
	UIObject();
	/// Constructor
	UIObject(float x, float y, float r, float s);
	/// Destructor
	~UIObject();

	/// Object ID
	UIType ID;
	UIType changeTo;

	///Screen X Position
	float posX;
	///Screen Y Position
	float posY;

	///Rotation
	float rotation;

	///Scale
	float scale;

	/// Visible
	bool visible;

	bool hoverPicture = false;

	bool changePicture = false;

	bool ready = false;
	
	bool bottom = false;

	uint64_t player = 0;

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

	/// Set postion of UIObject
	void setPos(float x, float y);

	/// Set the rotation for this object.
	void setRotation(float r);

	/// Set the scale for this object
	void setScale(float s);

	/// To Be Implemented

	///	void AttachComponent(ComponentType, argumentList, name);

	void DetachComponent();

	void setWidthAndHeight(int w, int h);

	int getWidth();

	int getHeight();

	
	///	void HandleMessage(MessageType message);// echoes to all attached component

private:
	/// Dynamic List of components
	std::vector<uiT_component> g_components;
	/// Number of Components Bound to GameObject
	int component_count;
	int width, height;
};

#endif