#pragma once
#ifndef MINERENDERCOMPONENT_H_INCLUDED
#define MINERENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "MineComponentIncludes.h"
class MineRenderComponent : public RenderComponent{
public:
	/// Constructor
	MineRenderComponent(GameObject* player);
	/// Destructor
	~MineRenderComponent();
	/// Update Function
	void Update();
};
#endif
