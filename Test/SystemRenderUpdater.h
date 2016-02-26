#pragma once
#include <vector>
#include "GameObject.h"
class SystemRenderUpdater
{
public:
	SystemRenderUpdater();
	~SystemRenderUpdater();
	void RenderUpdate(std::vector<GameObject*> rend);
};

