#pragma once
#include "RenderComponent.h"
#include "SystemGameObjectQueue.h"

class BackgroundProps :
	public RenderComponent
{
public:
	BackgroundProps();
	~BackgroundProps();
	Animation * surf;
	void Update();
};

void LoadBackgroundProps();