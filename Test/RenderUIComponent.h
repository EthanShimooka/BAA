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
#ifndef RENDERUICOMPONENT_H_INCLUDED
#define RENDERUICOMPONENT_H_INCLUDED

#include "Component.h"
#include "include\SDLRenderObject.h"
#include "UIObject.h"


class RenderUIComponent : public Component
{
public:

	/// Constructor
	RenderUIComponent();

	/// Destructor
	~RenderUIComponent();

	/// Renderable Sprite pointer
	SDLRenderObject* objRef;
	std::list <SDLRenderObject*> allObjs;
	bool visible;

	/// UI objects reference
	UIObject* uiObjectRef;


	/////////////////////////////////////////////////

	/// Assign Sprites 
	void AssignSprite(SDLRenderObject* rend);
	/// Updates Sprite to renderer
	virtual void Update();


};

#endif
