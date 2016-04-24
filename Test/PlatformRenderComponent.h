#pragma once
#ifndef PLATFORMRENDERCOMPONENT_H_INCLUDED
#define PLATFORMRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "include\SceneManager.h"
#include "PlatformComponentIncludes.h"

class PlatformRenderComponent : public RenderComponent
{
public:
	/// Constructor
	PlatformRenderComponent(GameObject* platform, int team);
	/// Destructor
	~PlatformRenderComponent();
	/// Update
	void Update();
};

#endif