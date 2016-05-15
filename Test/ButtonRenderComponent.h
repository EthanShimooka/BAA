#pragma once
#include "RenderComponent.h"

class ButtonRenderComponent :
	public RenderComponent
{
public:
	ButtonRenderComponent(GameObject* button, int imageID, float scale);
	~ButtonRenderComponent();
	void Update();

private:
	int defaultImage;
	int currentImage;
	std::string layer;

public:
	void changeSprite(int imageID);
	void setToDefault();
	void toggleSprites();
	void toggleSprites(int num);
	void addSecondSprite(int imageID);
	void changeLayer(std::string layer);
	const std::string getLayer() const { return layer; }
	const int getCurrImage() const { return currentImage; }
};

