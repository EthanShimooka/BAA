#pragma once
#include "RenderComponent.h"
#include <iostream>

class TutorialRenderComponent :
	public RenderComponent
{
public:
	TutorialRenderComponent(GameObject* tutorial, int _imageID, float scale = 1);
	~TutorialRenderComponent();

	SceneManager* sceneMan;
	int imageID;
	std::string layer;
	bool on;
	void toggleImage();
	void toggleImage(bool on);
};

