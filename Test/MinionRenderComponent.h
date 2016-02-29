#pragma once
#ifndef MINIONRENDERCOMPONENT_H_INCLUDED
#define MINIONRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "include\SceneManager.h"

class MinionRenderComponent : public RenderComponent
{
public:
	/// Constructor
	MinionRenderComponent();
	/// Destructor
	~MinionRenderComponent();
	/// Update
	void Update();
};

#endif