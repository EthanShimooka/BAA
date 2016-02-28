#pragma once
#ifndef FEATHERRENDERCOMPONENT_H_INCLUDED
#define FEATHERRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "include\SceneManager.h"

class FeatherRenderComponent : public RenderComponent
{
public:
	/// Constructor
	FeatherRenderComponent();
	/// Destructor
	~FeatherRenderComponent();
	/// Update
	void Update();
};

#endif