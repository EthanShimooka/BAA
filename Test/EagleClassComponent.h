#pragma once
#include "ClassComponent.h"
class EagleClassComponent :
	public ClassComponent
{
public:
	EagleClassComponent(GameObject* player);
	~EagleClassComponent();
	void Update();
	bool UseAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};

