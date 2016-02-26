#pragma once
#ifndef RENDERCOMPONENT_H_INCLUDED
#define RENDERCOMPONENT_H_INCLUDED

#include "Component.h"
#include "include\SDLRenderObject.h"
#include "include\SDLRenderObject.h"

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


	GameObject* gameObjectRef;



	/// Renderer Visibility Flag
	bool visible;
	/// horizontal Flip
	bool flipH;
	/// Verticle Flip
	bool flipV;


	/////////////////////////////////////////////////

	/// Assign Sprites 
	void AssignSprite(SDLRenderObject* rend);
	/// Updates Sprite to renderer
	void Update();


};

#endif
