#pragma once
#ifndef  BOOMERANGRENDERCOMPONENT_H_INCLUDED
#define  BOOMERANGRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
class BoomerangRenderComponent :
	public RenderComponent
{
public:
	BoomerangRenderComponent(GameObject* boomerang);
	~BoomerangRenderComponent();
	void Update();
};

#endif