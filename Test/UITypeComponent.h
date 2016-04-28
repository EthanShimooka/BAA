/**
*  UIRenderComponet.h
*  Authors: Ethan Shimooka, Vincent Moudy
*  Date 2/29/2016
*  Description :
   UIRenderComponent represents the UI-specific Render class

*/

#pragma once
#ifndef UITYPECOMPONENT_H_INCLUDED
#define UITYPECOMPONENT_H_INCLUDED
#include "UIRenderComponent.h"
#include "include\SceneManager.h"
#include "include\network\NetIncludes.h"

class UITypeComponent : public UIRenderComponent
{
public:
	/// Constructor
	UITypeComponent();
	/// Destructor
	~UITypeComponent();

	/// Create a new UI object
	void createUIType(UIType ID);
	/// Update
	void Update();
};

#endif