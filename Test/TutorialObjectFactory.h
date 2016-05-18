#pragma once
#include "GameObjectFactory.h"
#include "TutorialRenderComponent.h"

class TutorialObjectFactory :
	public GameObjectFactory
{
public:
	TutorialObjectFactory();
	~TutorialObjectFactory();

	GameObject* Spawn(uint64_t PID, int imageID, float posX, float posY);
};

