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
	int firstImage;
	int secondImage = NULL;
	int currentImage;
	float scale;
	std::string layer;
	SceneManager* sceneMan;

public:
	void changeSprite(int imageID);
	void setToDefault();
	void toggleSprites();
	void toggleSprites(int num);
	void addSecondSprite(int imageID);
	void changeLayer(std::string layer);
	std::string getLayer() const { return layer; }
	int getCurrImage() const { return firstImage; }
};

