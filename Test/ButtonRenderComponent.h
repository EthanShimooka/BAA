#pragma once
#include "RenderComponent.h"

class ButtonRenderComponent :
	public RenderComponent
{
public:
	ButtonRenderComponent(GameObject* button, int imageID, float scale);
	~ButtonRenderComponent();
	void Update();

	int defaultImage;
	int currentImage;

	void changeSprite(int imageID);
	void setToDefault();
	void toggleSprites();
	void addSecondSprite(int imageID);
};

