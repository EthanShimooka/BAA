#pragma once
#ifndef FANRENDERCOMPONENT_H_INCLUDED
#define FANRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "FanComponentIncludes.h"
class FanRenderComponent : public RenderComponent{
public:
	/// Constructor
	FanRenderComponent(GameObject* player);
	/// Destructor
	~FanRenderComponent();
	/// Update Function

	void buildAnimations();

	void Update();
};
#endif

