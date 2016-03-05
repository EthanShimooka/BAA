/**
*  RenderComponet.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	RenderComponent represents the abstreact base class from which all other
	render Components are derived.

	The Render Component is responsible for containing the SDL object refrence
	and managing it. Will probably handle the calls to animation as well.

*/



#pragma once
#ifndef RENDERCOMPONENT_H_INCLUDED
#define RENDERCOMPONENT_H_INCLUDED

#include "Component.h"
#include "include\SDLRenderObject.h"
#include "include\AnimationLibrary.h"
#include "time.h"

#include <unordered_map>

#include "MovementComponent.h"
#include "GameObject.h"


class RenderComponent :	public Component
{
public:

	/// Constructor
	RenderComponent();

	/// Destructor
	~RenderComponent();

	/// Renderable Sprite pointer
	SDLRenderObject* objRef;
	list <SDLRenderObject*> allObjs;
	//hash <animation> animations;
	GameObject* gameObjectRef;


	/// Renderer Visibility Flag
	bool visible;
	/// horizontal Flip
	bool flipH;
	/// Verticle Flip
	bool flipV;

	/// Animations hash table
	unordered_map<string, Animation*> animations;
	/// Current animation that is applyied on update
	Animation* currentAnimation;
	/// Queued animation that will be played next (may be applyied immediately)
	Animation* nextAnimation;
	/// time of last render
	int unsigned lasttime;
	/// amount of time since animation's beginning
	int unsigned progress;

	/////////////////////////////////////////////////

	/// Assign Sprites 
	void AssignSprite(SDLRenderObject* rend);
	/// Updates Sprite to renderer
	virtual void Update();
	/// animation setter
	void setAnimation(string name);
	/// animate based on current animation
	void animate();
};

#endif
