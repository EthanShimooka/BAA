#pragma once
#include "ClassComponent.h"
//#include "RenderComponent.h"

class ChickenClassComponent :
	public ClassComponent
{
public:
	ChickenClassComponent(GameObject* player);
	~ChickenClassComponent();
	void Update();
	bool UseAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};

