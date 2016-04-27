#pragma once
#include "ClassComponent.h"
#include "PlayerObjectFactory.h"
class EagleClassComponent :
	public ClassComponent
{
public:
	EagleClassComponent(GameObject* player);
	~EagleClassComponent();
	void Update();
	int useAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();
	int maxBirdseed = 8;
};

