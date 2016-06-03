#pragma once
#include "RenderComponent.h"
#include "SystemGameObjectQueue.h"


class TitleScreenProps :
	public RenderComponent
{
public:
	TitleScreenProps();
	~TitleScreenProps();
	void Update();
};


void LoadTitleScreenProps();