#pragma once
#include "RenderComponent.h"
#ifndef MINERENDERCOMPONENT_H_INCLUDED
#define MINERENDERCOMPONENT_H_INCLUDED
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
