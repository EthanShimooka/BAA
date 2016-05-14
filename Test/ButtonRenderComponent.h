#pragma once
#include "RenderComponent.h"

class ButtonRenderComponent :
	public RenderComponent
{
public:
	ButtonRenderComponent(GameObject* button, int imageID);
	~ButtonRenderComponent();
	void Update();

	int defaultImage;
	int currentImage;
	void changeSprite(int imageID);
	void setToDefault();
};

