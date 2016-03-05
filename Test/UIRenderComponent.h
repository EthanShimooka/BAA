/**
*  UIRenderComponet.h
*  Authors: Ethan Shimooka, Vincent Moudy
*  Date 2/29/2016
*  Description :
   UIRenderComponent represents the UI-specific Render class

*/

#pragma once
#ifndef UIRENDERCOMPONENT_H_INCLUDED
#define UIRENDERCOMPONENT_H_INCLUDED
#include "RenderUIComponent.h"
#include "include\SceneManager.h"

class UIRenderComponent : public RenderUIComponent
{
public:
	/// Constructor
	UIRenderComponent();
	/// Destructor
	~UIRenderComponent();

	/// Create a new UI object
	void createUIType(UIType ID);
	/// Update
	void Update();
};

#endif